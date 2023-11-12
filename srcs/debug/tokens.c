/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 08:57:11 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 16:16:26 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_token_content(void)
{
	scanner(RESET);

	while (scanner(READ))
	{
		printf("content: %s\n", scanner(READ)->content);
		scanner(NEXT);
	}
}
