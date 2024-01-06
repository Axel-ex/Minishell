/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:13 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/05 17:24:47 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(int exit_status, char *msg, char *var)
{
	dup2(STDERR_FILENO, STDOUT_FILENO);
	sh()->exit_status = exit_status;
	// printf("%sminishell%s: ", RED, NC);
	if (var && exit_status != SYNTAX_ERROR)
		printf("%s: ", var);
	printf("%s", msg);
	if (var && exit_status == SYNTAX_ERROR)
		printf(": %s", var);
	return (sh()->exit_status);
}

void	*alloc_error(char *msg)
{
	printf("%s: failed to allocate", msg);
	return (NULL);
}
