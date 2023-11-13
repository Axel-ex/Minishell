/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 14:31:57 by achabrer         ###   ########.fr       */
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
		sh()->line = readline("prompt> ");
		// signals(1);
		add_history(sh()->line);
		parser();
		if (!ft_strncmp(sh()->line, "exit", 4))
		{
			free_shell(false);
			break ;
		}
		print_ast(sh()->ast, 0);
		free_shell(true);
	}
	clear_history();
}

int	main(void)
{
	init_shell();
	//create_env(shell, getenv());
	main_loop();
	return (EXIT_SUCCESS);
}
