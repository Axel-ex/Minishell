/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/29 11:17:12 by achabrer         ###   ########.fr       */
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

char	*expand_variable(char *content)
{
	char	*new_content;
	char	*env_value;
	char	*key;

	new_content = ft_strdup("");
	while (*content)
	{
		if (*content == '$' && (ft_isalpha(*(content + 1))))
		{
			key = get_key_expansion((&content));
			env_value = getenv_var(key);
			free(key);
			if (env_value)
				new_content = append_value_to_content(new_content, env_value);
			if (!ft_isalnum(*content) && *content != '_')
				content--;
		}
		else
			new_content = append_char_to_content(new_content, *content);
		content++;
	}
	return (new_content);
}

void	expander(void)
{
	char	*temp;

	scanner(RESET);
	while (scanner(READ))
	{
		if (scanner(READ)->type == OTHER)
		{
			temp = expand_variable(scanner(READ)->content);
			free(scanner(READ)->content);
			scanner(READ)->content = temp;
		}
		scanner(NEXT);
	}
}
