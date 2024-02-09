# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: acroue <acroue@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/11 11:51:52 by acroue            #+#    #+#              #
#    Updated: 2024/02/09 19:50:42 by acroue           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME = pipex
BONUS = pipex_bonus

# Colors
DEFAULT    = \033[0m
BLACK    = \033[0;30m
RED        = \033[0;31m
GREEN    = \033[0;32m
YELLOW    = \033[0;33m
BLUE    = \033[0;34m
PURPLE    = \033[0;35m
CYAN    = \033[0;36m
BWHITE    = \033[1;37m

# Directories
LIBS_DIR = libs
SRCS_DIR = srcs
INCS_DIR = includes
BONUS_DIR = bonus
OBJS_DIR = objs
LIBFT_DIR = $(LIBS_DIR)/libft

# Files
LIBFT = $(LIBFT_DIR)/libft.a

define LIB :=
	$(LIBFT)
endef
LIB := $(strip $(LIB))

define INCLUDES :=
	$(INCS_DIR)
	$(LIBFT_DIR)
endef
INCLUDES := $(strip $(INCLUDES))

define SRC :=
	main.c
	forks.c
	exec.c
	here_doc.c
endef
SRC := $(strip $(SRC))

define BONUS_SRC :=
	$(addprefix $(BONUS_DIR)/, salut_bonus.c)
endef
BONUS_SRC := $(strip $(BONUS_SRC))

OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(SRC))
BONUS_OBJ := $(patsubst %.c,$(OBJS_DIR)/%.o,$(BONUS_SRC))

# Utils
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf
INCLUDES_FLAGS := $(addprefix -I , $(INCLUDES))
LIB_FLAGS = --no-print-directory --silent

# Rules
all: $(NAME)

$(NAME): $(LIBFT) $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@echo "$(CYAN)- Compiling$(DEFAULT) $<"
	@mkdir -p $(OBJS_DIR)/$(BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES_FLAGS) -c $< -o $@

clean:
	@echo "$(RED)! Removing$(DEFAULT) ${OBJS_DIR} files"
	@${RM} ${OBJS_DIR}

fclean: clean
	@echo "$(RED)! Removing$(DEFAULT) $(NAME)"
	@$(RM) $(NAME)
	@echo "$(RED)! Removing$(DEFAULT) $(BONUS)"
	@$(RM) $(BONUS)

re: fclean all

$(LIBFT):
	@echo "$(CYAN)~ Compiling$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make -C $(LIBFT_DIR) $(LIB_FLAGS)

cleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make clean -C $(LIBFT_DIR) $(LIB_FLAGS)

fcleanlib:
	@echo "$(RED)! Removing$(DEFAULT) $(PURPLE)$(LIBFT_DIR)$(DEFAULT)"
	@make fclean -C $(LIBFT_DIR) $(LIB_FLAGS)

relib: fcleanlib $(LIBFT)

bonus: $(BONUS)

$(BONUS): $(LIBFT) $(OBJ)
	@echo "$(GREEN)* Assembling $(BWHITE)$@$(DEFAULT)"
	@$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(BONUS)

cre:
	@clear
	@make re --no-print-directory

norm:
	@norminette $(SRCS_DIR) $(INCS_DIR) $(BONUS_DIR) | awk '/'Error'/ {print; found=1} END {if (!found) print "$(PURPLE)Norm O.K.$(DEFAULT)"}'
	@norminette $(LIBFT_DIR) | awk '/'Error'/ {print; found=1} END {if (!found) print "$(YELLOW)Norm libft O.K.$(DEFAULT)"}'

valerie: cre
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME)

example:
	@cc example.c -p example

stdout:
	@cc -g stdout.c libs/libft/libft.a
