/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:42 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/09 11:38:53 by achabrer         ###   ########.fr       */
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
		free(pipes[i]);
	free(pipes);
}
