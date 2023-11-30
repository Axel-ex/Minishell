/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:46:48 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/30 16:21:59 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//Basically memory was freed but not allocated. I know add to ethe envlist
//using ft_strdup to allocate first. I remove one function that was doing the same
// as getenv and getenv_var
//Modified update_keyiffound as well
int	cd_update_old_pwd(void)
{
	char	*oldpwd;

	oldpwd = getenv("PWD");  
	if (update_env_if_key_found("OLDPWD", oldpwd) == EXIT_FAILURE)
		env_add_back(ft_strdup("OLDPWD"), ft_strdup(oldpwd));
	return (EXIT_SUCCESS);
}

int	cd_goto_old_pwd(void)
{
	char	*oldpwd_path;

	oldpwd_path = getenv_var("OLDPWD");
	if (!oldpwd_path)
		ft_printf("%s", "minishell : cd: OLDPWD not set");
	cd_update_old_pwd();
	chdir(oldpwd_path);
	return (EXIT_SUCCESS);
}

int	cd_goto_home(void)
{
	cd_update_old_pwd();
	chdir(getenv("HOME"));
	return (EXIT_SUCCESS);
}

int	run_cd(t_ast *ast)
{
	//this first statement i thought it was useles since when you
	//update_env_keyblabla if its not ther its creates it but get invalid
	//free if I take out
	if (!getenv_var("OLDPWD"))
		env_add_back(ft_strdup("OLDPWD"), ft_strdup(getenv("PWD")));
	if (!ast->args[1])
		return (cd_goto_home());
	if (ft_strncmp(ast->args[1], "-", 2) == 0)
	    cd_goto_old_pwd();
	else
	{
		cd_update_old_pwd();
		chdir(ast->args[1]);
	}
	return (EXIT_SUCCESS);
}
