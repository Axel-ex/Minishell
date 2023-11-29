/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:50:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/29 11:41:07 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_enclosed_quotes(char *line)
{
	return (count_quotes(line) % 2 != 0);
}

bool	is_empty(char *line)
{
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
		return (print_error(SYNTAX_ERROR, ERR_OPERATOR_BEGIN,
				scanner(READ)->content));
	while (scanner(READ))
	{
		next = scanner(GET_NEXT);
		if (scanner(READ)->type != OTHER && next && next->type != OTHER)
			return (print_error(SYNTAX_ERROR, ERR_TOKEN_SEQ, NULL));
		last = scanner(READ);
		scanner(NEXT);
	}
	if (last->type != OTHER)
		return (print_error(SYNTAX_ERROR, ERR_OPERATOR_END, NULL));
	return (EXIT_SUCCESS);
}

void	trim_tokens(void)
{
	char	*quote;
	char	*new_content;

	quote = ft_calloc(sizeof(char), 2);
	scanner(RESET);
	while (scanner(READ))
	{
		*quote = scanner(READ)->content[0];
		if (*quote == '\'' || *quote == '\"')
		{
			new_content = ft_strtrim(scanner(READ)->content, quote);
			free(scanner(READ)->content);
			scanner(READ)->content = new_content;
		}
		scanner(NEXT);
	}
	free(quote);
}

int	parser(void)
{
	if (is_empty(sh()->line))
		return (EXIT_FAILURE);
	if (has_enclosed_quotes(sh()->line))
		return (print_error(SYNTAX_ERROR, ERR_UNCLOSED_QUOTES, NULL));
	get_token(sh()->line);
	if (syntax_checker() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	trim_tokens();
	expander();
	ast_generator();
	return (EXIT_SUCCESS);
}
