/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/22 17:06:46 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (new_ptr)
	{
		if (ptr)
		{
			ft_memcpy(new_ptr, ptr, new_size);
			free(ptr);
		}
		return (new_ptr);
	}
	else
	{
		return (NULL);
	}
}

char	*get_key_expansion(char **temp)
{
	char	*start;
	char	*key;

	start = ++(*temp);
	while (**temp && (ft_isalnum(**temp) || **temp == '_'))
		(*temp)++;
	key = ft_strdup(start);
	key[*temp - start] = '\0';
	return (key);
}

void	expand_variables(t_token *token)
{
	char	*temp;
	char	*new_content;
	char	*key;
	char	*value;
	size_t	old_len;

	temp = token->content;
	new_content = ft_strdup("");
	while (*temp)
	{
		if (*temp == '$' && (ft_isalpha(*(temp + 1))))
		{
			key = get_key_expansion(&temp);
			value = getenv(key);
			free(key);
			if (value)
			{
				old_len = ft_strlen(new_content);
				new_content = ft_realloc(new_content, old_len + ft_strlen(value)
						+ 1);
				ft_strlcat(new_content, value, old_len + ft_strlen(value) + 1);
			}
		}
		else
		{
			old_len = ft_strlen(new_content);
			new_content = ft_realloc(new_content, old_len + 2);
			new_content[old_len] = *temp;
			new_content[old_len + 1] = '\0';
		}
		temp++;
	}
	free(token->content);
	token->content = new_content;
}

void	expander(void)
{
	t_list	*temp;
	t_token	*token;

	temp = sh()->token_lst;
	while (temp)
	{
		token = ((t_token *)temp->content);
		if (token->type == REDIR2_OUT)
			temp = temp->next;
		else if (token->type == OTHER)
			expand_variables(token);
		temp = temp->next;
	}
}

// int	main(int argc, char *argv[])
// {
// 	if (argc < 2)
// 	{
// 		printf("Please provide a string as an argument.\n");
// 		return (1);
// 	}

// 	for (int i = 1; i < argc; i++)
// 	{
// 		t_token token;
// 		token.content = argv[i];
// 		printf("Original: %s, Expanded: %s\n", argv[i], token.content);
// 	}

// 	return (0);
// }
