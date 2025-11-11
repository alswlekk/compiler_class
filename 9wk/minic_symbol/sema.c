#include "sema.h"
#include "symbol_table.h"
#include <stdio.h>

int sema_errors = 0;

/* 에러 출력 헬퍼 */
static void err(int line, const char* msg, const char* name){
  sema_errors++;
  if(name) fprintf(stderr, "[SEMA] line %d: %s: %s\n", line, msg, name);
  else     fprintf(stderr, "[SEMA] line %d: %s\n", line, msg);
}

/* ----- 전방선언: 방문 함수들 ----- */
static void visit_stmt(Node* s);
static void visit_block(Node* comp);
static void visit_expr(Node* e);

/* 선언 처리:  type_spec + init_declarator_list  (여기서는 이름만 등록) */
static void handle_decl(Node* decl){
  Node* type = decl->child[0];   /* NK_TYPE (사용 안 함: 심볼만) */
  Node* list = decl->child[1];   /* NK_INIT_DECL_LIST */
  (void)type; /* 타입은 이번 예제에서 사용하지 않음 */

  for(int i=0;i<list->nchild;i++){
    Node* idecl = list->child[i];  /* NK_INIT_DECL, op=이름, child[0]=초기식 or NULL */
    const char* name = idecl->op;
    if(!sym_put(name, SYM_VAR, 0)){
      err(idecl->line, "redeclaration of identifier", name);
    }
    /* 초기식 내부에 식별자가 있으면 그 사용은 visit_expr에서 별도 검증됨 */
  }
}

/* 함수 정의 처리: 시그니처 등록 + 스코프 진입 + 파라미터 등록 + 본문 방문 */
static void handle_func_def(Node* f){
  /* child: [0]=ret type, [1]=param_list, [2]=compound */
  const char* fname = f->op;
  int arity = f->child[1]->nchild;

  if(!sym_put(fname, SYM_FUNC, arity)){
    err(f->line, "redefinition of function", fname);
  }

  /* 함수 스코프 */
  scope_push();

  /* 파라미터 등록 */
  for(int i=0;i<f->child[1]->nchild;i++){
    Node* p = f->child[1]->child[i]; /* NK_PARAM, op=이름, child[0]=type */
    if(!sym_put(p->op, SYM_PARAM, 0)){
      err(p->line, "duplicate parameter name", p->op);
    }
  }

  /* 본문 블록 방문 */
  visit_block(f->child[2]);

  scope_pop();
}

/* 블록 { ... } 방문: 내부 선언/문 순회 */
static void visit_block(Node* comp){
  /* comp: NK_COMPOUND -> child[0] = STMT_LIST */
  scope_push();
  Node* list = comp->child[0];
  for(int i=0;i<list->nchild;i++){
    Node* n = list->child[i];
    if(n->kind == NK_DECL) handle_decl(n);
    else                   visit_stmt(n);
  }
  scope_pop();
}

/* 문 방문 */
static void visit_stmt(Node* s){
  switch(s->kind){
    case NK_EXPR_STMT:
      if(s->nchild==1 && s->child[0]) visit_expr(s->child[0]);
      break;
    case NK_RETURN:
      if(s->nchild==1 && s->child[0]) visit_expr(s->child[0]);
      break;
    case NK_IF:
      visit_expr(s->child[0]);                /* cond */
      visit_stmt(s->child[1]);                /* then */
      if(s->nchild==3) visit_stmt(s->child[2]);  /* else */
      break;
    case NK_WHILE:
      visit_expr(s->child[0]);                /* cond */
      visit_stmt(s->child[1]);
      break;
    case NK_FOR:
      /* child: [init, cond, step, body] — init은 decl 또는 expr_opt(NULL 가능) */
      if(s->child[0]){
        if(s->child[0]->kind == NK_DECL) handle_decl(s->child[0]);
        else visit_expr(s->child[0]);
      }
      if(s->child[1]) visit_expr(s->child[1]);
      if(s->child[2]) visit_expr(s->child[2]);
      visit_stmt(s->child[3]);
      break;
    case NK_COMPOUND:
      visit_block(s);
      break;
    default:
      /* 기타는 필요 시 확장 */
      break;
  }
}

/* 식 방문: “심볼 존재 여부”만 검사 */
static void visit_expr(Node* e){
  if(!e) return;
  switch(e->kind){
    case NK_VAR: {
      if(!sym_get(e->op)) err(e->line, "use of undeclared identifier", e->op);
      break;
    }
    case NK_ASSIGN: {
      /* op=좌변 변수명, child[0]=rhs */
      if(!sym_get(e->op)) err(e->line, "assignment to undeclared identifier", e->op);
      if(e->nchild==1 && e->child[0]) visit_expr(e->child[0]);
      break;
    }
    case NK_CALL: {
      Sym* f = sym_get(e->op);
      if(!f || f->kind!=SYM_FUNC){
        err(e->line, "call to undeclared function", e->op);
      } else {
        int nargs = e->child[0] ? e->child[0]->nchild : 0;
        if(f->arity != nargs){
          err(e->line, "wrong number of arguments in call to", e->op);
        }
      }
      /* 인자들 내부 식별자 사용 검사 */
      if(e->child[0]){
        for(int i=0;i<e->child[0]->nchild;i++)
          visit_expr(e->child[0]->child[i]);
      }
      break;
    }
    case NK_UNOP:
      if(e->nchild==1) visit_expr(e->child[0]);
      break;
    case NK_BINOP:
      if(e->nchild>=1) visit_expr(e->child[0]);
      if(e->nchild>=2) visit_expr(e->child[1]);
      break;
    default:
      /* 상수, 괄호식 등: 자식들만 순회 */
      for(int i=0;i<e->nchild;i++) visit_expr(e->child[i]);
      break;
  }
}

/* 최상위(translation unit) 방문: 함수/전역 선언 */
static void visit_tu(Node* tu){
  for(int i=0;i<tu->nchild;i++){
    Node* ed = tu->child[i];
    if(ed->kind == NK_FUNC_DEF) {
      handle_func_def(ed);
    } else if(ed->kind == NK_DECL){
      /* 전역 변수 선언 */
      handle_decl(ed);
    }
  }
}

void sema_run(Node *root){
  symtab_init();
  scope_push();                /* 전역 스코프 */
  if(root && root->kind==NK_TRANSLATION_UNIT) visit_tu(root);
  scope_pop();
  /* 필요시 symtab_dump(); */
  /* symtab_fini();  // 종료 시 전체 해제 원하면 호출 */
}
