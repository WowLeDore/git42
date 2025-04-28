# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 16:05:38 by mguillot          #+#    #+#              #
#    Updated: 2025/04/15 16:55:24 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CNAM = client
SNAM = server

CSRC = client.c utils.c
SSRC = server.c utils.c

CSRC_BONUS = client_bonus.c utils_bonus.c
SSRC_BONUS = server_bonus.c utils_bonus.c

COBJ = $(CSRC:.c=.o)
SOBJ = $(SSRC:.c=.o)

COBJ_BONUS = $(CSRC:.c=_bonus.o)
SOBJ_BONUS = $(SSRC:.c=_bonus.o)

HDRS = minitalk.h
FLGS = -Wall -Wextra -Werror -g

CC = cc
RM = rm -f

all: $(CNAM) $(SNAM)

bonus: $(CNAM)_BONUS $(SNAM)_BONUS

$(CNAM): $(COBJ)
	$(CC) $(FLGS) $(COBJ) -o $(CNAM)

$(SNAM): $(SOBJ)
	$(CC) $(FLGS) $(SOBJ) -o $(SNAM)

$(CNAM)_BONUS: $(COBJ_BONUS)
	$(CC) $(FLGS) $(COBJ_BONUS) -o $(CNAM)

$(SNAM)_BONUS: $(SOBJ_BONUS)
	$(CC) $(FLGS) $(SOBJ_BONUS) -o $(SNAM)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -o $@

clean:
	$(RM) $(COBJ) $(SOBJ) $(COBJ_BONUS) $(SOBJ_BONUS)

fclean: clean
	$(RM) $(CNAM) $(SNAM)

re: fclean all

.PHONY: all bonus clean fclean re
