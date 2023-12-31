/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:50:54 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/05 12:31:34 by jgomes-v         ###   ########.fr       */
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
		return (print_error(SYNTAX_ERROR, SYNTH_ERR_TOKEN,
				scanner(READ)->content));
	while (scanner(READ))
	{
		next = scanner(GET_NEXT);
		if (scanner(READ)->type != OTHER && next && next->type != OTHER)
			return (print_error(SYNTAX_ERROR, SYNTH_ERR_TOKEN,
					scanner(READ)->content));
		last = scanner(READ);
		scanner(NEXT);
	}
	if (last->type != OTHER && last->type != SIMPLE_QUOTE)
		return (print_error(SYNTAX_ERROR, SYNTH_ERR_TOKEN, last->content));
	return (EXIT_SUCCESS);
}

void	trim_tokens(void)
{
	char	*new_content;

	scanner(RESET);
	while (scanner(READ))
	{
		new_content = remove_quotes(scanner(READ)->content);
		free(scanner(READ)->content);
		scanner(READ)->content = new_content;
		scanner(NEXT);
	}
}

int	parser(void)
{
	if (is_empty(sh()->line))
		return (EXIT_FAILURE);
	if (has_enclosed_quotes(sh()->line))
		return (print_error(SYNTAX_ERROR, ERR_UNCLOSED_QUOTES, NULL));
	get_token(sh()->line);
	if (syntax_checker() != EXIT_SUCCESS)
		return (sh()->exit_status);
	trim_tokens();
	expander();
	ast_generator();
	return (EXIT_SUCCESS);
}
