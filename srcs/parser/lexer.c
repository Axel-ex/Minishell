/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 15:00:28 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_token(char *line)
{
	t_token	*token;
	t_token	*origin;

	if (!line)
	{
		print_error("fail tokenizing: line is empty.");
		return (NULL);
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	origin = token;
	while (*line)
	{
		while (*line == ' ')
			line++;
		token->content = get_token_content(line);
		// token->type = get_token_type(token->content);
		token->len = ft_strlen(token->content);
		add_token(&token);
		line += token->len;
		token = token->next;
	}
	return (origin);
}
