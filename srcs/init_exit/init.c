/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:45:38 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/30 15:43:49 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(char **envp)
{
	ft_bzero(sh(), sizeof(t_shell));
	sh()->envp = envp;
	get_env_list(envp);
	sh()->path = ft_split(getenv("PATH"), ':');
	sh()->fd_in = STDIN_FILENO;
	sh()->fd_out = STDOUT_FILENO;
	sh()->nb_cmds = 0;
	sh()->exit_status = 0;
	sh()->count = 0;
}
