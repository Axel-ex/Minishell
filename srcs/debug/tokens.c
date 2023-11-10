/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:57:11 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 10:16:33 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_content(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		ft_printf("%d Content: %s\n", token->content);
		token = token->next;
		i++;
	}
}
