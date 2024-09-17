/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 14:05:58 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

int	ret_value;

enum lex_types
{
	INPUT = 0,
	OUTPUT = 1,
	HD_DELIMITER = 2,
	OUT_APPEND = 3,
	SQ_STRING = 4,
	DQ_STRING = 5,
	OPERATOR = 6,
	EXEC = 7,
	ARGS = 8
};

typedef struct s_lexems
{
	int		index;
	char 	*value;
	int		type;
}	t_lexems;

#endif