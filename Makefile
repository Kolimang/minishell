# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 22:18:44 by jrichir           #+#    #+#              #
#    Updated: 2024/10/07 10:38:12 by jrichir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------- VARIABLES ------------------------------------

ROOT_DIR  := $(realpath .)
INC_DIR   := $(ROOT_DIR)/include
SRC_DIR   := src/
OBJ_DIR   := build/

NAME      := minishell
CC        := gcc -g

# Paths to readline library (installed with brew)
ifeq ($(USER), jrichir)
	RL_H    := /Users/jrichir/mybin/opt/readline/include
	RL_LIB  := /Users/jrichir/mybin/opt/readline/lib
else
	RL_LIB  := /Users/lboumahd/.brew/opt/readline/lib
	RL_H    := /Users/lboumahd/.brew/opt/readline/include
endif

CFLAGS    := -I$(INC_DIR) -Wall -Wextra -Werror -g -fsanitize=address

LIBFT     := lib/libft/libft.a

LIBREADLFLAGS := -I$(RL_H) -L$(RL_LIB) -lreadline

RM        := rm -f

# Use wildcard to collect all .c files recursively in src/ and subdirectories
SRCS := $(wildcard $(SRC_DIR)*/*.c) $(wildcard $(SRC_DIR)*/**/*.c)
OBJS := $(OBJ_DIR)minishell.o $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS:$(SRC_DIR)minishell.c=))

#Back-up:
#FILES     := minishell
#SRCS      := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
#OBJS      := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# --------------------------------- RULES --------------------------------------

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	@echo "\033[1;34mBuilding \033[1;32m$(NAME)\033[1;34m program...\033[0m"
	@echo "\033[1;33m"
	@echo "  __  __ _       _      _          _ _   ﾟ ‧  ✩"
	@echo " |  \/  (_)     (_)    | |        | | |  ☾   ⋆ "
	@echo " | \  / |_ _ __  _  ___| |__   ___| | |  ⋆ ‧ ₊ "
	@echo " | |\/| | | '_ \| |/ __| '_ \ / _ \ | | ✩ ‧ ⋆ ‧"
	@echo " | |  | | | | | | |\__ \ | | |  __/ | |  ₊ ⋆ ‧ "
	@echo " |_|  |_|_|_| |_|_||___/_| |_|\___|_|_| ⋆  ﾟ ✩ "
	@echo "\033[0m"
	@$(CC) $(OBJS) $(CFLAGS) $(LIBREADLFLAGS) $(LIBFT) -o $@

$(LIBFT):
	@make -C lib/libft/

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
	fi

# Ensure the directory structure for object files exists before compiling
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) # Create the directory for the object file if it doesn't exist
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C lib/libft/
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "Deleted $(NAME) object files and dependencies."

fclean: clean
	make fclean -C lib/libft/
	@$(RM) $(NAME)
	@echo "Deleted $(NAME) program."

re: fclean all
