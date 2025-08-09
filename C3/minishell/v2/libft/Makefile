# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mguillot <mguillot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/08 14:10:13 by pbona             #+#    #+#              #
#    Updated: 2025/08/09 11:30:01 by mguillot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC =	cc
CFLAGS = -Wall -Werror -Wextra -I. -I$(DIR_PRINTF) -I$(DIR_GNL)

#Directories
DIR_CHAR = char
DIR_CONVERSION = conversion
DIR_GNL = ft_get_next_line
DIR_LIST = list
DIR_MEMORY = memory
DIR_OUTPUT = output
DIR_PRINTF = ft_printf
DIR_STRING = string

SRCS = \
	$(DIR_CHAR)/ft_isalnum.c $(DIR_CHAR)/ft_isalpha.c $(DIR_CHAR)/ft_isascii.c $(DIR_CHAR)/ft_isdigit.c $(DIR_CHAR)/ft_isprint.c $(DIR_CHAR)/ft_tolower.c $(DIR_CHAR)/ft_toupper.c \
	$(DIR_CONVERSION)/ft_atoi.c $(DIR_CONVERSION)/ft_itoa.c \
	$(DIR_GNL)/get_next_line_utils.c $(DIR_GNL)/get_next_line.c \
	$(DIR_LIST)/ft_lstadd_back.c $(DIR_LIST)/ft_lstadd_front.c $(DIR_LIST)/ft_lstclear.c $(DIR_LIST)/ft_lstdelone.c $(DIR_LIST)/ft_lstiter.c $(DIR_LIST)/ft_lstlast.c $(DIR_LIST)/ft_lstnew.c $(DIR_LIST)/ft_lstsize.c \
	$(DIR_MEMORY)/ft_bzero.c $(DIR_MEMORY)/ft_calloc.c $(DIR_MEMORY)/ft_memchr.c $(DIR_MEMORY)/ft_memrchr.c $(DIR_MEMORY)/ft_memcmp.c $(DIR_MEMORY)/ft_memcpy.c $(DIR_MEMORY)/ft_memmove.c $(DIR_MEMORY)/ft_memset.c \
	$(DIR_OUTPUT)/ft_putchar_fd.c $(DIR_OUTPUT)/ft_putendl_fd.c $(DIR_OUTPUT)/ft_putnbr_fd.c $(DIR_OUTPUT)/ft_putstr_fd.c \
	$(DIR_PRINTF)/ft_printf.c $(DIR_PRINTF)/ft_printf_conversion1.c $(DIR_PRINTF)/ft_printf_conversion2.c $(DIR_PRINTF)/ft_printf_util.c \
	$(DIR_STRING)/ft_split.c $(DIR_STRING)/ft_strchr.c $(DIR_STRING)/ft_strdup.c $(DIR_STRING)/ft_striteri.c $(DIR_STRING)/ft_strjoin.c $(DIR_STRING)/ft_strlcat.c $(DIR_STRING)/ft_strlcpy.c $(DIR_STRING)/ft_strncpy.c $(DIR_STRING)/ft_strlen.c $(DIR_STRING)/ft_strmapi.c $(DIR_STRING)/ft_strncmp.c $(DIR_STRING)/ft_strnstr.c $(DIR_STRING)/ft_strrchr.c $(DIR_STRING)/ft_strtrim.c $(DIR_STRING)/ft_substr.c \
   
OBJS = $(SRCS:.c=.o) 

HEADERS = \
	libft.h \
	$(DIR_PRINTF)/ft_printf.h \
	$(DIR_GNL)/get_next_line.h \

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

debug:
	@echo "Sources: $(SRCS)"
	@echo "Objetcts: $(OBJS)"
	@echo "Headers : $(HEADERS)"

.PHONY: all clean fclean re debug
