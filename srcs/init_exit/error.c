/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:13 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/14 14:05:12 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(int exit_status, char *msg, char *var)
{
	sh()->exit_status = exit_status;
	printf("%sError%s: ", RED, NC);
	if (var)
		printf("%s: ", var);
	printf("%s\n", msg);
	return (EXIT_FAILURE);
}

void	*alloc_error(char *msg)
{
	printf("%s: failed to allocate", msg);
	return (NULL);
}
