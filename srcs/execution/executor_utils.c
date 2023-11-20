/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:34:51 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 14:39:02 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	match_cmd(t_ast *ast)
{
	if (!ft_strncmp(ast->token->content, "exit", 5))
		free_shell(false);
	// if (ft_strncmp(ast->token->content, "echo", 5))
	// 	echo(ast->args);
	else
		execute_cmd(ast);
}

bool	is_forkable(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7)
		|| !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5))
		return (false);
	return (true);
}

bool	is_operator(t_token *token)
{
	if (token->type == OTHER)
		return (false);
	return (true);
}


char	*get_absolute_path(char *cmd)
{
	char	*path1;
	char	*path;
	int		i;

	i = -1;
	while (sh()->path[++i])
	{
		path1 = ft_strjoin(sh()->path[i], "/");
		path = ft_strjoin(path1, cmd);
		free(path1);
		if (!access(path, R_OK | F_OK))
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd)
{
	char	*path;
	char	*cwd;

	if (*cmd == '.')
	{
		cwd = getenv("PWD");
		path = ft_strjoin(cwd, cmd);
	}
	else
		path = get_absolute_path(cmd);
	return (path);
}
