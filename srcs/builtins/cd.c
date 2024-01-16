/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:46:48 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/16 16:10:11 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//	here really needs to be with cwd i tired geten_var but i was always getting the following path
// PWD=/Users/jota/Desktop/Repos/Minishell
// i bealieve the PWD of envv is not being correctly updated going to work on it later

int	cd_update_old_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE);
	oldpwd = ft_strdup(cwd);
	if (!oldpwd)
		return (EXIT_FAILURE);
	update_env_if_key_found("OLDPWD", oldpwd);
	free(oldpwd);
	return (EXIT_SUCCESS);
}

int	cd_goto_old_pwd(void)
{
	char	*oldpwd_path;

	oldpwd_path = getenv_var("OLDPWD");
	if (!oldpwd_path)
	{
		ft_printf("%s", "minishell : cd: OLDPWD not set\n");
		return (EXIT_FAILURE);
	}
	if (chdir(oldpwd_path) == 0)
	{
		ft_printf("%s", "minishell : cd: error changing directory\n");
		return (EXIT_FAILURE);
	}
	cd_update_old_pwd();
	return (EXIT_SUCCESS);
}

int	cd_goto_home(void)
{
	cd_update_old_pwd();
	chdir(getenv_var("HOME"));
	return (EXIT_SUCCESS);
}

int	run_cd(t_ast *ast)
{
	if (!ast->args[1])
		return (cd_goto_home());
	if (ft_strncmp(ast->args[1], "-", 2) == 0)
		cd_goto_old_pwd();
	else
	{
		if (chdir(ast->args[1]) != 0)
			return (print_error(1, ERR_DIR, ast->args[1]));
		cd_update_old_pwd();
	}
	return (EXIT_SUCCESS);
}
