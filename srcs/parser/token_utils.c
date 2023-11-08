/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:47:36 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 14:48:06 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_token_content(char *s)
{
	char	*content;
	int		size;
	int		i;

	size = 0;
	while (*s == ' ')
		s++;
	while (s[size] && s[size] != ' ' && size != MAX_TOKEN_LEN)
		size++;
	content = (char *)malloc(sizeof(char) * size + 1);
	if (!content)
		return (NULL);
	i = -1;
	while (++i < size)
		content[i] = s[i];
	content[++i] = '\0';
	return (content);
}

void	add_token(t_token **token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	new->next = NULL;
	(*token)->next = new;
}
