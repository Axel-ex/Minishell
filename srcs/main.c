/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/26 12:07:58 by jgomes-v         ###   ########.fr       */
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
		signals(1);
		sh()->line = readline(PROMPT);
		if (!sh()->line)
			free_shell(false);
		if (!is_empty(sh()->line))
			add_history(sh()->line);
		if (parser() == EXIT_SUCCESS)
			executor();
		free_shell(true);
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
	return (sh()->exit_status);
}
