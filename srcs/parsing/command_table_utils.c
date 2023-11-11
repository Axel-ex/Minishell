/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_table_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 11:27:21 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/11 11:28:56 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*remove_quotes(char *token_content)
{
	char	*trimmed;
	int		start;
	int		end;
	int		i;
	char	quote;

	start = 0;
	end = ft_strlen(token_content) - 1;
	quote = *token_content;
	while (token_content[start] && token_content[start] == quote)
		start++;
	while (end >= 0 && (token_content[end] == quote))
		end--;
	trimmed = (char *)malloc(sizeof(char) * end - start + 1);
	if (!trimmed)
		return (alloc_error("trimmed token"));
	i = 0;
	while (start <= end)
		trimmed[i++] = token_content[start++];
	trimmed[i] = '\0';
	return (trimmed);
}

void	trim_token(t_token *token_lst)
{
	t_token	*curr;
	char	*buf;


	curr = token_lst;
	while (curr)
	{
		if (token_lst->type == OTHER && count_quotes(token_lst->content))
		{
			buf = token_lst->content;
			token_lst->content = remove_quotes(token_lst->content);
			free(buf);
		}
		curr = curr->next;
	}
}