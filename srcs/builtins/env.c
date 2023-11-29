/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:20:55 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/29 16:40:08 by jgomes-v         ###   ########.fr       */
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
