/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:06 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/23 19:37:47 by jgomes-v         ###   ########.fr       */
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
# include <limits.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/wait.h>
# include "../Libft/includes/libft.h"
# include "init_exit.h"
# include "parsing.h"
# include "envp.h"
# include "execution.h"
# include "builtins.h"
# include "utils.h"
# include "export_utils.h"
# include "expander_utils.h"

# define PROMPT "minishell> "
# define MAX_TOKEN_LEN 100

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

/**
 * @brief returns shell structure from anywhere in the code.
 * 
 * @return t_shell* 
 */
t_shell	*sh(void);

/**
 * @brief categorise the input into types of token.
 * 
 */
typedef enum s_type
{
	OTHER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR2_OUT,
	SIMPLE_QUOTE,
}	t_type;

/**
 * @brief operation for the scanner. the scanner scans through the
 * list of token and execute these operation.
 * 
 * RESET: go at beggining of list
 * READ: get the token pointed by lst
 * NEXT: move of one element
 * GET_NEXT: get the next token
 * 
 */
typedef enum s_operation
{
	RESET,
	READ,
	NEXT,
	GET_NEXT,
}	t_operation;

typedef struct s_token
{
	char			*content;
	t_type			type;
}	t_token;

typedef struct s_ast
{
	t_token			*token;
	int				pos;
	char			**args;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_shell
{
	pid_t		pid;
	int			fd_in;
	int			fd_out;
	int			exit_status;
	char		*line;
	char		**path;
	char		**envp;
	t_list		*env_lst;
	t_list		*copy_env_lst;
	t_list		*token_lst;
	t_ast		*ast;
	int			**pipes;
	int			nb_cmds;
	int			sigint_flag;
	int			count;
}	t_shell;

#endif