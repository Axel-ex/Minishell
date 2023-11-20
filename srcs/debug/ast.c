/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:46:22 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 11:06:10 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_ast_node(t_ast *node)
{
	int		i;
	char	*type;
	char	*color;
	char	*args;

	i = 0;
	if (!node)
		return ;
	type = get_type(node->token->type);
	color = NC;
	args = "";
	if (!ft_strncmp(type, "PIPE", 5))
	{
		color = CYAN;
		args = "";
	}
	printf("[%s%s%s]\tpos: %d\t%s", color, type, NC, node->pos, args);
	while (node->args[i])
	{
		printf("%s", node->args[i]);
		if (node->args[i + 1])
			printf(", ");
		i++;
	}
	printf("\n");
}

void	print_ast(t_ast *ast, int position)
{
	int	i;

	i = -1;
	if (!ast)
		return ;
	if (position == 0)
		printf("\n\n");
	print_ast(ast->right, position + 5);
	while (++i < position)
		printf(" ");
	i = -1;
	print_ast_node(ast);
	print_ast(ast->left, position + 5);
}
