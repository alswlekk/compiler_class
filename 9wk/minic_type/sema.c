#include "sema.h"
#include "symbol_table.h"
#include "types.h"
#include <stdio.h>
#include <string.h>

int sema_errors = 0;

/* --- 헬퍼: 진단 & 타입 매핑 --- */
static void err(int line, const char* fmt, const char* a){
  sema_errors++; fprintf(stderr, "[SEMA] line %d: ", line);
  if(a) fprintf(stderr, fmt, a), fputc('\n', stderr);
  else  fprintf(stderr, "%s\n", fmt);
}

static TypeKind type_from_str(const char* s){
  if(!s) return TY_ERROR;
  if(strcmp(s,"int")==0)   return TY_INT;
  if(strcmp(s,"float")==0) return TY_FLOAT;
  if(strcmp(s,"char")==0)  return TY_CHAR;
  if(strcmp(s,"void")==0)  return TY_VOID;
  return TY_ERROR;
}

/* 간단 승격 규칙: char→int, float가 섞이면 float, 비교/논리는 int 취급 */
static TypeKind binop_type(TypeKind a, TypeKind b){
  if(a==TY_ERROR || b==TY_ERROR) return TY_ERROR;
  if(a==TY_CHAR) a=TY_INT;
  if(b==TY_CHAR) b=TY_INT;
  if(a==TY_FLOAT || b==TY_FLOAT) return TY_FLOAT;
  return TY_INT;
}

/* --- 전방 선언 --- */
static TypeKind check_expr(Node* n);
static void     visit_stmt(Node* s, TypeKind func_ret);
static void     visit_block(Node* comp, TypeKind func_ret);

/* 선언: type_spec + init_declarator_list */
static void handle_decl(Node* decl){
  TypeKind t = type_from_str(decl->child[0]->op);
  Node* list = decl->child[1];
  for(int i=0;i<list->nchild;i++){
    Node* idecl = list->child[i]; /* NK_INIT_DECL, op=이름, child[0]=초기식 or NULL */
    const char* name = idecl->op;
    if(!sym_put(name, SYM_VAR, t, 0))
      err(idecl->line, "redeclaration of '%s'", name);
    if(idecl->nchild==1 && idecl->child[0]){
      TypeKind rt = check_expr(idecl->child[0]);
      if(t==TY_INT && rt==TY_FLOAT)
        err(idecl->line, "narrowing init from float to int in '%s'", name);
      if(t==TY_VOID || rt==TY_VOID)
        err(idecl->line, "invalid void usage in init of '%s'", name);
    }
  }
}

/* 함수 정의: 시그니처 등록 + 파라미터 등록 + 본문 검사 */
static void handle_func_def(Node* f){
  TypeKind ret = type_from_str(f->child[0]->op);
  const char* fname = f->op;
  int arity = f->child[1]->nchild;

  if(!sym_put(fname, SYM_FUNC, ret, arity))
    err(f->line, "redefinition of function '%s'", fname);

  scope_push(); /* 함수 스코프 */

  /* 파라미터 */
  for(int i=0;i<arity;i++){
    Node* p = f->child[1]->child[i]; /* NK_PARAM, op=이름, child[0]=type */
    TypeKind pt = type_from_str(p->child[0]->op);
    if(!sym_put(p->op, SYM_PARAM, pt, 0))
      err(p->line, "duplicate parameter '%s'", p->op);
  }

  /* 본문 { STMT_LIST } */
  visit_block(f->child[2], ret);

  scope_pop();
}

/* 블록 { ... } */
static void visit_block(Node* comp, TypeKind func_ret){
  scope_push();
  Node* list = comp->child[0]; /* NK_STMT_LIST */
  for(int i=0;i<list->nchild;i++){
    Node* n = list->child[i];
    if(n->kind == NK_DECL) handle_decl(n);
    else                   visit_stmt(n, func_ret);
  }
  scope_pop();
}

/* 문장 */
static void visit_stmt(Node* s, TypeKind func_ret){
  switch(s->kind){
    case NK_EXPR_STMT:
      if(s->nchild==1 && s->child[0]) (void)check_expr(s->child[0]);
      break;
    case NK_RETURN:
      if(s->nchild==1 && s->child[0]){
        TypeKind rt = check_expr(s->child[0]);
        if(func_ret==TY_VOID) err(s->line, "return with a value in void function", NULL);
        else if(func_ret==TY_INT && rt==TY_FLOAT)
          err(s->line, "narrowing return from float to int", NULL);
        else if(rt==TY_VOID)
          err(s->line, "invalid void expression in return", NULL);
      } else {
        if(func_ret != TY_VOID) err(s->line, "non-void function must return a value", NULL);
      }
      break;
    case NK_IF:
      (void)check_expr(s->child[0]);
      visit_stmt(s->child[1], func_ret);
      if(s->nchild==3) visit_stmt(s->child[2], func_ret);
      break;
    case NK_WHILE:
      (void)check_expr(s->child[0]);
      visit_stmt(s->child[1], func_ret);
      break;
    case NK_FOR:
      if(s->child[0]){
        if(s->child[0]->kind==NK_DECL) handle_decl(s->child[0]);
        else (void)check_expr(s->child[0]);
      }
      if(s->child[1]) (void)check_expr(s->child[1]);
      if(s->child[2]) (void)check_expr(s->child[2]);
      visit_stmt(s->child[3], func_ret);
      break;
    case NK_COMPOUND:
      visit_block(s, func_ret);
      break;
    default:
      break;
  }
}

/* 식 타입 추론 */
static TypeKind check_expr(Node* n){
  if(!n) return TY_VOID;
  switch(n->kind){
    case NK_INT:   return TY_INT;
    case NK_FLOAT: return TY_FLOAT;
    case NK_CHAR:  return TY_CHAR;
    case NK_STRING:
      err(n->line, "string literal used in expression (unsupported here)", NULL);
      return TY_ERROR;

    case NK_VAR: {
      Sym* s = sym_get(n->op);
      if(!s){ err(n->line, "use of undeclared identifier '%s'", n->op); return TY_ERROR; }
      return s->tkind;
    }

    case NK_ASSIGN: {
      Sym* s = sym_get(n->op);
      if(!s){ err(n->line, "assignment to undeclared identifier '%s'", n->op); return TY_ERROR; }
      TypeKind rt = check_expr(n->child[0]);
      if(s->tkind==TY_INT && rt==TY_FLOAT)
        err(n->line, "narrowing assignment to '%s' (float→int)", n->op);
      if(s->tkind==TY_VOID || rt==TY_VOID)
        err(n->line, "invalid void type in assignment to '%s'", n->op);
      return s->tkind;
    }

    case NK_UNOP:
      return check_expr(n->child[0]);

    case NK_BINOP: {
      TypeKind a = check_expr(n->child[0]);
      TypeKind b = check_expr(n->child[1]);
      return binop_type(a,b);
    }

    case NK_CALL: {
      Sym* f = sym_get(n->op);
      if(!f || f->kind!=SYM_FUNC){
        err(n->line, "call to undeclared function '%s'", n->op);
        return TY_ERROR;
      }
      /* 인자 수 체크 */
      int nargs = n->child[0] ? n->child[0]->nchild : 0;
      if(f->arity != nargs)
        err(n->line, "wrong # of args in call to '%s'", n->op);
      /* 인자 타입 대강 검사(VOID 금지) */
      if(n->child[0]){
        for(int i=0;i<n->child[0]->nchild;i++){
          TypeKind at = check_expr(n->child[0]->child[i]);
          if(at==TY_VOID) err(n->line, "void value used as argument", NULL);
        }
      }
      return f->tkind; /* 반환 타입 */
    }

    default:
      if(n->nchild==1) return check_expr(n->child[0]);
      return TY_ERROR;
  }
}

/* translation_unit */
static void visit_tu(Node* tu){
  for(int i=0;i<tu->nchild;i++){
    Node* ed = tu->child[i];
    if(ed->kind == NK_FUNC_DEF) handle_func_def(ed);
    else if(ed->kind == NK_DECL) handle_decl(ed); /* 전역 변수 */
  }
}

void sema_run(Node *root){
  symtab_init();
  scope_push(); /* 전역 스코프 */
  if(root && root->kind==NK_TRANSLATION_UNIT) visit_tu(root);
  scope_pop();
  /* 필요 시 symtab_dump(); */
}
