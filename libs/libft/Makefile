# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroue <acroue@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 11:51:52 by acroue            #+#    #+#              #
#    Updated: 2024/01/24 18:50:25 by acroue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_is/ft_isalnum.c \
		ft_is/ft_isalpha.c \
		ft_is/ft_isascii.c \
		ft_is/ft_isdigit.c \
		ft_is/ft_isprint.c \
\
		ft_put/ft_putchar_fd.c \
		ft_put/ft_putendl_fd.c \
		ft_put/ft_putnbr_fd.c \
		ft_put/ft_putstr_fd.c \
\
		Get_next_line/get_next_line.c \
\
		Linked_lists/ft_lstadd_back_bonus.c \
		Linked_lists/ft_lstadd_front_bonus.c \
		Linked_lists/ft_lstclear_bonus.c \
		Linked_lists/ft_lstdelone_bonus.c \
		Linked_lists/ft_lstiter_bonus.c \
		Linked_lists/ft_lstlast_bonus.c \
		Linked_lists/ft_lstmap_bonus.c \
		Linked_lists/ft_lstnew_bonus.c \
		Linked_lists/ft_lstsize_bonus.c \
\
		Memory/ft_bzero.c \
		Memory/ft_calloc.c \
		Memory/ft_memchr.c \
		Memory/ft_memcmp.c \
		Memory/ft_memcpy.c \
		Memory/ft_memmove.c \
		Memory/ft_memset.c \
\
		Numbers/ft_atoi.c \
		Numbers/ft_itoa.c \
		Numbers/ft_random.c \
\
		Printf/ft_printf_basic_functions.c \
		Printf/ft_printf_hex.c \
		Printf/ft_printf_numbers.c \
		Printf/ft_printf.c \
\
		Strings/ft_sep_join.c \
		Strings/ft_split.c \
		Strings/ft_strlen.c \
		Strings/ft_strlcpy.c \
		Strings/ft_strlcat.c \
		Strings/ft_strchr.c \
		Strings/ft_strrchr.c \
		Strings/ft_strncmp.c \
		Strings/ft_strnjoin.c \
		Strings/ft_strnstr.c \
		Strings/ft_strdup.c \
		Strings/ft_substr.c \
		Strings/ft_strjoin.c \
		Strings/ft_strtrim.c \
		Strings/ft_strmapi.c \
		Strings/ft_striteri.c \
		Strings/ft_tolower.c \
		Strings/ft_toupper.c

CC = cc
CFLAGS = -Wall -Wextra -Werror
OBJS = $(SRCS:.c=.o)
NAME = libft.a
RM = rm -f

all: ${NAME}

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

${NAME} : ${OBJS}
	@ar rcs ${NAME} ${OBJS}
