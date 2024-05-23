#ifndef _STRFUNCS_H
#define _STRFUNCS_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

size_t string_length(const char *str);

char *string_filter(const char *str, char c);

bool string_is_symmetric(const char *str);

#endif