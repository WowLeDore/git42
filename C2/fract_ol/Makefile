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

NAME = fractol
HDRS = fractol.h keys.h

SRCS = fractol.c libft.c utils.c args.c
OBJS = $(SRCS:.c=.o)

FLGS = -Wall -Wextra -Werror
MLXF = -Lminilibx-linux -lmlx_Linux -lX11 -lXext

CC = cc
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLGS) $(OBJS) $(MLXF) -o $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
