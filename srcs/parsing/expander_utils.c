/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 19:42:31 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/23 19:42:55 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_value_expander(char *key)
{
	if (!ft_strncmp(key, "$?", 2))
		return (ft_itoa(sh()->exit_status));
	else
		return (getenv_var(key));
}

void	free_resources(char *old_res, char *key, char *value)
{
	free(old_res);
	free(key);
	if (value)
		free(value);
}

char	*expand_variable(char *cnt)
{
	char	*value;
	char	*key;
	char	*res;
	char	*old_res;

	res = ft_strdup(cnt);
	old_res = NULL;
	if (*res == '\'' && count_first_quote(res) % 2)
	{
		return (res);
	}
	while (ft_strnstr(res, "$", ft_strlen(res)))
	{
		key = get_key_exp(res);
		if (!key || is_empty(key))
		{
			free(key);
			break ;
		}
		value = get_value_expander(key);
		old_res = res;
		res = replace_var(res, key, value);
		free_resources(old_res, key, value);
	}
	return (res);
}
