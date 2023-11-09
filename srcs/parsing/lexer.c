/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 12:27:19 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*get_token(char *line, char **path)
{
	t_token	*token;
	t_token	*origin;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (alloc_error("token"));
	origin = token;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		token->content = get_token_content(line);
		token->type = get_token_type(token->content, path);
		line += ft_strlen(token->content);
		while (*line == ' ')
			line++;
		if (*line)
		{
			add_new_token(token);
			token = token->next;
		}
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
		return (alloc_error("token content"));
	i = -1;
	while (++i < size)
		content[i] = s[i];
	content[++i] = '\0';
	return (content);
}

t_type	get_token_type(char *token_content, char **path)
{
	if (is_command(token_content, path))
		return (CMD);
	if (ft_strncmp("|", token_content, 2))
		return (PIPE);
	if (ft_strncmp("<", token_content, 2))
		return (REDIR_IN);
	if (ft_strncmp(">", token_content, 2))
		return (REDIR_OUT);
	else
		return (FILE_NAME);
}
