
#include "../../includes/minishell.h"

void	free_copy_env_lst(void)
{
	t_list *current = sh()->copy_env_lst;
	t_list *next_node;

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


void copy_env_list(t_list *env_list)
{
	t_list *copy_list = NULL;
	t_list *temp;

	while (env_list)
	{
		temp = (t_list *)malloc(sizeof(t_list));
		temp->content = malloc(sizeof(t_env));
		((t_env *)temp->content)->key = ft_strdup(((t_env *)env_list->content)->key);
		((t_env *)temp->content)->value = ft_strdup(((t_env *)env_list->content)->value);
		ft_lstadd_back(&copy_list, temp);
		env_list = env_list->next;
	}
	sh()->copy_env_lst = copy_list;
}

void sort_copy_env_list(void)
{
	t_list *current = sh()->copy_env_lst;
	t_list *index = NULL;
	t_env *temp;

	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(((t_env *)current->content)->key, ((t_env *)index->content)->key) > 0)
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


