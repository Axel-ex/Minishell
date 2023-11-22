/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:15:06 by achabrer          #+#    #+#             */
/*   Updated: 2023/11/20 17:32:29 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

typedef struct s_pipe
{
	char	*msg;
	pid_t	pid;
	int		fds[2];
}	t_pipe;

void	redirect_io2(t_pipe *p, bool in, bool out)
{
	if (in)
		dup2(p->fds[0], STDIN_FILENO);
	if (out)
		dup2(p->fds[1], STDOUT_FILENO);
}

void	read_fd(t_pipe *p)
{
	char	buf;

	while (read(p->fds[0], &buf, 1))
		write(STDOUT_FILENO, &buf, 1);
}

int	main(void)
{
	t_pipe	p;

	p.msg = "hello";
	pipe(p.fds);
	p.pid = fork();
	if (!p.pid)
	{
		redirect_io2(&p, false, true);
		write(STDOUT_FILENO, p.msg, 5);
		p.pid = fork();
		if (!p.pid)
		{
			redirect_io2(&p, true, false);
			read_fd(&p);
		}
	}
	wait(NULL);
	return (0);
}
