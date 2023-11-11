
#include "../../includes/minishell.h"



void	env_len(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env.env[i])
		i++;
	shell->env.len = i;
}

void	init_env(t_shell *shell)
{
	shell->env.content = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.content)
		exit(EXIT_FAILURE);
	shell->env.key = malloc(sizeof(char *) * (shell->env.len + 1));
	if (!shell->env.key)
		exit(EXIT_FAILURE);
}