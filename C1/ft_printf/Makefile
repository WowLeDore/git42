# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/21 16:37:46 by mguillot          #+#    #+#              #
#    Updated: 2025/01/21 01:13:32 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LBFT_DIR = libft

LBFT_SRCS = \
	$(LBFT_DIR)/ft_isalpha.c			$(LBFT_DIR)/ft_isdigit.c			\
	$(LBFT_DIR)/ft_isalnum.c			$(LBFT_DIR)/ft_isascii.c			\
	$(LBFT_DIR)/ft_isprint.c			$(LBFT_DIR)/ft_strlen.c				\
	$(LBFT_DIR)/ft_memset.c				$(LBFT_DIR)/ft_bzero.c				\
	$(LBFT_DIR)/ft_memcpy.c				$(LBFT_DIR)/ft_memmove.c			\
	$(LBFT_DIR)/ft_strlcpy.c			$(LBFT_DIR)/ft_strlcat.c			\
	$(LBFT_DIR)/ft_toupper.c			$(LBFT_DIR)/ft_tolower.c			\
	$(LBFT_DIR)/ft_strchr.c				$(LBFT_DIR)/ft_strrchr.c			\
	$(LBFT_DIR)/ft_strncmp.c			$(LBFT_DIR)/ft_memchr.c				\
	$(LBFT_DIR)/ft_memcmp.c				$(LBFT_DIR)/ft_strnstr.c			\
	$(LBFT_DIR)/ft_atoi.c				$(LBFT_DIR)/ft_calloc.c				\
	$(LBFT_DIR)/ft_strdup.c				$(LBFT_DIR)/ft_substr.c				\
	$(LBFT_DIR)/ft_strjoin.c			$(LBFT_DIR)/ft_strtrim.c			\
	$(LBFT_DIR)/ft_split.c				$(LBFT_DIR)/ft_itoa.c				\
	$(LBFT_DIR)/ft_strmapi.c			$(LBFT_DIR)/ft_striteri.c			\
	$(LBFT_DIR)/ft_putchar_fd.c			$(LBFT_DIR)/ft_putstr_fd.c			\
	$(LBFT_DIR)/ft_putendl_fd.c			$(LBFT_DIR)/ft_putnbr_fd.c			\

LBFT_SRCS_BONUS = \
	$(LBFT_DIR)/ft_lstnew_bonus.c		$(LBFT_DIR)/ft_lstadd_front_bonus.c	\
	$(LBFT_DIR)/ft_lstsize_bonus.c		$(LBFT_DIR)/ft_lstlast_bonus.c		\
	$(LBFT_DIR)/ft_lstadd_back_bonus.c	$(LBFT_DIR)/ft_lstdelone_bonus.c	\
	$(LBFT_DIR)/ft_lstclear_bonus.c		$(LBFT_DIR)/ft_lstiter_bonus.c		\
	$(LBFT_DIR)/ft_lstmap_bonus.c											\

PRTF_SRCS = \
				ft_printf.c							ft_flags.c				\

LBFT_OBJS = $(LBFT_SRCS:.c=.o)
LBFT_OBJS_BONUS = $(LBFT_SRCS_BONUS:.c=.o)
PRTF_OBJS = $(PRTF_SRCS:.c=.o)

LBFT_HDRS = libft/libft.h
PRTF_HDRS = ft_printf.h

LBFT_NAME = libft.a
PRTF_NAME = libftprintf.a

CC = cc
AR = ar -rcs
RM = rm -f
FLGS = -Wall -Wextra -Werror

all: $(LBFT_NAME) $(PRTF_NAME)

$(LBFT_NAME): $(LBFT_OBJS)
	$(AR) $@ $?

libft_bonus: $(LBFT_OBJS) $(LBFT_OBJS_BONUS)
	$(AR) $(LBFT_NAME) $?

$(PRTF_NAME): $(PRTF_OBJS) $(LBFT_NAME)
	$(AR) $@ $?

$(LBFT_DIR)/%.o: $(LBFT_DIR)/%.c $(LBFT_HDRS)
	$(CC) -c $(FLGS) $< -o $@

%.o: %.c $(PRTF_HDRS)
	$(CC) -c $(FLGS) $< -o $@

clean:
	$(RM) $(PRTF_OBJS) $(LBFT_OBJS) $(LBFT_OBJS_BONUS)

fclean: clean
	$(RM) $(LBFT_NAME) $(PRTF_NAME)

re: fclean all

bonus: bonus_libft

.PHONY: all bonus clean fclean re
