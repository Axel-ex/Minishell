/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 17:14:39 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


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

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;

	(void)argc;
	(void)argv;
	shell = init_shell(envp);
	main_loop(shell);
	free_shell(shell, false);
	return (EXIT_SUCCESS);
}
