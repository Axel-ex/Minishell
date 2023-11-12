/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:43:30 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	token_add_back(char *content, t_type type)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->content = content;
	new->type = type;
	ft_lstadd_back(&sh()->token_lst, ft_lstnew(new));
}

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

char	*get_token_content(char *s)
{
	char	*content;
	int		size;
	int		i;

	size = 0;
	if (is_operator(s[size]))
		return (get_operator(s));
	else if (s[size] == '\"' || s[size] == '\'')
		while (s[size] && !is_operator(s[size])
			&& (s[size] != '\"' || s[size] != '\''))
			size++;
	else
		while (s[size] && s[size] != ' ' && !is_operator(s[size])
			&& size != MAX_TOKEN_LEN)
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
