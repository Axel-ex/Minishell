/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:45:38 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 12:39:16 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	**init_token(char **line)
{
	t_token	**token_list;
	int		size;

	size = 0;
	while (line[size])
		size++;
	token_list = (t_token **)malloc(sizeof(t_token *) * size + 1);
	if (!token_list)
		alloc_error("token_list");
	token_list[size + 1] = NULL;
	return (token_list);
}

t_shell	*init_shell(void)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (alloc_error("shell"));
	shell->path = ft_split(getenv("PATH"), ':');
	shell->lines = NULL;
	return (shell);
}
