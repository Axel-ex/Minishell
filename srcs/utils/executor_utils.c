/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:34:51 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/20 09:20:24 by Axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int check_cmd_path(char* cmd)
{
    char* cmd_path;
    struct stat stats;

    if (is_empty(cmd))
        return (0);
    cmd_path = get_cmd_path(cmd);
    if (ft_strchr(cmd, '/') && stat(cmd, &stats) == -1)
		return (print_error(ERR_CMD, DIR_NT_FOUND, cmd));
	if (!cmd_path)
        return (print_error(ERR_CMD, CMD_NT_FOUND, cmd));
    if (access(cmd_path, F_OK | X_OK))
        print_error(ERR_DIR, PERM_DEN, cmd);
	else if (S_ISDIR(stats.st_mode))
		print_error(ERR_DIR, IS_DIR, cmd);
    free(cmd_path);
    return (EXIT_SUCCESS);
}

bool is_forkable(char* cmd)
{
    if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "export", 7) ||
        !ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "exit", 5))
        return (false);
    return (true);
}

bool is_operator(t_type type)
{
    if (type == OTHER)
        return (false);
    return (true);
}

char* get_absolute_path(char* cmd)
{
    char* path1;
    char* path;
    int i;

    i = -1;
    if (!access(cmd, F_OK))
        return (ft_strdup(cmd));
    while (sh()->path[++i])
    {
        path1 = ft_strjoin(sh()->path[i], "/");
        path = ft_strjoin(path1, cmd);
        free(path1);
        if (!access(path, F_OK))
            return (path);
        free(path);
    }
    return (NULL);
}

char* get_cmd_path(char* cmd)
{
    char* path;
    char* cwd;

    if (*cmd == '.')
    {
        cmd++;
        cwd = getenv_var("PWD");
        path = ft_strjoin(cwd, cmd);
		free(cwd);
    }
    else
        path = get_absolute_path(cmd);
    return (path);
}
