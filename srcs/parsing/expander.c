/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/22 18:16:57 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

char	*append_value_to_content(char *new_content, char *value)
{
	size_t	old_len;

	old_len = ft_strlen(new_content);
	new_content = ft_realloc(new_content, old_len + ft_strlen(value) + 1);
	ft_strlcat(new_content, value, old_len + ft_strlen(value) + 1);
	return (new_content);
}

char	*append_char_to_content(char *new_content, char c)
{
	size_t	old_len;

	old_len = ft_strlen(new_content);
	new_content = ft_realloc(new_content, old_len + 2);
	new_content[old_len] = c;
	new_content[old_len + 1] = '\0';
	return (new_content);
}

void	expand_variables(t_token *token)
{
	char	*temp;
	char	*new_content;
	char	*key;
	char	*value;

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
				new_content = append_value_to_content(new_content, value);

		}
		else
			new_content = append_char_to_content(new_content, *temp);
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
