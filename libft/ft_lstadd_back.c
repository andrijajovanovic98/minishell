/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:07:04 by bszilas           #+#    #+#             */
/*   Updated: 2024/04/11 15:28:45 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*current;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	current = *lst;
	while (current->next)
		current = current->next;
	current->next = new;
}

/*
static void	del(void* data)
{

	printf("content \"%p\" very much deleted! ;)\n", data);
}

int main(int argc, char const *argv[])
{
	t_list * l =  NULL; t_list * l2 =  NULL;
	ft_lstadd_back(&l, ft_lstnew((void*)1));
	ft_lstadd_back(&l, ft_lstnew((void*)2));
			ft_lstiter(l, del);
	ft_lstadd_back(&l2, ft_lstnew((void*)3));
	ft_lstadd_back(&l2, ft_lstnew((void*)4));
		ft_lstadd_back(&l2, ft_lstnew((void*)5));
			ft_lstiter(l2, del);
	ft_lstadd_back(&l, l2);


	ft_lstclear(&l, &del);
	return 0;
}
*/