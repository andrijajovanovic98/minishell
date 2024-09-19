/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: szilas <szilas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 16:47:45 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/29 18:42:28 by szilas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		current = *lst;
		*lst = current->next;
		del(current->content);
		current->content = NULL;
		free(current);
		current = NULL;
	}
}
/*
static void	*f(void* data)
{
	printf("%s\n", (char*)data);
	return (NULL);
}

static void	del(void* data)
{
	printf("content \"%s\" very much deleted! ;)\n", (char*)data);
}

int main(int argc, char const *argv[])
{
	char s1[6] = "first";
	char s2[7] = "second";
	char s3[6] = "third";

	t_list *first = ft_lstnew(s1);
	t_list *head = first;

	t_list *second = ft_lstnew(s2);
	ft_lstadd_front(&head, second);

	t_list *third = ft_lstnew(s3);
	ft_lstadd_back(&head, third);

	ft_lstclear(&head, del);
	
	return 0;
}
*/