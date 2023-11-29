/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:57:01 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/29 16:37:51 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_all_export(void)
{
	scanner_env(RESET);
	while (scanner_env(READ))
	{
		ft_printf("declare -x ");
		ft_printf("%s=", scanner_env(READ)->key);
		ft_printf("\"%s\"\n", scanner_env(READ)->value);
		scanner_env(NEXT);
	}
	return (EXIT_SUCCESS);
}

void	run_export(t_ast *ast)
{
	if (!ast->args[1])
		print_all_export();
}