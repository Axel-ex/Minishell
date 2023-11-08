/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:34:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 15:28:13 by achabrer         ###   ########.fr       */
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
		if (!ft_strncmp("quit", line, 4))
		{
			free(line);
			break ;
		}
		shell->token = get_token(line);
		// while (shell->token)
		// {
		// 	ft_printf("%s\n", shell->token->content);
		// 	shell->token = shell->token->next;
		// }
		free (line);
	}
	free_shell(shell);
	return (EXIT_SUCCESS);
}
