/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:34:51 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/28 11:40:29 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_cmd_path(char *cmd)
{
	char		*cmd_path;
	struct stat	stats;

	cmd_path = get_cmd_path(cmd);
	if (!cmd_path)
	{
		free(cmd_path);
		return (print_error(CMD_NT_FD, ERR_CMD, cmd));
	}
	stat(cmd_path, &stats);
	if (S_ISDIR(stats.st_mode))
	{
		free(cmd_path);
		return (print_error(DIR_NT_FD, ERR_DIR, cmd_path));
	}
	free(cmd_path);
	return (EXIT_SUCCESS);
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
