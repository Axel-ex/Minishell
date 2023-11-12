/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 11:32:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/12 14:41:34 by achabrer         ###   ########.fr       */
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

t_shell	*sh(void);

# define MAX_TOKEN_LEN 100

# define NC		"\e[0m"
# define RED	"\e[31m"
# define GREEN	"\e[32m"
# define PURPLE	"\e[35m"
# define CYAN	"\e[36m"

typedef enum s_type
{
	OTHER,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR2_IN,
	REDIR2_OUT,
}	t_type;

typedef enum s_operation
{
	RESET,
	READ,
	NEXT,
	AHEAD_NEXT,
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
	int		len;
	char	**key;
	char	**content;
	int		index;
}			t_env;

typedef struct s_shell
{
	char	*line;
	t_list	*token_lst;
	t_ast	*ast;
	char	**path;
	t_env	env;
	int		exit_status;
}	t_shell;


#endif