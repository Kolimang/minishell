# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 22:18:44 by jrichir           #+#    #+#              #
#    Updated: 2024/09/16 16:24:47 by jrichir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------- VARIABLES ------------------------------------

ROOT_DIR  := $(realpath .)
INC_DIR   := $(ROOT_DIR)/include
SRC_DIR   := src/
OBJ_DIR   := build/

NAME      := minishell
CC        := gcc

#Paths to readline library (installed with brew)
ifeq ($(USER), jrichir)
	RL_H    := /Users/jrichir/mybin/opt/readline/include
	RL_LIB  := /Users/jrichir/mybin/opt/readline/lib
else
	RL_LIB  := /Users/lboumahd/.brew/opt/readline/lib
	RL_H    := /Users/lboumahd/.brew/opt/readline/include
endif

CFLAGS    := -I$(INC_DIR) -Wall -Wextra -Werror

LIBREADLN := -I$(RL_H) -L$(RL_LIB) -lreadline

LIBFT_H := lib/libft
LIBFT_LIB := lib/libft
 
LIBFT     := -I$(LIBFT_H) -L$(LIBFT_LIB) -lft

RM        := rm -f

FILES     := minishell

SRCS      := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

# --------------------------------- RULES --------------------------------------

.PHONY: bonus all clean fclean re

all: $(NAME)

#$(NAME): $(OBJ_DIR) $(LIBFT_M) $(OBJS)
$(NAME): $(OBJ_DIR) $(OBJS)
	@(cd include/libftx ; make all)
#	@$(CC) $(CFLAGS) ./include/libftx/libft.a $(OBJS) -o $@
	@echo "Build $(NAME) program."
	@$(CC) $(OBJS) $(CFLAGS) $(LIBREADLN) $(LIBFT) -o $@

# LIBFT_M:
# 	make -C lib/libft/

$(OBJ_DIR):
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
	fi

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@(cd lib/libft ; make clean)
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "Delete $(NAME) object files and dependencies."

fclean: clean
	@(cd lib/libft ; make fclean)
	@$(RM) $(NAME)
	@echo "Delete $(NAME) program."

re: fclean all
