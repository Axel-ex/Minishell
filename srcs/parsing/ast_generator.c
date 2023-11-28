/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_generator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 10:35:35 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/28 17:14:17 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	extend_cmd(t_ast *cmd)
{
	t_ast	*redir;

	redir = new_ast_node(token_dup(scanner(READ)));
	if (!redir)
		return ;
	scanner(NEXT);
	redir->args = matrix_append(redir->args, ft_strdup(scanner(READ)->content));
	redir->left = cmd->left;
	cmd->left = redir;
}

t_ast	*parse_cmd(void)
{
	t_ast	*cmd;

	cmd = new_ast_node(token_dup(scanner(READ)));
	if (!cmd)
		return (NULL);
	cmd->pos = sh()->nb_cmds++;
	while (scanner(READ) && scanner(READ)->type != PIPE)
	{
		if (scanner(READ)->type >= REDIR_IN
			&& scanner(READ)->type <= REDIR2_OUT)
			extend_cmd(cmd);
		else
			cmd->args = matrix_append(cmd->args,
					ft_strdup(scanner(READ)->content));
		scanner(NEXT);
	}
	return (cmd);
}

t_ast	*extend_pipe(t_ast *ast, t_ast *new_cmd)
{
	t_ast	*root;

	root = new_ast_node(new_token(ft_strdup("|"), PIPE));
	if (!root)
		return (NULL);
	root->left = ast;
	root->right = new_cmd;
	return (root);
}

void	ast_generator(void)
{
	t_ast	*cmd;

	scanner(RESET);
	sh()->ast = parse_cmd();
	cmd = NULL;
	while (scanner(READ) && scanner(READ)->type == PIPE)
	{
		scanner(NEXT);
		cmd = parse_cmd();
		sh()->ast = extend_pipe(sh()->ast, cmd);
	}
}
