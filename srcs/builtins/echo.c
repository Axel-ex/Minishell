/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:01:08 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/08 12:40:55 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_echo(t_ast *ast)
{
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	sh()->exit_status = 0;
	if (!ast->args[i])
		return (printf("\n"));
	if (!ft_strncmp(ast->args[i], "-n", 3))
	{
		new_line = false;
		i++;
	}
	while (ast->args[i])
	{
		printf("%s", ast->args[i++]);
		if (ast->args[i])
			printf(" ");
	}
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}
