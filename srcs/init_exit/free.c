/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:02:05 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/14 11:16:23 by achabrer         ###   ########.fr       */
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

void	free_ast(t_ast *ast)
{
	t_ast	*left;
	t_ast	*right;

	if (!ast)
		return ;
	free_token(ast->token);
	free_matrix(ast->args);
	left = ast->left;
	right = ast->right;
	free(ast);
	free_ast(left);
	free_ast(right);
}

void	free_env_lst(t_env *env_lst)
{
	free(env_lst->key);
	// free(env_lst->value);
	free(env_lst);
}

void	free_shell(bool keep_iterating)
{
	ft_lstclear(&sh()->token_lst, (void (*))free_token);
	ft_lstclear(&sh()->env_lst, (void (*))free_env_lst);
	free(sh()->line);
	free_ast(sh()->ast);
	if (!keep_iterating)
	{
		free_matrix(sh()->path);
	}
}
