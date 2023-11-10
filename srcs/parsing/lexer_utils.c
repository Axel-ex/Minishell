/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 12:11:35 by achabrer         ###   ########.fr       */
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
