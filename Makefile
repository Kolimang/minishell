# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 22:18:44 by jrichir           #+#    #+#              #
#    Updated: 2024/09/16 11:09:09 by lboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------- VARIABLES ------------------------------------

ROOT_DIR  := $(realpath .)
INC_DIR   := $(ROOT_DIR)/include
SRC_DIR   := src/
OBJ_DIR   := build/

NAME      := minishell
CC        := gcc

#readline library (installed with brew)
#jefaisdesconflits
ifeq ($(USER), jrichir)
	RL_H    := /Users/jrichir/mybin/opt/readline/include
	RL_LIB  := /Users/jrichir/mybin/opt/readline/lib
else
	RL_LIB  := /Users/lboumahd/.brew/opt/readline/lib
	RL_H    := /Users/lboumahd/.brew/opt/readline/include
endif

#TEST COMMENT
CFLAGS    := -I$(INC_DIR) -Wall -Wextra -Werror

RM        := rm -f

FILES     := minishell

SRCS      := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# --------------------------------- RULES --------------------------------------

.PHONY: bonus all clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS)
	@echo "Build $(NAME) program."
	@$(CC) $(OBJS) $(CFLAGS) -I$(RL_H) -L$(RL_LIB) -lreadline -o $@

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "Delete $(NAME) object files and dependencies."

fclean: clean
	@$(RM) $(NAME)
	@echo "Delete $(NAME) program."

re: fclean all
