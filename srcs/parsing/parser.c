/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:50:54 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/24 10:06:45 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_enclosed_quotes(char *line)
{
	return (count_quotes(line) % 2 != 0);
}

bool	is_empty(char *line)
{
	if (!line)
		return (true);
	if (*line == '\0' || *line == '\n' || *line == '\t')
		return (true);
	return (false);
}

static int	syntax_checker(void)
{
	t_token	*next;
	t_token	*last;

	scanner(RESET);
	if (scanner(READ)->type != OTHER)
		return (print_error(ERR_SYNTHAX, SYNTH_ERR_TOKEN,
				scanner(READ)->content));
	while (scanner(READ))
	{
		next = scanner(GET_NEXT);
		if (scanner(READ)->type != OTHER && next && next->type != OTHER
			&& scanner(READ)->type != SIMPLE_QUOTE
			&& next->type != SIMPLE_QUOTE)
			return (print_error(ERR_SYNTHAX, SYNTH_ERR_TOKEN,
					scanner(READ)->content));
		last = scanner(READ);
		scanner(NEXT);
	}
	if (last->type != OTHER && last->type != SIMPLE_QUOTE)
		return (print_error(ERR_SYNTHAX, SYNTH_ERR_TOKEN, last->content));
	return (EXIT_SUCCESS);
}

void	trim_ast_content(t_ast *ast)
{
	char	*new_content;
	int		i;

	if (!ast)
		return ;
	trim_ast_content(ast->left);
	trim_ast_content(ast->right);
	i = 0;
	while (ast->args[i])
	{
		new_content = remove_quotes(ast->args[i]);
		free(ast->args[i]);
		ast->args[i] = new_content;
		i++;
	}
}

int	parser(void)
{
	if (is_empty(sh()->line))
		return (EXIT_FAILURE);
	if (has_enclosed_quotes(sh()->line))
		return (print_error(ERR_SYNTHAX, ERR_UNCLOSED_QUOTES, NULL));
	get_token(sh()->line);
	if (syntax_checker() != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	expander();
	ast_generator();
	trim_ast_content(sh()->ast);
	return (EXIT_SUCCESS);
}
