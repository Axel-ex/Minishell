/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:45:38 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 12:54:31 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	init_shell(void)
{
	ft_bzero(sh(), sizeof(t_shell));
	sh()->path = ft_split(getenv("PATH"), ':');
	sh()->exit_status = 0;
}
