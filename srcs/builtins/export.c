/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 14:57:01 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/23 19:22:20 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	print_all_export(void)
{
	t_list	*current;

	copy_env_list();
	sort_copy_env_list();
	current = sh()->copy_env_lst;
	while (current)
	{
		ft_printf("declare -x ");
		ft_printf("%s=", ((t_env *)current->content)->key);
		ft_printf("\"%s\"\n", ((t_env *)current->content)->value);
		current = current->next;
	}
	free_copy_env_lst();
	return (EXIT_SUCCESS);
}

void	validate_identifier(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
	{
		print_error_export(1, "not a valid identifier\n", "export", "`'");
		return ;
	}
	if (arg[i] == '=' && arg[i + 1] == '\0')
		print_error_export(1, "not a valid identifier\n", "export", arg);
	while (arg[i] != '\0' && arg[i] != '=')
	{
		if ((i == 0 && !ft_isalpha(arg[i]) && arg[i] != '_') || (i > 0
				&& !ft_isalpha(arg[i]) && arg[i] != '_' && !ft_isdigit(arg[i])))
		{
			print_error_export(1, "not a valid identifier\n", "export", arg);
			return ;
		}
		i++;
	}
}

void	handle_export_with_equal(t_list *to_add, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_pos;
	t_env	*existing_var;

	equal_pos = ft_strchr(arg, '=');
	*equal_pos = '\0';
	key = ft_strdup(arg);
	value = ft_strdup(equal_pos + 1);
	*equal_pos = '=';
	existing_var = env_find(key);
	if (existing_var)
	{
		free(existing_var->value);
		existing_var->value = value;
		free(key);
	}
	else
	{
		((t_env *)to_add->content)->key = key;
		((t_env *)to_add->content)->value = value;
		env_add_back(key, value);
	}
}

void	handle_export_without_equal(t_list *to_add, char *arg)
{
	t_env	*existing_var;

	existing_var = env_find(arg);
	if (existing_var == NULL)
	{
		((t_env *)to_add->content)->value = ft_strdup("");
		((t_env *)to_add->content)->key = ft_strdup(arg);
		env_add_back(((t_env *)to_add->content)->key,
			((t_env *)to_add->content)->value);
	}
}

void	run_export(t_ast *ast)
{
	t_list	*to_add;
	int		i;

	if (!ast->args[1])
	{
		print_all_export();
		return ;
	}
	if (sh()->nb_cmds > 1)
		return ;
	i = 1;
	while (ast->args[i])
	{
		validate_identifier(ast->args[i]);
		to_add = (t_list *)malloc(sizeof(t_list));
		to_add->content = malloc(sizeof(t_env));
		if (ft_strchr(ast->args[i], '=') != NULL)
			handle_export_with_equal(to_add, ast->args[i]);
		else
			handle_export_without_equal(to_add, ast->args[i]);
		free(to_add->content);
		free(to_add);
		i++;
	}
}
