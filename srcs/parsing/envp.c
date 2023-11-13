/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:31:46 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/13 17:31:50 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	copy_key_content(t_env *env, char *equals, int index)
{
	int	key_len;
	int	content_len;

	key_len = equals - env->env[index];
	env->key[index] = malloc(key_len + 1);
	if (!env->key[index])
		exit(EXIT_FAILURE);
	ft_strlcpy(env->key[index], env->env[index], key_len + 1);
	equals++;
	content_len = ft_strlen(equals);
	env->content[index] = malloc(content_len + 1);
	if (!env->content[index])
		exit(EXIT_FAILURE);
	ft_strlcpy(env->content[index], equals, content_len + 1);
}

void	populate_env_struct(t_env *env)
{
	int		i;
	char	*equals;

	i = 0;
	env->len = 0;
	while (env->env[env->len] != NULL)
		env->len++;
	allocate_memory(env);
	while (i < env->len)
	{
		equals = ft_strchr(env->env[i], '=');
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
