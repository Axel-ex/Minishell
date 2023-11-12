/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:34:57 by achabrer         ###   ########.fr       */
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
	else if (op == NEXT)
		curr = curr->next;
	else if (op == GET_NEXT && curr->next)
		return (curr->next->content);
	return (NULL);
}

static char	*ft_alloc_fill(int size, char to_fill)
{
	char	*res;
	int		i;

	i = 0;
	res = (char *)malloc(sizeof(char) * size + 1);
	if (!res)
		return (alloc_error("operator token"));
	while (i < size)
		res[i++] = to_fill;
	res[i] = '\0';
	return (res);
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

bool	is_operator(char c)
{
	if (c == '|' || c == '>' || c == '<')
		return (true);
	return (false);
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