/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/01/31 12:28:22 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*handle_quotes(char *cnt, int *in_single_quotes, int *in_double_quotes)
{
	if (*cnt == '\'')
	{
		*in_single_quotes = !(*in_single_quotes);
		if (!(*in_single_quotes) && *(cnt + 1) == '$')
			*in_single_quotes = 2;
	}
	else if (*cnt == '\"')
		*in_double_quotes = !(*in_double_quotes);
	return (cnt);
}

char	*handle_dollar(char **cnt, int in_single_quotes, int in_double_quotes,
		char **new)
{
	char	*key;
	char	*env_value;

	if (**cnt == '$' && (in_single_quotes != 1 || in_double_quotes)
		&& ((ft_isalpha(*(*cnt + 1))) || *(*cnt + 1) == '_'))
	{
		key = get_key_expansion(cnt);
		env_value = getenv_var(key);
		free(key);
		if (env_value)
			*new = append_value_to_content(*new, env_value);
	}
	else if (**cnt == '$' && ((*(*cnt + 1) >= '0' && *(*cnt + 1) <= '9')
			|| *(*cnt + 1) == '\"'))
		(*cnt)++;
	else if (**cnt == '$' && *(*cnt + 1) == '?' && !in_single_quotes)
	{
		*new = append_value_to_content_error(*new, ft_itoa(sh()->exit_status));
		(*cnt)++;
	}
	return (*cnt);
}

char	*handle_other(char **cnt, char **new)
{
	*new = append_char_to_content(*new, **cnt);
	return (*cnt);
}

char	*expand_variable(char *cnt)
{
	char	*new;
	int		in_single_quotes;
	int		in_double_quotes;

	in_single_quotes = 0;
	in_double_quotes = 0;
	if (!ft_strncmp("\"$\"", cnt, 4))
		return (ft_strdup(cnt));
	new = ft_strdup("");
	while (*cnt)
	{
		if (*cnt == '\'' || *cnt == '\"')
			cnt = handle_quotes(cnt, &in_single_quotes, &in_double_quotes);
		else if (*cnt == '$')
			cnt = handle_dollar(&cnt, in_single_quotes, in_double_quotes, &new);
		else
			cnt = handle_other(&cnt, &new);
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
