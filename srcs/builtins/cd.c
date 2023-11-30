/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:46:48 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/30 15:14:29 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*cd_get_path(char *key)
{
	t_list	*curr;
	char	*path_of_env;

	scanner_env(RESET);
	curr = sh()->env_lst;
	while (curr)
	{
		if (ft_strncmp(key, ((t_env *)(curr->content))->key, ft_strlen(key)
				+ 1) == 0)
		{
			path_of_env = (((t_env *)(curr->content))->value);
		}
		curr = curr->next;
	}
	return (path_of_env);
}

int	cd_update_old_pwd(void)
{
	char	cwd[PATH_MAX];
	char	*oldpwd;

	if (getcwd(cwd, PATH_MAX) == NULL)
		return (EXIT_FAILURE); 
    oldpwd = cwd;  
    printf("%s",oldpwd);
	if (!oldpwd)
		return (EXIT_FAILURE);    
	if (update_env_if_key_found("OLDPWD", oldpwd) == EXIT_FAILURE)
		env_add_back("OLDPWD", oldpwd);
	return (EXIT_SUCCESS);
}

int	cd_goto_old_pwd(void)
{
	char	*oldpwd_path;

	oldpwd_path = cd_get_path("OLDPWD");
	if (!oldpwd_path)
		ft_printf("%s", "minishell : cd: OLDPWD not set");
	cd_update_old_pwd();
	chdir(oldpwd_path);
	return (EXIT_SUCCESS);
}

int	cd_goto_home(void)
{
	cd_update_old_pwd();
	chdir(cd_get_path("HOME"));
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
		cd_update_old_pwd();
		chdir(ast->args[1]);
	}
	return (EXIT_SUCCESS);
}
