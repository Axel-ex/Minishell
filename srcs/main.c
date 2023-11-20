/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 14:23:44 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_shell	*sh(void)
{
	static t_shell	sh;

	return (&sh);
}

static void	main_loop(void)
{
	while (42)
	{
		sh()->line = readline(PROMPT);
		// signals(1);
		add_history(sh()->line);
		parser();
		executor();
		free_shell(true);
	}
	clear_history();
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_shell(envp);
	main_loop();
	return (EXIT_SUCCESS);
}
