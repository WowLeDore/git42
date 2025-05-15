# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/14 17:06:27 by mguillot          #+#    #+#              #
#    Updated: 2025/05/14 19:28:03 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HDRS = philo.h

SRCS = philo.c parse.c
OBJS = $(SRCS:.c=.o)

FLGS = -Wall -Wextra -Werror

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
