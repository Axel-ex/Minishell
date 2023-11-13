/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:57:11 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 15:17:52 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_type(t_type type)
{
	if (type == PIPE)
		return ("PIPE");
	else if (type == REDIR_IN)
		return ("<");
	else if (type == REDIR_OUT)
		return (">");
	else if (type == REDIR2_IN)
		return ("<<");
	else if (type == REDIR2_OUT)
		return (">>");
	else
		return ("OTHER");
}

void	print_token_content(t_token *token)
{
	char	*type;

	type = get_type(token->type);
	printf("content: %s\t\t|| type: %s\n", token->content, type);
}

void	print_token_lst(void)
{
	scanner(RESET);
	printf("\n");
	while (scanner(READ))
	{
		print_token_content(scanner(READ));
		scanner(NEXT);
	}
	printf("\n");
}
