/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:57:11 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/09 11:07:01 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_content(t_token **token)
{
	int		i;
	t_token	*curr;

	i = -1;
	while (token[++i])
	{
		curr = token[i];
		while (curr)
		{
			printf("content: %s\n", curr->content);
			curr = curr->next;
		}
	}
}
