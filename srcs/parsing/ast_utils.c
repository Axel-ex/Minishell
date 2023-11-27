/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:39:40 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/27 13:53:12 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_ast	*new_ast_node(t_token *token)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	if (!new_node)
		return (alloc_error("new ast node"));
	new_node->args = ft_calloc(1, sizeof(char *));
	if (!new_node->args)
		return (alloc_error("args of new ast node"));
	new_node->token = token;
	new_node->pos = 0;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

int	get_matrix_len(char **matrix)
{
	int	len;

	if (!matrix)
		return (0);
	len = 0;
	while (matrix[len])
		len++;
	return (len);
}

char	**matrix_append(char **matrix, char *to_append)
{
	int		i;
	char	**new;

	i = -1;
	new = ft_calloc(get_matrix_len(matrix) + 2, sizeof(char *));
	if (!new)
		return (alloc_error("new matrix"));
	while (matrix[++i])
		new[i] = ft_strdup(matrix[i]);
	new[i] = to_append;
	free_matrix(matrix);
	return (new);
}
