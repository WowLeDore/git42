# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/10 17:04:19 by mguillot          #+#    #+#              #
#    Updated: 2025/04/12 02:31:35 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
HDRS = push_swap.h

SRCS =	push_swap.c	conquer.c	divide.c	int_circ_queue.c	libft.c		\
		rules1.c	rules2.c	rules3.c	verif.c				print.c
OBJS = $(SRCS:.c=.o)

FLGS = -Wall -Wextra -Werror -g

CC = cc
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLGS) $(OBJS) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
