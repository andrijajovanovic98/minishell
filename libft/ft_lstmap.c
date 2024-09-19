/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:05:12 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/21 10:39:21 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_or_del(void *content, void (*del)(void *))
{
	t_list	*new;

	new = malloc(sizeof (t_list));
	if (!new)
	{
		del(content);
		return (NULL);
	}
	if (!content)
		new->content = NULL;
	else
		new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*dest;
	t_list	*dest_head;

	if (!lst || !f || !del)
		return (NULL);
	dest_head = ft_lstnew_or_del(f(lst->content), del);
	if (!dest_head)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		dest = ft_lstnew_or_del(f(lst->content), del);
		if (!dest)
		{
			ft_lstclear(&dest_head, del);
			return (NULL);
		}
		ft_lstadd_back(&dest_head, dest);
		lst = lst->next;
	}
	return (dest_head);
}
/*
static void	*f(void* data)
{
	printf("%s\n", (char*)data);
	return (NULL);
}

static void	f2(void* data)
{
	printf("%s\n", (char*)data);
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

	t_list *new = ft_lstmap(second, &f, &del);
	ft_lstclear(&new, &del);
	ft_lstclear(&head, &del);

	t_list *l = ft_lstnew(strdup(" 1 2 3 "));
	t_list *ret;

	l->next = ft_lstnew(strdup("ss"));
	l->next->next = ft_lstnew(strdup("-_-"));
	ft_lstiter(l, &f2);
	ret = ft_lstmap(l, &f, &del);

	ft_lstclear(&l, &del);
	ft_lstclear(&ret, &del);
	
	return 0;
}
*/