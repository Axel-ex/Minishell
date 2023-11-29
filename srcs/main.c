/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/29 10:20:13 by achabrer         ###   ########.fr       */
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
		if (!is_empty(sh()->line))
			add_history(sh()->line);
		if (parser() != EXIT_FAILURE)
			executor();
		free_shell(true);
		print_ast(sh()->ast, 0);
	}
	clear_history();
	free_shell(false);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	init_shell(envp);
	main_loop();
	return (EXIT_SUCCESS);
}
