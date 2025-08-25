# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 13:46:07 by mguillot          #+#    #+#              #
#    Updated: 2025/08/25 17:42:56 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	minishell

HDIR	:=	./incl/
SDIR	:=	./srcs/
ODIR	:=	./objs/
LDIR	:=	./libft/

PDIR	:=	./parser/
EDIR	:=	./exec/
BDIR	:=	./builtins/

HDRS	:=	$(addprefix $(HDIR),	\
				minishell.h			\
			)
SRCS	:=	$(addprefix $(SDIR),	\
				env.c				\
				print.c				\
				heredoc.c			\
				free.c				\
				minishell.c			\
			)
SRCS	+=	$(addprefix $(SDIR)$(PDIR),	\
				split.c					\
				group.c					\
				quote.c					\
				expand.c				\
				wordsplit.c				\
				clean.c					\
				assigns.c				\
				commands.c				\
				parse.c					\
			)
SRCS	+=	$(addprefix $(SDIR)$(EDIR),	\
				exec.c					\
			)
SRCS	+=	$(addprefix $(SDIR)$(BDIR),	\
				b_echo.c					\
			)
OBJS	:=	$(patsubst $(SDIR)%.c,$(ODIR)%.o,$(SRCS))
LBFT	:=	$(LDIR)libft.a

CC		:=	cc
CFLGS	:=	-Wall -Wextra -Werror -I"$(HDIR)" -I"$(LDIR)"
LFLGS	:=	-lreadline

RMF		:=	rm -f
RMRF	:=	rm -rf


all: $(NAME)

gdb: CFLGS += -g
gdb: re

$(NAME): $(OBJS) $(HDRS) $(LBFT)
	$(CC) $(CFLGS) $(OBJS) $(LBFT) -o $(NAME) $(LFLGS)

$(ODIR)%.o: $(SDIR)%.c $(HDRS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLGS) -c $< -o $@

$(LBFT):
	@make -C "$(LDIR)"

clean:
	$(RMRF) $(ODIR)
	@make clean -C "$(LDIR)"

fclean: clean
	$(RMF) $(NAME)
	@make fclean -C "$(LDIR)"

re: fclean all

.PHONY: all clean fclean re debug gdb
