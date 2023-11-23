/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/23 09:40:12 by achabrer         ###   ########.fr       */
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

void	expand_variable(t_token *token)
{
	char	*temp;
	char	*new_content;
	char	*env_value;
	char	*key;

	temp = token->content;
	new_content = ft_strdup("");
	while (*temp)
	{
		if (*temp == '$' && (ft_isalpha(*(temp + 1))))
		{
			key = get_key_expansion(&temp);
			env_value = getenv_var(key);
			free(key);
			if (env_value)
				new_content = append_value_to_content(new_content, env_value);
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
	t_token	*token;

	scanner(RESET);
	while (scanner(READ))
	{
		token = ((t_token *)scanner(READ));
		if (token->type == REDIR2_OUT)
			scanner(NEXT);
		else if (token->type == OTHER)
			expand_variable(token);
		scanner(NEXT);
	}
}
// void	expander(void)
// {
// 	scanner(RESET);
// 	while (scanner(READ))
// 	{
// 		if (scanner(READ)->type == OTHER)
// 			expand_variables(scanner(READ));
// 		scanner(NEXT);
// 	}
// }