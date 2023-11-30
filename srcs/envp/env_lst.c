/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 23:10:03 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/30 18:42:41 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
It's basically the same as token! they are added onto a list
and we will be able to go through the list with a scanner!
*/

char	*get_key(char *envp)
{
	char	*key;
	int		size;

	size = 0;
	while (envp[size] && envp[size] != '=')
		size++;
	key = (char *)malloc(sizeof(char) * size + 1);
	if (!key)
		return (alloc_error("get key."));
	key[size] = '\0';
	while (size--)
		key[size] = envp[size];
	return (key);
}

/*
Skip the char until finding a '=' and return a copy of the rest
of the string
*/
char	*get_value(char *envp)
{
	char	*value;
	int		size;
	int		start;
	int		i;

	size = 0;
	i = 0;
	while (envp[size] && envp[size] != '=')
		size++;
	start = size + 1;
	while (envp[size])
		size++;
	value = (char *)malloc(sizeof(char) * ((size - start) + 1));
	if (!value)
		return ((alloc_error("get value.")));
	while (start < size)
	{
		value[i] = envp[start];
		i++;
		start++;
	}
	value[i] = '\0';
	return (value);
}

void	env_add_back(char *key, char *value)
{
	t_env	*var;

	var = (t_env *)malloc(sizeof(t_env));
	if (!var)
		return ;
	var->key = key;
	var->value = value;
	ft_lstadd_back(&sh()->env_lst, ft_lstnew(var));
}

void	get_env_list(char **envp)
{
	char	*key;
	char	*value;
	int		i;

	i = -1;
	while (envp[++i])
	{
		key = get_key(envp[i]);
		value = NULL;
		value = get_value(envp[i]);
		env_add_back(key, value);
	}
}
