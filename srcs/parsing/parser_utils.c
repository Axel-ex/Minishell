/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/12/11 14:16:05 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*scanner(t_operation op)
{
	static t_list	*curr = NULL;

	if (op == RESET)
		curr = sh()->token_lst;
	else if (op == READ && curr)
		return (curr->content);
	else if (op == NEXT && curr)
		curr = curr->next;
	else if (op == GET_NEXT && curr->next)
		return (curr->next->content);
	return (NULL);
}

char	*get_operator(char *s)
{
	if (!ft_strncmp(">>", s, 2))
		return (ft_alloc_fill(2, '>'));
	if (!ft_strncmp("<<", s, 2))
		return (ft_alloc_fill(2, '<'));
	if (!ft_strncmp(">", s, 1))
		return (ft_alloc_fill(1, '>'));
	if (!ft_strncmp("<", s, 1))
		return (ft_alloc_fill(1, '<'));
	if (!ft_strncmp("|", s, 1))
		return (ft_alloc_fill(1, '|'));
	else
		return (NULL);
}

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

char	*remove_quotes(char *content)
{
	char	*res;
	char	quote;
	int		i;
	int		j;
	int		count;

	quote = get_first_quote(content);
	i = -1;
	count = 0;
	while (content[++i])
		if (content[i] == quote)
			count++;
	res = ft_calloc(sizeof(char), i - count + 1);
	i = 0;
	j = 0;
	while (content[i])
	{
		if (content[i] == quote)
			i++;
		res[j++] = content[i++];
	}
	res[j] = '\0';
	return (res);
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
