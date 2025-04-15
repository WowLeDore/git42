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
HDRS = minitalk.h

CSRC = client.c utils.c
SSRC = server.c utils.c

COBJ = $(CSRC:.c=.o)
SOBJ = $(SSRC:.c=.o)

FLGS = -Wall -Wextra -Werror

CC = cc
RM = rm -f

all: $(CNAM) $(SNAM)

$(CNAM): $(COBJ)
	$(CC) $(FLGS) $(COBJ) -o $(CNAM)

$(SNAM): $(SOBJ)
	$(CC) $(FLGS) $(SOBJ) -o $(SNAM)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -o $@

clean:
	$(RM) $(COBJ) $(SOBJ)

fclean: clean
	$(RM) $(CNAM) $(SNAM)

re: fclean all

.PHONY: all clean fclean re
