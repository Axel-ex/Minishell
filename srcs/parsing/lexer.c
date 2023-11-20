/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 10:55:22 by achabrer         ###   ########.fr       */
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
		return (REDIR2_IN);
	if (!strncmp(">>", token_content, 3))
		return (REDIR2_OUT);
	else
		return (OTHER);
}

char	*get_quoted_content(char *line)
{
	char	*res;
	char	quote;
	int		i;

	quote = line[0];
	i = 1;
	while (line[i] != quote)
		i++;
	res = (char *)malloc(sizeof(char) * i + 2);
	if (!res)
		return (alloc_error("quoted content"));
	ft_strlcpy(res, line, i + 2);
	return (res);
}

char	*get_other(char *line)
{
	bool	in_quotes;
	char	quote;
	char	*res;
	int		i;

	in_quotes = false;
	quote = '\0';
	i = -1;
	while (line[++i] && line[i] != quote)
	{
		if (line[i] == '\"' || line[i] == '\'')
		{
			quote = line[i];
			in_quotes = true;
		}
		if ((line[i] == ' ' || line[i] == '>' || line[i] == '<'
				|| line[i] == '|') && !in_quotes)
			break ;
	}
	if (quote != '\0')
		i++;
	res = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(res, line, i + 1);
	return (res);
}

