/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 17:26:57 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_command(char *token_content, char **path)
{
	int		i;
	char	*cmd2;
	char	*cmd;

	i = 0;
	while (path[i])
	{
		cmd2 = ft_strjoin(path[i], "/");
		cmd = ft_strjoin(cmd2, token_content);
		free(cmd2);
		if (!access(cmd, X_OK))
		{
			free(cmd);
			return (true);
		}
		free(cmd);
		i++;
	}
	return (false);
}

void	add_back_token(t_token **token_lst, char *content, t_type type)
{
	t_token	*new;
	t_token	*curr;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->content = content;
	new->type = type;
	new->next = NULL;
	if (!token_lst || !*token_lst)
		*token_lst = new;
	else
	{
		curr = *token_lst;
		while (curr->next)
			curr = curr->next;
		curr->next = new;
	}
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
	if (!ft_strncmp(">", s, 1))
		return (ft_alloc_fill(1, '<'));
	if (!ft_strncmp("|", s, 1))
		return (ft_alloc_fill(1, '|'));
	else
		return (NULL);
}
