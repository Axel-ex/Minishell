/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:13 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/10 14:30:07 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(char *msg, int exit_status)
{
	g_exit_status = exit_status;
	printf("%sError%s:\t%s\n", RED, NC, msg);
	return (EXIT_FAILURE);
}

void	*alloc_error(char *msg)
{
	printf("%s: failed to allocate", msg);
	return (NULL);
}
