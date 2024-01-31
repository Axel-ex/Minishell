
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
	//free(value);
	return (new_content);
}

char	*append_value_to_content_error(char *new_content, char *value)
{
	size_t	old_len;

	old_len = ft_strlen(new_content);
	new_content = ft_realloc_str(new_content, old_len + ft_strlen(value) + 1);
	ft_strlcat(new_content, value, old_len + ft_strlen(value) + 1);
	free(value);
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