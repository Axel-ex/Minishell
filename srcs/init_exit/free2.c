/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:42 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/25 11:53:56 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(int **pipes)
{
	int	i;

	if (!pipes)
		return ;
	i = -1;
	while (++i < sh()->nb_cmds)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
	}
	free(pipes);
}

void	update_path(void)
{
	char	*path;

	path = getenv_var("PATH");
	if (!path)
	{
		if (sh()->path)
		{
			free_matrix(sh()->path);
			sh()->path = NULL;
		}
		return ;
	}
	free_matrix(sh()->path);
	sh()->path = ft_split(path, ':');
	free(path);
}
