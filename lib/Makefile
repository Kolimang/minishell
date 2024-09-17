# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/10 15:59:07 by jrichir           #+#    #+#              #
#    Updated: 2024/09/17 11:12:46 by lboumahd         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re

all:
	@echo "Make libft"
	@(cd libft_original; make all)
	@echo "Make ft_printf"
	@(cd ft_printf; make all)
	@echo "Make gnl"
	@(cd gnl; make all)
	@mkdir -p temp ; \
	cd temp ; \
	ar -x ../libft_original/libft_original.a ; \
	ar -x ../ft_printf/libftprintf.a ; \
	ar -x ../gnl/gnl.a ; \
	ar -rcs ../libft.a *.o ; \
	echo "Archiving libraries into expanded libft.a file." ; \
	cd .. ; \
	rm -rf temp

clean:
	@(cd libft_original ; make clean)
	@(cd ft_printf ; make clean)
	@(cd gnl ; make clean)

fclean:
	@(cd libft_original ; make fclean)
	@(cd ft_printf ; make fclean)
	@(cd gnl ; make fclean)
	@rm -f libft.a
	@echo "Delete expanded libft.a library file."

re: fclean all
