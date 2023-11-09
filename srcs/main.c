/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 12:52:49 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	t_shell	*shell;
	int		i;

	shell = init_shell();
	while (true)
	{
		line = readline("prompt> ");
		shell->lines = ft_split(line, ';');
		shell->token = init_token(shell->lines);
		i = -1;
		while (shell->lines[++i])
			shell->token[i] = get_token(shell->lines[i], shell->path);
		if (!ft_strncmp(shell->lines[0], "exit", 4))
		{
			free(line);
			break ;
		}
		free_shell(shell, true);
		free(line);
	}
	free_shell(shell, false);
	return (EXIT_SUCCESS);
}
