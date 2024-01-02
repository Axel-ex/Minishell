/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 12:49:54 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/02 15:59:11 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_exit(t_ast *ast)
{
	if (ast->args[2])
	{
		print_error(1, "too many arguments", "exit");
		return ;
	}
	if (ast->args[1] && ft_isnumeric(ast->args[1]))
		sh()->exit_status = ft_atoi(ast->args[1]) % 256;
	else if (ast->args[1] && !ft_isnumeric(ast->args[1]))
		print_error(255, "numeric argument required", ast->args[1]);
	free_shell(false);
}
