/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:44:42 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/21 17:04:39 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_pipes(int **pipes)
{
	int	i;

	if (!pipes || !*pipes)
		return ;
	i = -1;
	while (++i < sh()->nb_cmds - 1)
		free(pipes[i]);
	free(pipes);
}

// void	free_ast_node(t_ast *ast)
// {
// 	free_token(ast->token);
// 	free_matrix(ast->args);
// }

// void	free_ast(t_ast *ast, void (*del)(t_ast *))
// {
// 	if (!ast)
// 		return ;
// 	free_ast(ast->left, del);
// 	free_ast(ast->right, del);
// 	del(ast);
// 	free(ast);
// }