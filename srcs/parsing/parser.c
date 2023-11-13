/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:50:54 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 15:52:22 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	has_enclosed_quotes(char *line)
{
	return (count_quotes(line) % 2 != 0);
}

static bool	is_empty(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n' && *line != '\t')
			return (false);
		line++;
	}
	return (true);
}

static int	syntax_checker(void)
{
	t_token	*next;
	t_token	*last;

	scanner(RESET);
	if (scanner(READ)->type != OTHER)
		return (print_error(ERR_OPERATOR_BEGIN, SYNTAX_ERROR));
	while (scanner(READ))
	{
		next = scanner(GET_NEXT);
		if (scanner(READ)->type != OTHER && next && next->type != OTHER)
			return (print_error(ERR_TOKEN_SEQ, SYNTAX_ERROR));
		last = scanner(READ);
		scanner(NEXT);
	}
	if (last->type != OTHER)
		return (print_error(ERR_OPERATOR_END, SYNTAX_ERROR));
	return (EXIT_SUCCESS);
}

int	parser(void)
{
	if (has_enclosed_quotes(sh()->line))
		return (print_error(ERR_UNCLOSED_QUOTES, 2));
	if (is_empty(sh()->line))
		return (EXIT_FAILURE);
	get_token(sh()->line);
	syntax_checker();
	//expander
	//trim_token
	ast_generator();
	return (EXIT_SUCCESS);
}
