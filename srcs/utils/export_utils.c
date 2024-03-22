/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 15:02:39 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/22 09:47:25 by Axel             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_copy_env_lst(void)
{
	t_list	*current;
	t_list	*next_node;

	current = sh()->copy_env_lst;
	while (current != NULL)
	{
		next_node = current->next;
		free(((t_env *)current->content)->key);
		free(((t_env *)current->content)->value);
		free(current->content);
		free(current);
		current = next_node;
	}
	sh()->copy_env_lst = NULL;
}

void	copy_env_list(void)
{
	t_env	*temp;

	sh()->copy_env_lst = NULL;
	scanner_env(RESET);
	while (scanner_env(READ))
	{
		temp = (t_env *)malloc(sizeof(t_env));
		if (!temp)
			return ;
		temp->key = ft_strdup(scanner_env(READ)->key);
		temp->value = ft_strdup(scanner_env(READ)->value);
		ft_lstadd_back(&sh()->copy_env_lst, ft_lstnew(temp));
		scanner_env(NEXT);
	}
}

void	sort_copy_env_list(void)
{
	t_list	*current;
	t_list	*index;
	t_env	*temp;

	index = NULL;
	current = sh()->copy_env_lst;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(((t_env *)current->content)->key,
					((t_env *)index->content)->key) > 0)
			{
				temp = current->content;
				current->content = index->content;
				index->content = temp;
			}
			index = index->next;
		}
		current = current->next;
	}
}
