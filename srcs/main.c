/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/11 13:44:29 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

void	main_loop(t_shell *shell)
{
	char	*line;

	while (true)
	{
		line = readline("prompt> ");
		signals(1);
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
	//create_env(shell, getenv());
	main_loop(shell);
	free_shell(shell, false);
	return (EXIT_SUCCESS);
}
