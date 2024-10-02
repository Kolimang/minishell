/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/02 17:46:07 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
 #include <string.h>
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
	OPERATOR,
	EXEC,
	ARGS
};

typedef enum {
    LEX_TYPE_1, // Define actual types based on your context
    LEX_TYPE_2,
    // Add other types as needed
} lex_types;

typedef struct s_lexems
{
    int index;
    char *str;
    char *value;
    enum lex_types type;
    struct s_lexems *next;
} t_lexems;

typedef struct s_env
{
    char *var_name;
    char *var_val;
    int index;
    struct s_env *next;
} t_env;


// Expander 
void handle_SQ(char **res, char *tmp, int *i, int start);
void handle_DQ(char **res, char *tmp, int *i,  t_env *new_env);
char *handle_exp(char *tmp, t_lexems *lexeme, t_env *new_env);
void process_regular(t_lexems *lexeme, t_env *new_env);
void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag);
void expander(char **res, char *tmp, int *i, t_env *new_env);
char *find_var(char *var, t_env *new_env);
char *replace_var(char *tmp, int *i, int start, t_env *new_env);
void append_to_str(char **res, char *tmp, int end, int start);

// To deploy 
void handle_NQ(char **res, char *tmp, int *i, t_env *new_env, t_lexems *lexeme);
void process_HRDOC(t_lexems *lexeme);

//lol
char	*ft_strldup(char *s, int max_len);
// static char	*expand(char *str, t_env *local_env);

// static char	*handle_dollar(char *str, int *i, t_env *local_env);

// char	*expaner(char *str, t_env *new_env);

// char	*dup_word(char *str, int *i);

#endif