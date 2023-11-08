/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/08 17:39:29 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/readline.h>
# include "../Libft/includes/libft.h"
# include "init_exit.h"
# include "parsing.h"

# define MAX_TOKEN_LEN 100

typedef enum s_type
{
	CMD = 0,
	REDIR_IN,
	REDIR_OUT,
	FILE_NAME,
	PIPE,
}	t_type;

typedef struct s_token
{
	char			*content;
	t_type			type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char	*path;
	char	**args;
	int		fd_in;
	int		fd_out;
}	t_cmd;

typedef struct s_shell
{
	t_token	*token;
	t_cmd	*cmd;
	char	**path;
}	t_shell;

#endif