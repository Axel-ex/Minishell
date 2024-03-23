/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2024/03/23 19:30:50 by jgomes-v         ###   ########.fr       */
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

int	count_first_quote(char *cnt)
{
	int		i;
	char	quote;

	i = 0;
	quote = cnt[i];
	while (cnt[i] && cnt[i] == quote)
		i++;
	return (i);
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
