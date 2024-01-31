/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 14:47:53 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/23 10:21:53 by achabrer         ###   ########.fr       */
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

void	token_add_back(char *content, t_type type, int count_space)
{
	static t_type	last_type = PIPE;
	t_token			*new;

	if (!count_space && sh()->token_lst
		&& !get_operator(content) && !is_operator(last_type))
	{
		token_content_append(content);
		return ;
	}
	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return ;
	new->content = content;
	new->type = type;
	last_type = type;
	ft_lstadd_back(&sh()->token_lst, ft_lstnew(new));
}

void	token_content_append(char *to_append)
{
	t_token	*last;
	char	*new_content;
	int		curr_size;
	int		new_size;

	last = ft_lstlast(sh()->token_lst)->content;
	curr_size = ft_strlen(last->content);
	new_size = curr_size + ft_strlen(to_append) + 1;
	new_content = ft_calloc(sizeof(char), new_size);
	if (!new_content)
		return ;
	ft_strlcpy(new_content, last->content, ft_strlen(last->content) + 1);
	ft_strlcpy(new_content + curr_size, to_append, ft_strlen(to_append) + 1);
	free(last->content);
	last->content = new_content;
}
