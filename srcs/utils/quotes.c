/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2024/02/14 13:40:57 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_quotes(char *line)
{
	int		quotes;
	int		in_squote;
	int		in_dquote;

	quotes = 0;
	in_squote = 0;
	in_dquote = 0;
	while (*line)
	{
		if (*line == '\'' && in_dquote == 0)
		{
			in_squote = 1 - in_squote;
			quotes++;
		}
		else if (*line == '"' && in_squote == 0)
		{
			in_dquote = 1 - in_dquote;
			quotes++;
		}
		line++;
	}
	return (quotes);
}

char	get_first_quote(char *line)
{
	while (*line)
	{
		if (*line == '\'' || *line == '\"')
			return (*line);
		line++;
	}
	return (*line);
}

int	get_last_quote_pos(char *line)
{
	int		i;
	char	quote;
	int		pos;
	int		quotes_count;

	quotes_count = 0;
	quote = get_first_quote(line);
	pos = 0;
	i = -1;
	while (line[++i])
	{
		if (line[i] == quote)
		{
			pos = i;
			quotes_count++;
		}
		if ((line[i] == ' ' || line[i] == '>' || line[i] == '<'
				|| line[i] == '|') && quotes_count % 2 == 0)
			break ;
	}
	return (pos);
}

bool	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (true);
	return (false);
}

char	*remove_quotes(char *cnt)
{
	char	*origin;
	char	*res;
	char	quote;

	origin = malloc(sizeof(char) * ft_strlen(cnt) + 1);
	if (!origin)
		return (NULL);
	res = origin;
	while (*cnt)
	{
		if (is_quote(*cnt))
		{
			quote = *cnt++;
			while (*cnt && *cnt != quote)
				*res++ = *cnt++;
			if (*cnt)
				cnt++;
		}
		else
			*res++ = *cnt++;
	}
	*res = '\0';
	return (origin);
}
