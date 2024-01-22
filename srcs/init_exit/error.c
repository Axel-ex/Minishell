/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:13 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/22 11:48:00 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_error(int exit_status, char *msg, char *var)
{
	ft_putstr_fd("minishell: ", 2);
	if (var && exit_status != ERR_SYNTHAX)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	if (var && exit_status == ERR_SYNTHAX)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(var, 2);
	}
	ft_putstr_fd("\n", 2);
	sh()->exit_status = exit_status;
	return (sh()->exit_status);
}

void	*alloc_error(char *msg)
{
	printf("%s: failed to allocate", msg);
	return (NULL);
}

int	print_error_export(int exit_status, char *msg, char *var, char *arg)
{
	sh()->exit_status = exit_status;
	ft_putstr_fd("minishell: ", 2);
	if (var && exit_status != ERR_SYNTHAX)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	return (sh()->exit_status);
}
