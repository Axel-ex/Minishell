/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 12:30:06 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/29 14:04:52 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void remove_env_variable(const char *key)
{
t_list *curr = sh()->env_lst;

while (curr)
{
    if (ft_strncmp(key, ((t_env *)(curr->content))->key,
        ft_strlen(key) + 1) == 0)
    {
        remove_current_node(&sh()->env_lst, curr);
        return;
    }
    curr = curr->next;
}

}

void run_unset(t_ast *ast)
{
	int i;
	if (!ast->args[1])
		return;

	i = 1;
		while (ast->args[i])
		{
			remove_env_variable(ast->args[i]);
			i++;
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
		free_env_lst(current->content);
		free(current);
		return ;
	}
	prev = *head;
	while (prev->next != NULL && prev->next != current)
		prev = prev->next;
	if (prev->next == NULL)
		return ;
	prev->next = current->next;
	free_env_lst(current->content);
	free(current);
}
