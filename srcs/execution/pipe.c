/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/18 14:02:51 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/21 11:28:16 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pipe_create(void)
{
	int	i;

	i = -1;
	sh()->pipes = (int **)malloc(sizeof(int *));
	if (!sh()->pipes)
		return ;
	while (++i < sh()->nb_cmds - 1)
	{
		sh()->pipes[i] = (int *)malloc(sizeof(int) * 2);
		if (pipe(sh()->pipes[i]))
			print_error(errno, "pipe call", NULL);
	}
}

void	pipe_connect(int ast_pos)
{
	if (sh()->nb_cmds < 2)
		return ;
	if (ast_pos)
		sh()->fd_in = sh()->pipes[ast_pos - 1][0];
	if (ast_pos != sh()->nb_cmds - 1)
		sh()->fd_out = sh()->pipes[ast_pos][1];
}
