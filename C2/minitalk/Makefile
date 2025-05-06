# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/15 16:05:38 by mguillot          #+#    #+#              #
#    Updated: 2025/05/05 14:36:03 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CNAM = client
SNAM = server

CSRC = client.c
SSRC = server.c

COBJ = $(CSRC:.c=.o)
SOBJ = $(SSRC:.c=.o)

HDRS = minitalk.h
FLGS = -Wall -Wextra -Werror

CC = cc
RM = rm -f

all: $(CNAM) $(SNAM)

bonus: all

$(CNAM): $(COBJ)
	$(CC) $(FLGS) $(COBJ) -o $(CNAM)

$(SNAM): $(SOBJ)
	$(CC) $(FLGS) $(SOBJ) -o $(SNAM)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -o $@

clean:
	$(RM) $(COBJ) $(SOBJ) $(COBJ_BONUS) $(SOBJ_BONUS)

fclean: clean
	$(RM) $(CNAM) $(SNAM)

re: fclean all

.PHONY: all bonus clean fclean re
