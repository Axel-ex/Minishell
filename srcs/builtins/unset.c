/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:30:06 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/29 13:38:04 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	run_unset(t_ast *ast)
{
	int		i;
	t_list	*curr;

	i = 1;
	scanner_env(RESET);
	curr = sh()->env_lst;
	while (curr)
	{
		if (ft_strncmp(ast->args[i], ((t_env *)(curr->content))->key,
				ft_strlen(ast->args[i]) + 1) == 0)
		{
			removeCurrentNode(&sh()->env_lst, curr);
		}
		curr = curr->next;
	}
	return (0);
}

void	removeCurrentNode(t_list **head, t_list *current)
{
	t_list	*prev;

	if (*head == NULL || current == NULL)
		return ;
	if (*head == current)
	{
		*head = current->next;
		free(current);
		return ;
	}
	prev = *head;
	while (prev->next != NULL && prev->next != current)
	{
		prev = prev->next;
	}
	if (prev->next == NULL)
		return ;
	prev->next = current->next;
	free(current);
}
