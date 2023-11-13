/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:46:22 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 15:20:33 by achabrer         ###   ########.fr       */
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
	color = NC;
	args = "args:";
	type = get_type(node->token->type);
	if (!ft_strncmp(type, "PIPE", 5))
	{
		color = CYAN;
		args = "";
	}
	printf("[%s%s%s]\t%s\t", color, type, NC, args);
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
