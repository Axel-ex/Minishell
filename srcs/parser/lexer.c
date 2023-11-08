/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 15:48:03 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_token(char *line)
{
	t_token	*token;
	t_token	*origin;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	origin = token;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		add_new_token(token);
		token->content = get_token_content(line);
		// token->type = get_token_type(token->content);
		token->len = ft_strlen(token->content);
		line += token->len;
		token = token->next;
	}
	return (origin);
}

char	*get_token_content(char *s)
{
	char	*content;
	int		size;
	int		i;

	size = 0;
	while (s[size] && s[size] != ' ' && size != MAX_TOKEN_LEN)
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		return (NULL);
	i = -1;
	while (++i < size)
		content[i] = s[i];
	content[++i] = '\0';
	return (content);
}
