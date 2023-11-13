
#include "../../includes/minishell.h"

void	copy_key_content(t_env *env, char *equals, int index)
{
	int	key_len;

	key_len = equals - env->env[index];
	env->key[index] = malloc(key_len + 1);
	env->content[index] = ft_strdup(equals + 1);
	if (!env->key[index] || !env->content[index])
		exit(EXIT_FAILURE);
	ft_strlcpy(env->key[index], env->env[index], key_len);
	env->key[index][key_len] = '\0';
}

void	populate_env_struct(t_env *env)
{
	int		i;
	char	*equals;

	env->len = 0;
	while (env->env[env->len] != NULL)
		env->len++;
	allocate_memory(env);
	i = 0;
	while (i < env->len)
	{
		equals = strchr(env->env[i], '=');
		if (equals != NULL)
			copy_key_content(env, equals, i);
		else
			exit(EXIT_FAILURE);
		i++;
	}
}

void	free_memory(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->len)
	{
		free(env->key[i]);
		free(env->content[i]);
		i++;
	}
	free(env->key);
	free(env->content);
}

void	env_len(t_env *env)
{
	env->len = 0;
	while (env->env[env->len] != NULL)
		env->len++;
}

void	allocate_memory(t_env *env)
{
	env->key = malloc(sizeof(char *) * env->len);
	env->content = malloc(sizeof(char *) * env->len);
	if (!env->key || !env->content)
		exit(EXIT_FAILURE);
}



/*becomes this*/
// void	env_len(void)
// {
// 	int	i;

// 	i = 0;
// 	while (sh()->env.env[i])
// 		i++;
// 	sh()->env.len = i;
// }

// void	init_env(void)
// {
// 	sh()->env.content = malloc(sizeof(char *) * (sh()->env.len + 1));
// 	if (sh()->env.content)
// 		exit(EXIT_FAILURE);
// 	sh()->env.key = malloc(sizeof(char *) * (sh()->env.len + 1));
// 	if (!sh()->env.key)
// 		exit(EXIT_FAILURE);
// }