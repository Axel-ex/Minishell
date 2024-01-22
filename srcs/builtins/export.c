/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:57:01 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/22 11:40:11 by achabrer         ###   ########.fr       */
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

void	validate_identifier(t_ast *ast)
{
	int	i;

	i = 0;
	if (ast->args[1][i] == '=' && ast->args[1][i + 1] == '\0')
		print_error_export(1, "not a valid identifier\n", "export",
			ast->args[1]);
	while (ast->args[1][i] != '\0' && ast->args[1][i] != '=')
	{
		if ((i == 0 && !ft_isalpha(ast->args[1][i]) && ast->args[1][i] != '_')
			||
			(i > 0 && !ft_isalpha(ast->args[1][i]) && ast->args[1][i] != '_'
					&& !ft_isdigit(ast->args[1][i])))
		{
			print_error_export(1, "not a valid identifier\n", "export",
				ast->args[1]);
			return ;
		}
		i++;
	}
}

void	handle_export_with_equal(t_list *to_add, t_ast *ast)
{
	((t_env *)to_add->content)->value = get_value(ast->args[1]);
	((t_env *)to_add->content)->key = get_key(ast->args[1]);
	env_add_back(((t_env *)to_add->content)->key,
		((t_env *)to_add->content)->value);
}

void	handle_export_without_equal(t_list *to_add, t_ast *ast)
{
	t_env	*existing_var;

	existing_var = env_find(ast->args[1]);
	if (existing_var == NULL)
	{
		((t_env *)to_add->content)->value = ft_strdup("");
		((t_env *)to_add->content)->key = ft_strdup(ast->args[1]);
		env_add_back(((t_env *)to_add->content)->key,
			((t_env *)to_add->content)->value);
	}
}

void	run_export(t_ast *ast)
{
	t_list	*to_add;

	if (!ast->args[1])
	{
		print_all_export();
		return ;
	}
	if (sh()->nb_cmds > 1)
		return ;
	validate_identifier(ast);
	to_add = (t_list *)malloc(sizeof(t_list));
	to_add->content = malloc(sizeof(t_env));
	if (ft_strchr(ast->args[1], '=') != NULL)
		handle_export_with_equal(to_add, ast);
	else
		handle_export_without_equal(to_add, ast);
	free(to_add->content);
	free(to_add);
}
