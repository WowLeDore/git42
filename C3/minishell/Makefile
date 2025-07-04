# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/24 18:35:44 by pbona             #+#    #+#              #
#    Updated: 2025/06/29 19:58:27 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

#external library
DIR_LIBFT = libft
LIB_LIBFT = $(DIR_LIBFT)/libft.a

INCLUDES = includes
CFLAGS = -Wall -Werror -Wextra -I$(INCLUDES) -I$(DIR_LIBFT)
LIBFLAGS = -lreadline
HDRS = \
	$(INCLUDES)/minishell.h \
	$(INCLUDES)/tokens.h \

#directories
DIR_SRCS = srcs

SRCS = \
	$(DIR_SRCS)/main.c \
	$(DIR_SRCS)/lexer.c \
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

gdb: CFLAGS += -g
gdb: re

$(LIB_LIBFT):
	make -C $(DIR_LIBFT)

$(NAME): $(OBJS) $(LIB_LIBFT)
	$(CC) $(OBJS) $(LIB_LIBFT) -o $(NAME) $(LIBFLAGS)

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	make clean -C $(DIR_LIBFT)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(DIR_LIBFT)

re: fclean all

debug:
	@echo "Sources: $(SRCS)"
	@echo "Objetcts: $(OBJS)"
	@echo "Flags: $(CFLAGS)"

.PHONY: all clean fclean re debug gdb
