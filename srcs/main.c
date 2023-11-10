/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 14:33:03 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

static void	main_loop(t_shell *shell)
{
	char	*line;

	while (true)
	{
		line = readline("prompt> ");
		add_history(line);
		parser(shell, line);
		if (!ft_strncmp(line, "exit", 4))
		{
			free(line);
			break ;
		}
		free_shell(shell, true);
		free(line);
	}
	clear_history();
}

int	main(void)
{
	t_shell	*shell;

	shell = init_shell();
	main_loop(shell);
	free_shell(shell, false);
	return (EXIT_SUCCESS);
}
