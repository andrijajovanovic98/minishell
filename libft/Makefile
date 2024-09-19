# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/08 12:01:27 by bszilas           #+#    #+#              #
#    Updated: 2024/08/13 11:41:17 by bszilas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = \
ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_lstiter.c \
ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstlast.c \
ft_lstmap.c ft_lstnew.c ft_lstsize.c ft_printf.c ft_printf_fmts.c ft_abs.c \
ft_free_array.c ft_rng.c ft_gnl.c ft_argv_splitter.c ft_iswhitespace.c ft_pow.c

NAME = libft.a
INC = .
CC = cc
OBJDIR = obj
OBJ := $(addprefix $(OBJDIR)/,$(patsubst %.c,%.o,$(SRC)))
CFLAGS := -Wall -Wextra -Werror -I$(INC)

all: $(OBJDIR) $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJDIR):
	mkdir -p $@

debug:
	$(CC) $(CFLAGS) -g $(SRC)
	lldb a.out

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ) $(OBJDIR)

fclean: clean
	rm -rf $(NAME) *.out

push: fclean
	git add .
	git commit -m "quickpush $(shell date)"
	git push

re: fclean all

.PHONY: all clean fclean re push debug

.SILENT: clean fclean push $(NAME)