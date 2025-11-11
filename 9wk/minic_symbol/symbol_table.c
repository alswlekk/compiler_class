/**
 * symbol_table.c
 * -----------------------------------------------
 * Symbol Table (심볼 테이블) 관리 모듈
 *
 * 컴파일러의 의미 분석 단계에서 사용되는 핵심 자료구조.
 * - 변수, 함수, 매개변수 이름 등 "심볼(Symbol)"을 저장하고
 *   스코프(중첩 블록)에 따라 유효 범위를 관리한다.
 *
 * 구현 방식:
 *   • 해시 테이블(Hash Table) + 체인(linked list)
 *   • 스코프는 "가드(guard node)"를 삽입하여 구분
 *   • scope_push() / scope_pop() 로 스코프 스택을 관리
 *
 * 지원 기능:
 *   - symtab_init() / symtab_fini(): 전체 초기화 및 해제
 *   - scope_push() / scope_pop(): 스코프 진입/탈출
 *   - sym_put(): 심볼 등록 (중복 선언 시 false)
 *   - sym_get(): 이름으로 심볼 탐색 (가장 가까운 스코프 우선)
 *   - symtab_dump(): 현재 테이블 상태 출력
 *
 */


#include "symbol_table.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define NHASH 211       /* 해시 버킷 수 — 소수(prime) 사용으로 충돌 감소 */

static Sym* buckets[NHASH];
/* 현재 스코프 깊이(0=전역, 1=함수, 2=블록 등) */
static int cur_level = 0;

/**
 * make_guard()
 * -------------------------------------------------
 * 스코프 경계 표시용 노드(guard node)를 생성한다.
 * name==NULL 인 노드를 각 버킷의 맨 앞에 삽입해
 * scope_pop() 시 이 노드 전까지의 심볼만 제거하도록 한다.
 */
 static Sym* make_guard(void){
  Sym* g = (Sym*)calloc(1, sizeof(Sym));
  g->name = NULL; g->level = cur_level;
  return g;
}

/**
 * h(name)
 * -------------------------------------------------
 * 간단한 해시 함수.
 * 문자열을 131진법으로 계산한 뒤 버킷 수(NHASH)로 나눈다.
 */
static unsigned h(const char *s){
  unsigned v=0; while(*s) v = v*131u + (unsigned char)(*s++);
  return v % NHASH;
}

/**
 * symtab_init()
 * -------------------------------------------------
 * 전역 심볼 테이블을 초기화한다.
 * (모든 버킷 포인터를 NULL로 설정)
 */
void symtab_init(void){ memset(buckets, 0, sizeof(buckets)); cur_level = 0; }

/**
 * symtab_fini()
 * -------------------------------------------------
 * 모든 심볼 노드를 해제한다.
 * (스코프 구분 없이 전체 제거)
 */
void symtab_fini(void){
  for(int i=0;i<NHASH;i++){
    Sym* p=buckets[i];
    while(p){ Sym* n=p->next; free(p); p=n; }
    buckets[i]=NULL;
  }
}

/**
 * scope_push()
 * -------------------------------------------------
 * 새 스코프(블록, 함수 등)에 진입할 때 호출.
 * - 스코프 깊이(cur_level) 1 증가
 * - 모든 버킷 앞에 guard 노드 삽입
 *
 * 예:
 *   {   ← scope_push()
 *     int x;
 *   }   ← scope_pop()
 */
void scope_push(void){
  cur_level++;
  for(int i=0;i<NHASH;i++){
    Sym* g=make_guard(); g->next=buckets[i]; buckets[i]=g;
  }
}

/**
 * scope_pop()
 * -------------------------------------------------
 * 현재 스코프에서 선언된 모든 심볼을 제거한다.
 * - guard 노드까지의 모든 노드를 free()
 * - guard 노드도 함께 제거
 * - 스코프 깊이 1 감소
 */
void scope_pop(void){
  for(int i=0;i<NHASH;i++){
    Sym* p=buckets[i];
    while(p && p->name!=NULL){ Sym* n=p->next; free(p); p=n; }
    if(p){ Sym* n=p->next; free(p); buckets[i]=n; }
  }
  cur_level--;
}

/**
 * sym_put(name, kind, arity)
 * -------------------------------------------------
 * 현재 스코프에 새 심볼을 등록한다.
 * - name: 심볼 이름
 * - kind: SYM_VAR / SYM_PARAM / SYM_FUNC
 * - arity: 함수의 인자 개수 (변수는 0)
 *
 * 중복 선언 시 false 반환 (등록 실패)
 * 정상 등록 시 true 반환
 */
bool sym_put(const char *name, SymKind kind, int arity){
  unsigned idx=h(name);
  
  /* 현재 스코프(가드 전까지) 중복 검사 */
  for(Sym* p=buckets[idx]; p && p->name!=NULL; p=p->next){
    if(strcmp(p->name,name)==0) return false;
  }
  
  /* 새 심볼 생성 및 연결 */
  Sym* s=(Sym*)calloc(1,sizeof(Sym));
  s->name=name; s->kind=kind; s->arity=arity; s->level=cur_level;
  s->next=buckets[idx]; buckets[idx]=s;
  return true;
}

/**
 * sym_get(name)
 * -------------------------------------------------
 * 현재 및 모든 상위 스코프에서 심볼을 탐색한다.
 * - 가장 가까운(최근) 스코프의 심볼을 반환
 * - 존재하지 않으면 NULL 반환
 */
Sym* sym_get(const char *name){
  unsigned idx=h(name);
  for(Sym* p=buckets[idx]; p; p=p->next){
    if(p->name && strcmp(p->name,name)==0) return p;
  }
  return NULL;
}

/**
 * symtab_dump()
 * -------------------------------------------------
 * 전체 심볼 테이블 내용을 디버깅용으로 출력한다.
 * (스코프 번호, 종류, 이름, 인자 수)
 */
void symtab_dump(void){
  for(int i=0;i<NHASH;i++){
    for(Sym* p=buckets[i]; p; p=p->next){
      if(!p->name) continue;
      const char* k = (p->kind==SYM_VAR?"var":p->kind==SYM_PARAM?"param":"func");
      printf("[%d] %-6s %s (arity=%d)\n", p->level, k, p->name, p->arity);
    }
  }
}
