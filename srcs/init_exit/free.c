/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:02:05 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 17:17:47 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tokens(t_token	*token)
{
	t_token	*curr;
	t_token	*buf;

	curr = token;
	while (curr)
	{
		buf = curr;
		curr = curr->next;
		free(buf->content);
		free(buf);
	}
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_shell(t_shell *shell, bool keep_iterating)
{

	free_tokens(shell->token);
	if (!keep_iterating)
	{
		free_matrix(shell->path);
		free(shell);
	}
}
