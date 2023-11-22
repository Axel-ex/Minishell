/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgomes-v <jgomes-v@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 17:49:43 by jgomes-v          #+#    #+#             */
/*   Updated: 2023/11/22 14:41:58 by jgomes-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	expand_variables(t_token *token)
{
	char	*key;
	char	*value;
	char	*result;
	char	*temp;
	char	*start;

	temp = token->content;
	result = malloc(ft_strlen(token->content) + 1);
	result[0] = '\0';
	while (*temp)
	{
		if (*temp == '$' && (ft_isalpha(*(temp + 1))))
		{
			temp++;
			start = temp;
			while (*temp && (ft_isalnum(*temp) || *temp == '_'))
				temp++;
			key = strdup(start);
			key[temp - start] = '\0';
			value = getenv(key);
			free(key);
			if (value)
				ft_strlcat(result, value, ft_strlen(result) + ft_strlen(value)
						+ 1);
			else
				ft_strlcat(result, "$", ft_strlen(result) + 2);
		}
		else
		{
			result[ft_strlen(result)] = *temp;
			result[ft_strlen(result) + 1] = '\0';
		}
		temp++;
	}
	token->content = result;
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
