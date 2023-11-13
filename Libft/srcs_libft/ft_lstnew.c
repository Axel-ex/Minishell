/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achabrer <achabrer@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 16:03:56 by axelc             #+#    #+#             */
/*   Updated: 2023/11/13 12:46:05 by achabrer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*element;

	element = (t_list *)malloc(sizeof(*element));
	if (!element)
		return (NULL);
	element->content = content;
	element->next = NULL;
	element->prev = NULL;
	return (element);
}
