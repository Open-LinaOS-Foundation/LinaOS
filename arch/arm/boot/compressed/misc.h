#ifndef MISC_H
#define MISC_H

#include <linaos/compiler.h>

void error(char *x) __noreturn;
extern unsigned long free_mem_ptr;
extern unsigned long free_mem_end_ptr;

#endif
