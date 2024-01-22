/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/22 11:37:01 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_token(char *line)
{
	char	*content;
	t_type	type;

	while (*line)
	{
		while (*line == ' ')
			line++;
		if (!*line)
			break ;
		content = get_token_content(line);
		type = get_token_type(content);
		line += ft_strlen(content);
		token_add_back(content, type);
	}
}

char	*get_token_content(char *line)
{
	int		i;

	i = 0;
	if (line[i] == '>' || line[i] == '<' || line[i] == '|')
		return (get_operator(line));
	else if (line[i] == '\'' || line[i] == '\"')
		return (get_quoted_content(line));
	else
		return (get_other(line));
}

t_type	get_token_type(char *token_content)
{
	if (!ft_strncmp("|", token_content, 2))
		return (PIPE);
	if (!ft_strncmp("<", token_content, 2))
		return (REDIR_IN);
	if (!ft_strncmp(">", token_content, 2))
		return (REDIR_OUT);
	if (!strncmp("<<", token_content, 3))
		return (HEREDOC);
	if (!strncmp(">>", token_content, 3))
		return (REDIR2_OUT);
	if (!strncmp("\'", token_content, 1))
		return (SIMPLE_QUOTE);
	else
		return (OTHER);
}

char	*get_quoted_content(char *line)
{
	char	*res;
	int		last_quote_pos;

	last_quote_pos = get_last_quote_pos(line);
	res = (char *)malloc(sizeof(char) * last_quote_pos + 2);
	if (!res)
		return (alloc_error("quoted content"));
	ft_strlcpy(res, line, last_quote_pos + 2);
	return (res);
}

char	*get_other(char *line)
{
	bool	in_quotes;
	char	quote;
	char	*res;
	int		i;

	in_quotes = false;
	quote = get_first_quote(line);
	i = -1;
	while (line[++i])
	{
		if (line[i] == quote)
		{
			if (!in_quotes)
				in_quotes = true;
			else
				in_quotes = false;
		}
		if ((line[i] == ' ' || line[i] == '>' || line[i] == '<'
				|| line[i] == '|') && !in_quotes)
			break ;
	}
	res = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(res, line, i + 1);
	return (res);
}
