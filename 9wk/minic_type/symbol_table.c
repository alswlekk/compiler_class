/**
 * symbol_table.c — 해시+가드 기반 스코프 심볼 테이블
 */
#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NHASH 211
static struct Sym* buckets[NHASH];
static int cur_level = 0;

/* 스코프 경계 guard(name==NULL) */
static struct Sym* make_guard(void){
  struct Sym* g = (struct Sym*)calloc(1, sizeof(struct Sym));
  g->name = NULL; g->level = cur_level;
  return g;
}

static unsigned h(const char *s){
  unsigned v=0; while(*s) v = v*131u + (unsigned char)(*s++);
  return v % NHASH;
}

void symtab_init(void){ memset(buckets, 0, sizeof(buckets)); cur_level = 0; }

void symtab_fini(void){
  for(int i=0;i<NHASH;i++){
    struct Sym* p=buckets[i];
    while(p){ struct Sym* n=p->next; free(p); p=n; }
    buckets[i]=NULL;
  }
}

void scope_push(void){
  cur_level++;
  for(int i=0;i<NHASH;i++){
    struct Sym* g=make_guard(); g->next=buckets[i]; buckets[i]=g;
  }
}

void scope_pop(void){
  for(int i=0;i<NHASH;i++){
    struct Sym* p=buckets[i];
    while(p && p->name!=NULL){ struct Sym* n=p->next; free(p); p=n; }
    if(p){ struct Sym* n=p->next; free(p); buckets[i]=n; }
  }
  cur_level--;
}

bool sym_put(const char *name, SymKind kind, TypeKind tkind, int arity){
  unsigned idx=h(name);
  /* 현재 스코프 guard 전까지만 중복 검사 */
  for(struct Sym* p=buckets[idx]; p && p->name!=NULL; p=p->next){
    if(strcmp(p->name,name)==0) return false;
  }
  struct Sym* s=(struct Sym*)calloc(1,sizeof(struct Sym));
  s->name=name; s->kind=kind; s->tkind=tkind; s->arity=arity; s->level=cur_level;
  s->next=buckets[idx]; buckets[idx]=s;
  return true;
}

struct Sym* sym_get(const char *name){
  unsigned idx=h(name);
  for(struct Sym* p=buckets[idx]; p; p=p->next){
    if(p->name && strcmp(p->name,name)==0) return p;
  }
  return NULL;
}

void symtab_dump(void){
  for(int i=0;i<NHASH;i++){
    for(struct Sym* p=buckets[i]; p; p=p->next){
      if(!p->name) continue;
      const char* k = (p->kind==SYM_VAR?"var":p->kind==SYM_PARAM?"param":"func");
      const char* t = (p->tkind==TY_INT?"int":p->tkind==TY_FLOAT?"float":
                       p->tkind==TY_CHAR?"char":p->tkind==TY_VOID?"void":"error");
      printf("[%d] %-5s %-6s %s (arity=%d)\n", p->level, k, t, p->name, p->arity);
    }
  }
}
