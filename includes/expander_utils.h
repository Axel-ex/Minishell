#ifndef EXPANDER_UTILS_H
#define EXPANDER_UTILS_H

# include "minishell.h"


void free_resources(char *old_res, char *key, char *value);
char *expand_variable(char *cnt);

#endif 