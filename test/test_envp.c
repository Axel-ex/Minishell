/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 17:55:22 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 18:02:59 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	j;

	(void)argc;
	(void)argv;
	i = -1;
	while (envp[++i])
		printf("%s\n", envp[i]);
	return (0);
}
