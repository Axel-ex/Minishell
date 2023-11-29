/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:57:01 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/29 18:36:10 by jgomes-v         ###   ########.fr       */
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
	t_list	*to_add;

	if (!ast->args[1])
	{
		print_all_export();
		return ;
	}
	if (!ft_isalpha(ast->args[1][0]))
		ft_printf("export: `%c': not a valid identifier\n", ast->args[1][0]);

	if (ft_strchr(ast->args[1], '=') != NULL)
	{
		to_add = (t_list *)malloc(sizeof(t_list));
		to_add->content = malloc(sizeof(t_env));
		((t_env *)to_add->content)->value = get_value(ast->args[1]);
		((t_env *)to_add->content)->key = get_key(ast->args[1]);
		env_add_back(((t_env *)to_add->content)->key,
				((t_env *)to_add->content)->value);
		free(to_add->content);		
		free(to_add);
	}
}
