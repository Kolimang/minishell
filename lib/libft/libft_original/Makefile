# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 15:59:07 by jrichir           #+#    #+#              #
#    Updated: 2024/09/17 10:27:49 by jrichir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --------------------------------- NOTES --------------------------------------

# := defines a simply-expanded variable (is evaluated only once)
# =  defines a recursively-expanded variable (is evaluated every time the 
#    variable occurs in the code)

# Vocabulary
# target(s): dependency(-ies)
#	action(s)

# Targets starting with a dot (.) are not considered by Make as the default
# rule. The same applies to pattern rules that contain the % wildcard.

# In a pattern rule that has multiple targets, ' $@ ' is the name of whichever
# target caused the rule's recipe to be run.

# When wildcard % appears in the dependency list, it is replaced with the same
# string that was used to perform substitution in the target.

# Inside actions we can use:  
#     $@ to represent the full target name of the current target  
#     $? returns the dependencies that are newer than the current target  
#     $* returns the text that corresponds to % in the target     
#     $< returns the name of the first dependency 
#     $^ returns the names of all the dependencies with space as the delimiter

# Command prefixes
#	-	Ignore errors
#	@	Don’t print command
#	+	Run even if Make is in ‘don’t execute’ mode

# Colors
# Usage:	@echo "$(YELLOW)$(TOTAL_FILES) object files compiled.$(CLOSE)"


# ------------------------------- VARIABLES ------------------------------------

NAME := libft_original.a
CC := cc
CFLAGS := -Wall -Wextra -Werror
INC = -I include
AR := ar -cr
RM := rm -f

SRC_DIR := src/
OBJ_DIR := build/

FILES := ft_memset \
		ft_bzero \
		ft_calloc \
		ft_memcpy \
		ft_memmove \
		ft_memchr \
		ft_memcmp \
		ft_strlen \
		ft_strlcpy \
		ft_strlcat \
		ft_strchr \
		ft_strrchr \
		ft_strnstr \
		ft_strncmp \
		ft_atoi \
		ft_isalpha \
		ft_isdigit \
		ft_isalnum \
		ft_isascii \
		ft_isprint \
		ft_toupper \
		ft_tolower \
		ft_strdup \
		ft_strjoin \
		ft_substr \
		ft_strtrim \
		ft_split \
		ft_itoa \
		ft_strmapi \
		ft_striteri \
		ft_putchar_fd \
		ft_putstr_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_lstnew \
		ft_lstadd_front \
		ft_lstsize \
		ft_lstlast \
		ft_lstadd_back \
		ft_lstdelone \
		ft_lstclear \
		ft_lstiter \
		ft_lstmap

SRCS := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

TOTAL_FILES := $(words $(FILES))
CURRENT_FILE = 0


# --------------------------------- RULES --------------------------------------

.PHONY: bonus all clean fclean re .setup

# if the directory to store object files does not exist, create it.
.setup:
	@if [ ! -d $(OBJ_DIR) ]; then \
		mkdir -p $(OBJ_DIR); \
		echo "Create '$(OBJ_DIR)' directory."; \
	fi

all: .setup $(NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "Object files packaged into '$(NAME)' library file (.a archive file)."

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	@if [ $(CURRENT_FILE) -eq $(TOTAL_FILES) ]; then echo "$(TOTAL_FILES) object files compiled.👌"; fi

clean:
	@$(RM) $(OBJS)
	@rm -rf $(OBJ_DIR)
	@echo "Delete libft_orginal object files."

fclean: clean
	@$(RM) $(NAME)
	@echo "Delete libft_original.a library file."

re: fclean all
