/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:34:51 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/14 17:52:11 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_not_operator(t_token *token)
{
	if (token->type == OTHER)
		return (true);
	return (false);
}

char	*get_relative_path(char *cmd)
{
	char	*cwd;
	char	*path;

	cwd = getenv("PWD");
	path = ft_strjoin(cwd, cmd);
	return (path);
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

	if (*cmd == '.')
		path = get_relative_path(++cmd);
	else
		path = get_absolute_path(cmd);
	return (path);
}
