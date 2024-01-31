/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 10:01:01 by achabrer          #+#    #+#             */
/*   Updated: 2024/01/31 10:40:17 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	count_firstquotes(char *content, char quote)
{
	int	count;
	int	i;

	count = 0;
	i = -1;
	while (content[++i] && content[i] == quote)
		count++;
	return (count);
}

char	*pre_trim(char *content)
{
	char	*new_content;
	int		count;
	int		size;
	char	quote;
	size_t	i;

	quote = get_first_quote(content);
	count = count_firstquotes(content, quote);
	if (!count || count % 2 != 0)
		return (content);
	size = ft_strlen(content) - (2 * count) + 1;
	new_content = (char *)malloc(sizeof(char) * size);
	if (!new_content)
		return (alloc_error("ast trim"));
	content += count;
	i = -1;
	while (++i < ft_strlen(content) - count)
		new_content[i] = content[i];
	new_content[i] = '\0';
	return (new_content);
}
