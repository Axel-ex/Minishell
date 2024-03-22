/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/22 16:39:46 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_key_exp(char *cnt)
{
	char	*tmp;
	int		len;

	len = 0;
	tmp = ft_strnstr(cnt, "$", ft_strlen(cnt));
	if (tmp[1] == '?')
		return (ft_strdup("$?"));
	if (ft_isdigit(tmp[1]))
		return (ft_substr(tmp, 0, 1));
	while (ft_isalnum(tmp[len + 1]) || tmp[len + 1] == '_')
		len++;
	return (ft_substr(tmp, 1, len));
}

char	*replace_var(char *cnt, char *key, char *value)
{
	char	*new;
	char	*start;
	char	*end;
	int		size;

	if (!value)
		value = "";
	size = ft_strlen(cnt) - ft_strlen(key) + ft_strlen(value) + 1;
	new = (char *)malloc(sizeof(char) * size);
	if (!new)
		return (NULL);
	start = ft_strnstr(cnt, "$", ft_strlen(cnt)) + 1;
	end = start + ft_strlen(key);
	if (*start == '?')
		end--;
	ft_strlcpy(new, cnt, start - cnt);
	ft_strlcat(new, value, size);
	ft_strlcat(new, end, size);
	return (new);
}

static int	count_first_quote(char *cnt)
{
	int		i;
	char	quote;

	i = 0;
	quote = cnt[i];
	while (cnt[i] && cnt[i] == quote)
		i++;
	return (i);
}

char	*expand_variable(char *cnt)
{
	char	*value;
	char	*key;
	char	*res;

	res = ft_strdup(cnt);
	if (*res == '\'' && count_first_quote(res) % 2)
		return (res);
	while (ft_strnstr(res, "$", ft_strlen(res)))
	{
		key = get_key_exp(res);
		if (!key)
			break ;
		if (is_empty(key))
		{
			free(key);
			break ;
		}
		if (!ft_strncmp(key, "$?", 2))
			value = ft_itoa(sh()->exit_status);
		else
			value = getenv_var(key);
		res = replace_var(res, key, value);
		free(key);
		if (value)
			free(value);
	}
	return (res);
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
