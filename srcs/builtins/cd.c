/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:46:48 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/25 10:22:25 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	cd_update_old_pwd();
	if (chdir(oldpwd_path))
	{
		ft_printf("%s", "minishell : cd: error changing directory\n");
		free(oldpwd_path);
		return (EXIT_FAILURE);
	}
	free(oldpwd_path);
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
	if (ast->args[2])
		return (print_error(ERR_GEN, TOO_MANY_ARGS, ast->args[0]));
	if (ft_strncmp(ast->args[1], "-", 2) == 0)
		cd_goto_old_pwd();
	else
	{
		cd_update_old_pwd();
		if (chdir(ast->args[1]) != 0)
			return (print_error(1, DIR_NT_FOUND, ast->args[1]));
	}
	return (EXIT_SUCCESS);
}
