# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 13:46:07 by mguillot          #+#    #+#              #
#    Updated: 2025/08/13 16:55:32 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

HDIR	:= ./incl/
SDIR	:= ./srcs/
ODIR	:= ./objs/
LDIR	:= ./libft/

HDRS	:= $(addprefix $(HDIR),	\
				minishell.h		\
			)
SRCS	:= $(addprefix $(SDIR),	\
				free.c			\
				split.c			\
				group.c			\
				env.c			\
				quote.c			\
				expand.c		\
				print.c			\
				parse.c			\
				minishell.c		\
			)
OBJS	:= $(addprefix $(ODIR), $(notdir $(SRCS:.c=.o)))
LBFT	:= $(LDIR)libft.a

CC		:= cc
FLGS	:= -Wall -Wextra -Werror -I"$(HDIR)" -I"$(LDIR)" -lreadline

RMF		:= rm -f
RMRF	:= rm -rf


all: $(NAME)

gdb: FLGS += -g
gdb: re

$(NAME): $(OBJS) $(HDRS) $(LBFT)
	$(CC) $(FLGS) $(OBJS) $(LBFT) -o $(NAME)

$(ODIR)%.o: $(SDIR)%.c $(HDRS)
	@mkdir -p $(ODIR)
	$(CC) $(FLGS) -c $< -o $@
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
