/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/29 16:47:57 by jgomes-v         ###   ########.fr       */
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
	(*temp)--;
	return (key);
}

char	*append_value_to_content(char *new_content, char *value)
{
	size_t	old_len;

	old_len = ft_strlen(new_content);
	new_content = ft_realloc_str(new_content, old_len + ft_strlen(value) + 1);
	ft_strlcat(new_content, value, old_len + ft_strlen(value) + 1);
	return (new_content);
}

char	*append_char_to_content(char *new_content, char c)
{
	size_t	old_len;

	old_len = ft_strlen(new_content);
	new_content = ft_realloc_str(new_content, old_len + 2);
	new_content[old_len] = c;
	new_content[old_len + 1] = '\0';
	return (new_content);
}
char	*expand_variable(char *cnt)
{
	char	*new;
	char	*env_value;
	char	*key;
	int		in_single_quotes;
	int		in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	new = ft_strdup("");
	while (*cnt)
	{
		if (*cnt == '\'')
		{
			in_single_quotes = !in_single_quotes;
			if (!in_single_quotes && *(cnt + 1) == '$')
			{
				in_single_quotes = 2;
			}
		}
		else if (*cnt == '\"')
		{
			in_double_quotes = !in_double_quotes;
		}
		if (*cnt == '$' && (in_single_quotes != 1 || in_double_quotes)
			&& ((ft_isalpha(*(cnt + 1))) || *(cnt + 1) == '_'))
		{
			key = get_key_expansion((&cnt));
			env_value = getenv_var(key);
			free(key);
			if (env_value)
				new = append_value_to_content(new, env_value);
		}
		else if (*cnt == '$' && ((*(cnt + 1) >= '0' && *(cnt + 1) <= '9')
					|| *(cnt + 1) == '\"'))
			cnt++;
		else if (*cnt == '$' && *(cnt + 1) == '?' && !in_single_quotes)
		{
			new = append_value_to_content(new, ft_itoa(sh()->exit_status));
			cnt++;
		}
		else
		{
			new = append_char_to_content(new, *cnt);
		}
		if (in_single_quotes == 2)
			in_single_quotes = 0;
		cnt++;
	}
	return (new);
}

void	expander(void)
{
	char	*temp;

	scanner(RESET);
	while (scanner(READ))
	{
		if (scanner(READ)->type == OTHER || scanner(READ)->type == SIMPLE_QUOTE)
		{
			temp = expand_variable(scanner(READ)->content);
			free(scanner(READ)->content);
			scanner(READ)->content = temp;
		}
		scanner(NEXT);
	}
}
