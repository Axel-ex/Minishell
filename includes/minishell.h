/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/13 23:32:44 by achabrer         ###   ########.fr       */
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
# include <readline/history.h>
# include "../Libft/includes/libft.h"
# include "init_exit.h"
# include "parsing.h"
# include "debug.h"
# include "signals.h"
# include "envp.h"


# define MAX_TOKEN_LEN 100

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

/**
 * @brief returns shell structure from anywhere in the code
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
	REDIR2_IN,
	REDIR2_OUT,
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
	PREV,
	GET_NEXT,
	GET_PREV,
}	t_operation;

typedef struct s_token
{
	char			*content;
	t_type			type;
}	t_token;

typedef struct s_ast
{
	t_token			*token;
	char			**args;
	int				index;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

typedef struct s_env
{
	char	**env;
	char	**key;
	char	**content;
	int		len;
}			t_env;

typedef struct s_shell
{
	char		*line;
	int			fd_in;
	int			fd_out;
	t_list		*token_lst;
	t_ast		*ast;
	char		**path;
	t_list		*env_lst;
	t_env		env;
	int			exit_status;
}	t_shell;


#endif