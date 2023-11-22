/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 15:02:05 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/22 09:28:53 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_token(t_token *token)
{
	if (!token)
		return ;
	free(token->content);
	free(token);
}

void	free_matrix(char **matrix)
{
	int	i;

	if (!matrix || !*matrix)
		return ;
	i = -1;
	while (matrix[++i])
		free(matrix[i]);
	free(matrix);
}

void	free_ast(t_ast *ast)
{
	if (!ast)
		return ;
	free_ast(ast->left);
	free_ast(ast->right);
	free_token(ast->token);
	free_matrix(ast->args);
	free(ast);
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
	free(sh()->line);
	free_ast(sh()->ast);
	free_pipes(sh()->pipes);
	sh()->token_lst = NULL;
	sh()->ast = NULL;
	sh()->pipes = NULL;
	sh()->nb_cmds = 0;
	if (!keep_iterating)
	{
		ft_lstclear(&sh()->env_lst, (void (*))free_env_lst);
		free_matrix(sh()->path);
		exit(EXIT_SUCCESS);
	}
}
