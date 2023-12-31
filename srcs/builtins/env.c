/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:20:55 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/12/01 10:33:45 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	run_env(void)
{
	scanner_env(RESET);
	while (scanner_env(READ))
	{
		printf("%s=%s\n", scanner_env(READ)->key, scanner_env(READ)->value);
		scanner_env(NEXT);
	}
	return (EXIT_SUCCESS);
}

int	update_env_if_key_found(char *key, char *new_value)
{
	scanner_env(RESET);
	while (scanner_env(READ))
	{
		if (ft_strncmp(scanner_env(READ)->key, key, ft_strlen(key) + 1) == 0)
		{
			free(scanner_env(READ)->value);
			scanner_env(READ)->value = ft_strdup(new_value);
			return (EXIT_SUCCESS);
		}
		scanner_env(NEXT);
	}
	return (EXIT_FAILURE);
}
