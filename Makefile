# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bszilas <bszilas@student.42vienna.com>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/16 16:17:41 by bszilas           #+#    #+#              #
#    Updated: 2024/08/17 11:53:45 by bszilas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFILES = readline.c lexer.c lexerutils.c lexerutils2.c signal.c interpret.c cd.c \
parser.c error.c interpret_utils.c parser_utils.c execute.c builtin.c here_doc.c \
exec_utils.c file_redirections.c environment.c cleanup.c free.c syntax_checker.c \
execute_pipes.c interpret_compound_var.c interpret_utils2.c environment_utils2.c \
environment_utils.c parser_utils2.c lexerutils3.c error_utils.c exec_utils2.c \
environment_utils3.c heredoc_utils.c exec_utils3.c environment_utils9000.c

CC = cc
LIBDIR = libft
SRCDIR = src/
INCDIR = inc/
OBJDIR = obj/
LIB = libft.a
RM = rm -rf
SRC = $(addprefix $(SRCDIR),$(CFILES))
OBJ = $(addprefix $(OBJDIR),$(CFILES:%.c=%.o))
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR)
LFLAGS = -L$(LIBDIR) -lft -lreadline

all: $(LIB) $(OBJDIR) $(NAME)

tester:
	$(CC) $(CFLAGS) -D TESTER=1 $(SRC) -o minishell $(LFLAGS)
	
$(LIB):
	make -C $(LIBDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	make clean -C $(LIBDIR)
	$(RM) $(OBJ) $(OBJDIR)

fclean: clean
	$(RM) $(LIBDIR)/$(LIB) $(NAME) $(DB) *.out

diagram:
	cflow --main=main --depth=6 --omit-arguments -f dot $(SRC) | dot -Txlib

re: fclean all

.PHONY: all clean fclean re debug diagram

.SILENT: clean fclean 