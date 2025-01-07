# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 17:07:46 by mguillot          #+#    #+#              #
#    Updated: 2024/09/04 19:11:00 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOURCES = srcs/ft_doop.c srcs/ft_res.c
HEADER = includes/
OBJECTS = srcs/ft_doop.o srcs/ft_res.o
NAME = do-op
CC = cc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I$(HEADER)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(OPTIONS) $(SOURCES) -o $(NAME)

clean:
	rm -f $(NAME)

fclean: clean
	rm -f $(OBJECTS)

re: fclean all
