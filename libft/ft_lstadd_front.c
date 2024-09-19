/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 18:51:07 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/21 18:53:26 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = *lst;
		*lst = new;
	}
}
/*
int main(int argc, char const *argv[])
{
	char s1[6] = "first";
	char s2[7] = "second";
	char *s3 = "third";

	t_list *first = ft_lstnew(s1);
	t_list *head = first;

	t_list *second = ft_lstnew(s2);
	ft_lstadd_front(&head, second);

	t_list *third = ft_lstnew(s3);
	ft_lstadd_back(&head, third);

	printf("%d\n", ft_lstsize(head));
	printf("%s\n", (char *)ft_lstlast(head)->content);

	t_list *current = head;
    while (current)
	{
		printf("%s\n", (char*)current->content);
        current = current->next;
    }
	
	current = head;
    while (current)
	{
        t_list *next = current->next;
        free(current);
        current = next;
    }
	return 0;
}
*/