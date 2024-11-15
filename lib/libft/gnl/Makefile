# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 15:59:07 by jrichir           #+#    #+#              #
#    Updated: 2024/11/14 13:49:55 by jrichir          ###   ########.fr        #
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

NAME := gnl.a
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
    CC			:=	cc -g3 -fno-omit-frame-pointer -Wno-unused-result
else
    CC			:=	cc -g3 -fno-omit-frame-pointer
endif
CFLAGS := -Wall -Wextra -Werror
INC := -I include
AR := ar -cr
RM := rm -f

SRC_DIR := src/
OBJ_DIR := build/

FILES := get_next_line \
		get_next_line_utils

SRCS := $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS := $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

TOTAL_FILES := $(words $(FILES))
CURRENT_FILE = 0


# --------------------------------- RULES --------------------------------------

.PHONY: all clean fclean re .setup

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
	@echo "Delete gnl object files."

fclean: clean
	@$(RM) $(NAME)
	@echo "Delete gnl.a library file."

re: fclean all
