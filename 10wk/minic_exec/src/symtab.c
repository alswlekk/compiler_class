#include <string.h>
#include <stdio.h>
#include "symtab.h"

#define MAX_SYMS 1024

typedef struct {
    char name[32];
    int value;
    int in_use;
    int initialized;
} Sym;

static Sym table[MAX_SYMS];

void sym_init(void)
{
    memset(table, 0, sizeof(table));
}

static Sym* find_sym(const char* name)
{
    for (int i = 0; i < MAX_SYMS; ++i) {
        if (table[i].in_use && strcmp(table[i].name, name) == 0) {
            return &table[i];
        }
    }
    return NULL;
}

int sym_set(const char* name, int value)
{
    Sym* s = find_sym(name);
    if (!s) {
        for (int i = 0; i < MAX_SYMS; ++i) {
            if (!table[i].in_use) {
                table[i].in_use = 1;
                strncpy(table[i].name, name, sizeof(table[i].name) - 1);
                s = &table[i];
                break;
            }
        }
    }
    if (!s) {
        fprintf(stderr, "symbol table full\n");
        return 0;
    }
    s->value = value;
    s->initialized = 1;
    return 1;
}

int sym_get(const char* name, int* out)
{
    Sym* s = find_sym(name);
    if (!s || !s->initialized) return 0;
    if (out) *out = s->value;
    return 1;
}
