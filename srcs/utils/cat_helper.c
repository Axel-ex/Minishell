/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat_helper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 14:55:58 by achabrer          #+#    #+#             */
/*   Updated: 2024/03/25 11:54:16 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	only_cats(void)
{
	return (count_cat() == sh()->nb_cmds);
}

int	count_cat(void)
{
	int		count;
	char	*substr;

	count = 0;
	scanner(RESET);
	while (scanner(READ))
	{
		substr = ft_strnstr(scanner(READ)->content, "cat",
				ft_strlen(scanner(READ)->content));
		if (substr && scanner(GET_NEXT) && scanner(GET_NEXT)->type != OTHER)
			count++;
		scanner(NEXT);
	}
	return (count);
}

void	sigint_hand(int signo)
{
	(void)signo;
	sh()->count++;
}

void	handle_hang(int cat_count)
{
	char	*line;

	signal(SIGINT, sigint_hand);
	while (sh()->count < cat_count)
	{
		line = readline("");
		if (!line)
			break ;
		printf("\n");
		free(line);
		sh()->count++;
	}
	sh()->count = 0;
}

bool	is_echo_pwd(char *s)
{
	if (!ft_strncmp(s, "echo", 5) || !ft_strncmp(s, "pwd", 4))
		return (true);
	return (false);
}
