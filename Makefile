# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/26 22:18:44 by jrichir           #+#    #+#              #
#    Updated: 2024/11/22 03:00:07 by jrichir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ------------------------------- VARIABLES ------------------------------------

ROOT_DIR  := $(realpath .)
INC_DIR   := $(ROOT_DIR)/include

SRC_DIR   := src/
OBJ_DIR   := build/

NAME      := minishell

CC		  := cc
CFLAGS    := -I$(INC_DIR) -g3 -Wall -Wextra -Werror

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CFLAGS			+=	-Wno-unused-result
	LIBREADLFLAGS	:= -lreadline
else
#	Paths to readline library (installed with brew)
	ifeq ($(USER), jrichir)
		RL_H    	:= /Users/jrichir/.brew/opt/readline/include
		RL_LIB  	:= /Users/jrichir/mybin/opt/readline/lib
	else
		RL_LIB  	:= /Users/lboumahd/.brew/opt/readline/lib
		RL_H    	:= /Users/lboumahd/.brew/opt/readline/include
	endif
	LIBREADLFLAGS 	:= -I$(RL_H) -L$(RL_LIB) -lreadline
endif

LIBFT     := lib/libft/libft.a

RM        := rm -f

FILES     := 	builtins/cd \
				builtins/cd2 \
				builtins/echo \
				builtins/env \
				builtins/exit \
				builtins/export \
				builtins/pwd \
				builtins/unset\
				env/env_free \
				env/env_init \
				env/env_print \
				env/env_sort \
				env/env_update \
				env/env_utils \
				exec/exec_builtins \
				exec/exec_child_utils \
				exec/exec_parent\
				exec/exec_child \
				exec/exec_hrdoc \
				exec/exec_paths \
				exec/exec_redir_in \
				exec/exec_redir_out \
				exec/exec_utils \
				exec/execute \
				expander/exp_hr \
				expander/expander_helper \
				expander/expander \
				lexer/check_input \
				lexer/handle_symbols1 \
				lexer/handle_symbols2 \
				lexer/heredoc \
				lexer/history \
				lexer/lexemes \
				lexer/tokenize \
				parser/parse_cmd \
				parser/parser_utils \
				signals/signals \
				signals/signals2 \
				utils/errors \
				utils/errors2 \
				utils/free \
				utils/print \
				utils/utils \
				utils/utils2 \
				minishell

SRCS      := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS      := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

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

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@) # Create the directory for the object file if it doesn't exist
	$(CC) $(CFLAGS) -c $< -o $@

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
