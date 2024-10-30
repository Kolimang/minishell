# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/20 12:26:19 by jrichir           #+#    #+#              #
#    Updated: 2024/10/29 09:57:06 by jrichir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libftprintf.a

CC				=	cc -g2 -O1 -fno-omit-frame-pointer
CFLAGS			=	-Wall -Wextra -Werror
INC				=	-I include
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf

SRC				=	ft_printf \
					ft_printf_utils_str \
					ft_printf_utils_nb \
					ft_printf_char \
					ft_printf_hex \
					ft_printf_int \
					ft_printf_ptr \
					ft_printf_str \
					ft_printf_u


SRC_DIR			=	src
OBJ_DIR			=	build

SRCS 			=	$(addsuffix .c, $(SRC))
OBJS			=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

TOTAL_FILES := $(words $(SRC))
CURRENT_FILE = 0

# --------------------------------- RULES --------------------------------------

# if the directory to store object files does not exist, create it.
#.setup:
#	@if [ ! -d $(OBJ_DIR) ]; then \
#		mkdir -p $(OBJ_DIR); \
#		echo "Create '$(OBJ_DIR)' directory."; \
#	fi

.PHONY:				all clean fclean re libftprintf

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c
					@mkdir -p $(OBJ_DIR)
					@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
					@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
					@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo "$(TOTAL_FILES) object files compiled.👌"; fi

all:				$(NAME)

$(NAME):			$(OBJS)
					@$(AR) $(ARFLAGS) $(NAME) $(OBJS)
					@echo "Object files packaged into '$(NAME)' library file (.a archive file)."

#$(NAME):			$(OBJ_DIR) $(OBJS)
#					$(AR) $(ARFLAGS) $(NAME) $(OBJS)

#$(OBJ_DIR):
#					mkdir -p $(OBJ_DIR)

clean:
					@$(RM) $(OBJ_DIR)
					@echo "Delete ft_printf object files."

fclean:				clean
					@$(RM) $(NAME)
					@echo "Delete libftprintf.a library file."

re:					fclean all
