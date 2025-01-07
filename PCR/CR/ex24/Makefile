# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/02 13:43:40 by mguillot          #+#    #+#              #
#    Updated: 2024/11/04 18:32:30 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER_FOLDER = includes/
SOURCE_FOLDER = srcs/

SOURCES = $(SOURCE_FOLDER)ft_putchar.c \
	$(SOURCE_FOLDER)ft_swap.c \
	$(SOURCE_FOLDER)ft_putstr.c \
	$(SOURCE_FOLDER)ft_strlen.c \
	$(SOURCE_FOLDER)ft_strcmp.c 
OBJECTS = $(SOURCES:.c=.o)

LIB_NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
OPTIONS = -I $(HEADER_FOLDER) -c
AR = ar rc

all: $(LIB_NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(OPTIONS) $< -o $@

$(LIB_NAME): $(OBJECTS)
	$(AR) $(LIB_NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(LIB_NAME)

re: fclean all
