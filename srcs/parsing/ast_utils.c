/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:39:40 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 14:48:23 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*new_node;

	new_node = (t_ast *)malloc(sizeof(t_ast));
	new_node->args = (char **)malloc(sizeof(char *));
	if (!new_node || !new_node->args)
		return (alloc_error("new ast node"));
	new_node->token = token;
	return (new_node);
}

static int	get_matrix_len(char **matrix)
{
	int	len;

	len = 0;
	while (matrix[len])
		len++;
	return (len);
}

char	**matrix_append(char **matrix, char *to_append)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **)malloc(sizeof(char *) * (get_matrix_len(matrix)+ 2));
	if (!new)
		return (alloc_error("new matrix"));
	while (matrix[i])
	{
		new[i] = ft_strdup(matrix[i]);
		i++;
	}
	new[i] = to_append;
	new[i + 1] = NULL;
	free_matrix(matrix);
	return (new);
}
