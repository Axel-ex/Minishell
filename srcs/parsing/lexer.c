/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:47:31 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 16:39:28 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	get_token(t_shell *shell, char *line)
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
		add_back_token(&shell->token, content, type);
	}
}

char	*get_token_content(char *s)
{
	char	*content;
	int		size;
	int		i;

	size = 0;
	if (s[size] == '|' || s[size] == '>' || s[size] == '<')
		return (get_operator(s));
	if (s[size] == '\"' || s[size] == '\'')
		while (s[size] && (s[size] != '\"' || s[size] != '\''))
			size++;
	else
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
