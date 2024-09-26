/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/24 12:08:24 by lboumahd         ###   ########.fr       */
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
# define SQ 39
# define DQ 34
//SQ DQ changed
enum lex_types
{
	INPUT,
	OUTPUT,
	HD_DELIMITER,
	OUT_APPEND,
	SQ,
	DQ,
	OPERATOR,
	EXEC,
	ARGS
};

typedef struct s_lexems
{
	int		index;
	char 	*str;
	char	*value; //set q null, contient la vraie valeur de retour de lex
	enum lex_types type;
	t_lexems *next;
}	t_lexems;

typedef struct s_env
{
	char *var;
	int	index;
	t_env *next;
}t_env;


#endif