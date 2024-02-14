/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:01:08 by achabrer          #+#    #+#             */
/*   Updated: 2024/02/14 13:51:19 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	skip_n(char *content)
{
	int	i;

	i = 1;
	while (content[i] && content[i] == 'n')
		i++;
	return (i);
}

static void	print_args(char	**args, int i)
{
	while (args[i])
	{
		if (!ft_strncmp(args[i], "~", 2))
		{
			ft_putstr_fd(getenv("HOME"), sh()->fd_out);
			i++;
		}
		else
			printf("%s", args[i++]);
		if (!is_empty(args[i]))
			printf(" ");
	}
}

int	run_echo(t_ast *ast)
{
	int		i;
	int		j;
	bool	new_line;

	i = 1;
	new_line = true;
	sh()->exit_status = 0;
	if (!ast->args[i])
		return (printf("\n"));
	if (!ft_strncmp(ast->args[i], "-n", 2))
	{
		new_line = false;
		j = skip_n(ast->args[i]);
		if (!ast->args[i][j])
			i++;
	}
	print_args(ast->args, i);
	if (new_line)
		printf("\n");
	return (EXIT_SUCCESS);
}
