/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:47:53 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/18 08:55:05 by achabrer         ###   ########.fr       */
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

t_token	*new_token(char *content, t_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (alloc_error("new token"));
	token->content = content;
	token->type = type;
	return (token);
}

t_token	*token_dup(t_token *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (alloc_error("token dup ast"));
	new->content = ft_strdup(token->content);
	new->type = token->type;
	return (new);
}

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
