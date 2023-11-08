/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 17:29:19 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	t_shell	*shell;

	shell = init_shell();
	while (true)
	{
		line = readline("prompt> ");
		if (!ft_strncmp("exit", line, 4))
		{
			free(line);
			break ;
		}
		shell->token = get_token(line, shell->path);
		free (line);
	}
	free_shell(shell);
	return (EXIT_SUCCESS);
}
