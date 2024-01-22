/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:30:06 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/22 11:44:58 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_unset(t_ast *ast)
{
	int		i;
	t_list	*curr;

	if (!ast->args[1])
		return ;
	i = 1;
	curr = sh()->env_lst;
	while (curr)
	{
		if (ft_strncmp(ast->args[i], ((t_env *)(curr->content))->key,
			ft_strlen(ast->args[i]) + 1) == 0)
			return (remove_current_node(&sh()->env_lst, curr));
		curr = curr->next;
	}
}

void	remove_current_node(t_list **head, t_list *current)
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
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = current->next;
	free(current);
}
