/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:02:05 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 15:33:44 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_token(t_token *token)
{
	if (!token)
		return (NULL);
	free(token->content);
	free(token);
	return (NULL);
}

void	free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	free_shell(bool keep_iterating)
{
	ft_lstclear(&sh()->token_lst, (void (*))free_token);
	free(sh()->line);
	if (!keep_iterating)
	{
		free_matrix(sh()->path);
	}
}
