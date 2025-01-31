# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:37:46 by mguillot          #+#    #+#              #
#    Updated: 2025/01/21 14:29:47 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
HDRS = ft_printf.h
SRCS = ft_printf.c
OBJS = $(SRCS:.c=.o)
FLGS = -Wall -Wextra -Werror

CC = cc
AR = ar -rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $?

%.o: %.c $(HDRS)
	$(CC) -c $(FLGS) $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
