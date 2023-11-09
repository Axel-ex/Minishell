/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 12:20:49 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_new_token(t_token *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->next = NULL;
	token->next = new;
}

bool	is_command(char *token_content, char **path)
{
	int		i;
	char	*cmd1;
	char	*cmd2;

	i = 0;
	while (path[i])
	{
		cmd1 = ft_strjoin(path[i], "/");
		cmd2 = ft_strjoin(cmd1, token_content);
		if (!access(cmd2, X_OK))
		{
			free(cmd1);
			free(cmd2);
			return (true);
		}
		free(cmd1);
		free(cmd2);
		i++;
	}
	return (false);
}
