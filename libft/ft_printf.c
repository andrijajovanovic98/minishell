/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bszilas <bszilas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:36:37 by bszilas           #+#    #+#             */
/*   Updated: 2024/05/21 10:54:01 by bszilas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	decide_format(const char **fmt, va_list args, int *len)
{
	*fmt += 1;
	if (**fmt == 's')
		print_string(va_arg(args, char *), len);
	else if (**fmt == 'c')
		print_char(va_arg(args, int), len);
	else if (**fmt == 'p')
		print_pointer(va_arg(args, void *), len);
	else if (**fmt == 'd' || **fmt == 'i')
		print_decimal(va_arg(args, int), len);
	else if (**fmt == 'u')
		print_decimal(va_arg(args, unsigned int), len);
	else if (**fmt == 'x' || **fmt == 'X')
		print_hex(va_arg(args, unsigned int), **fmt, len);
	else if (**fmt == '%')
		print_char(**fmt, len);
	else if (**fmt == '\0')
	{
		*len = -1;
		*fmt -= 1;
	}
	else
	{
		print_char('%', len);
		print_char(**fmt, len);
	}
}

int	ft_printf(const char *fmt, ...)
{
	va_list	args;
	int		len;

	if (!fmt)
		return (-1);
	len = 0;
	va_start(args, fmt);
	while (*fmt != 0 && len != -1)
	{
		if (*fmt == '%')
		{
			decide_format(&fmt, args, &len);
			fmt++;
		}
		else
			print_char(*fmt++, &len);
	}
	va_end(args);
	return (len);
}
/*
############### hi! use 'make run' for a quick compilation  ###################


__________________________________CHAR_TEST____________________________________

#include <stdio.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	int len, ft_len;

    for (int i = -150; i < -10; i++)
    {
	    len = printf("%i with ___printf : %c\n", i, i);
		ft_len = ft_printf("%i with ft_printf : %c\n", i, i);
    	fuctions_diff(len, ft_len);
    }
	len = printf("");
	ft_len = ft_printf("");
	fuctions_diff(len, ft_len);

    return 0;
}

____________________________________INT_TEST___________________________________

#include <stdio.h>
#include <stdlib.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
 		length diff : %d\n\n", len - ft_len);
}

int main()
{
    int len, ft_len, ran;

    for (int i = -1; i < 3; i++)
    {
        ran = rand();

	    len = printf("\n%d\n", ran);
		ft_len = ft_printf("%d\n\n", ran);
		fuctions_diff(len, ft_len);

	    len = printf("\n%d\n", -ran);
		ft_len = ft_printf("%d\n\n", -ran);
    	fuctions_diff(len, ft_len);
    }
	return 0;
}

___________________________LIMITS_TEST_________________________________________


#include <stdio.h>
#include <limits.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
 		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	int len = printf("\n%u\n", INT_MIN);
	int ft_len = ft_printf("%u\n\n", INT_MIN);
	fuctions_diff(len, ft_len);

	len = printf("\n%u\n", UINT_MAX);
	ft_len = ft_printf("%u\n\n", UINT_MAX);
	fuctions_diff(len, ft_len);
		
	len = printf("\n%d\n", INT_MIN);
	ft_len = ft_printf("%d\n\n", INT_MIN);
	fuctions_diff(len, ft_len);
		
	len = printf("\n%d\n", LONG_MIN);
	ft_len = ft_printf("%d\n\n", LONG_MIN);
	fuctions_diff(len, ft_len);

	len = printf("\n%d\n", LONG_MAX);
	ft_len = ft_printf("%d\n\n", LONG_MAX);
	fuctions_diff(len, ft_len);

	len = printf("\n%d\n", LLONG_MAX);
	ft_len = ft_printf("%d\n\n", LLONG_MAX);
	fuctions_diff(len, ft_len);

	len = printf("\n%d\n", LLONG_MIN);
	ft_len = ft_printf("%d\n\n", LLONG_MIN);
	fuctions_diff(len, ft_len);

	len = printf("\n%p\n", ULLONG_MAX);
	ft_len = ft_printf("%p\n\n", ULLONG_MAX);
	fuctions_diff(len, ft_len);
		
    return 0;
}

_________________________________STRING_TEST___________________________________

#include <stdio.h>
#include <stdlib.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	int len = 0, ft_len = 0, strlen = 20;
	char str[strlen + 1];

	for (int j = 0; j < 10; j++)
	{
	    for (int i = 0; i < strlen; i++)
	        str[i] = (char)(rand() % 130);
	    str[strlen] = 0;

	    len = printf("\n||%s|| = ___string %d\n", str, j);
	    ft_len = ft_printf("||%s|| = ft_string %d\n\n",str, j);
		fuctions_diff(len, ft_len);
	}
	len = printf("\n%s = NULL ___string\n", (char*)0);
	ft_len = ft_printf("%s = NULL ft_string\n\n", (char*)0);
	fuctions_diff(len, ft_len);
		
	ft_len = ft_printf("\n%s%s = ft_printf\n", "hello", "world");
	len = printf("%s%s = ___printf\n\n", "hello", "world");
	fuctions_diff(len, ft_len);
		
	ft_len = ft_printf("\n%s%s%s = ft_printf\n", "1", "2", "3's a charm");
	len = printf("%s%s%s = ___printf\n\n", "1", "2", "3's a charm");
	fuctions_diff(len, ft_len);

	return 0;
}


_______________________________%_EDGE_CASES____________________________________


#include <stdio.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	int len = 0, ft_len = 0;

	len = printf("%");
	printf(" = ___single percent sign\n");
	ft_len = ft_printf("%");
	ft_printf(" = ft_single percent sign\n\n");
	fuctions_diff(len, ft_len);

	len = printf("%%");
	printf(" = ___2 percent signs\n");
	ft_len = ft_printf("%%");
	ft_printf(" = ft_2 percent signs\n\n");
	fuctions_diff(len, ft_len);
	
	len = printf("%%%");
	printf(" = ___3 percent signs\n");
	ft_len = ft_printf("%%%");
	ft_printf(" = ft_3 percent signs\n\n");
	fuctions_diff(len, ft_len);
		
	len = printf("%s%%%", "%");
	printf(" = ___4 percent signs\n");
	ft_len = ft_printf("%s%%%", "%");
	ft_printf(" = ft_4 percent signs\n\n");
	fuctions_diff(len, ft_len);
		
	len = printf("%%%%%");
	printf(" = ___5 percent signs\n");
	ft_len = ft_printf("%%%%%");
	ft_printf(" = ft_5 percent signs\n\n");
	fuctions_diff(len, ft_len);

	return 0;
}

_________________________HEX_TEST______________________________________________

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
    int len, ft_len, ran;

    for (int i = -1; i < 5; i++)
    {
        srand(i);
        ran = rand();
	    len = printf("\n%X\n", ran);
		ft_len = ft_printf("%X\n\n", ran);
    	fuctions_diff(len, ft_len);

	    len = printf("\n%x\n", -ran);
		ft_len = ft_printf("%x\n\n", -ran);
    	fuctions_diff(len, ft_len);
    }
	
	len = printf("\n%x\n", 0);
	ft_len = ft_printf("%x\n\n", 0);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%X\n", INT_MIN);
	ft_len = ft_printf("%X\n\n", INT_MIN);
	fuctions_diff(len, ft_len);

    return 0;
}

________________________POINTER_TEST___________________________________________

#include <stdio.h>
#include <stdlib.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	char *p1 = "string";
	int n = 1;
	static int nbr = -1;
	char *p2 = malloc(1 * sizeof (char));

	int len = printf("\n%p\n", p1);
	int ft_len = ft_printf("%p\n\n", p1);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", &p1);
	ft_len = ft_printf("%p\n\n", &p1);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", p2);
	ft_len = ft_printf("%p\n\n", p2);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", &p2);
	ft_len = ft_printf("%p\n\n", &p2);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", &n);
	ft_len = ft_printf("%p\n\n", &n);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", &nbr);
	ft_len = ft_printf("%p\n\n", &nbr);
	fuctions_diff(len, ft_len);
	
	len = printf("\n%p\n", NULL);
	ft_len = ft_printf("%p\n\n", NULL);
	fuctions_diff(len, ft_len);

	free (p2);
	return 0;
}

____________________________MIXED_TEST_________________________________________


#include <stdio.h>

void fuctions_diff(int len, int ft_len)
{
	if (len - ft_len)
		printf("\n------------------------------------\n \
		length diff : %d\n\n", len - ft_len);
}

int main()
{
	int len = printf("___mix : %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% \n\
	%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% \n\
	%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42, 42, \
	'B', "-42", -42, -42 ,-42 ,-42, 42, \
	'C', "0", 0, 0 ,0 ,0, 42, 0);
	int ft_len = ft_printf("ft_mix : %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% \n\
	%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% \n\
	%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%\n", 'A', "42", 42, 42 ,42 , 42, 42, \
	'B', "-42", -42, -42 ,-42 ,-42, 42, \
	'C', "0", 0, 0 ,0 ,0, 42, 0);

	fuctions_diff(len, ft_len);
	return 0;
}
*/