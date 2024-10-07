/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 17:19:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Include library headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// Include project headers
# include "tokens.h"
# include "utils.h"

int	g_ret_value;
# define SQ 39
# define DQ 34
//SQ DQ changed

typedef struct s_lexems
{
    int index;
    char *str; //"$USER"
    char *value; // lboumahd
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
void handle_sq(char **res, char *tmp, int *i, int start);
void handle_dq(char **res, char *tmp, int *i,  t_env *new_env);
char *handle_exp(char *tmp, t_lexems *lexeme, t_env *new_env);
void process_regular(t_lexems *lexeme, t_env *new_env);
void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag);
void expander(char **res, char *tmp, int *i, t_env *new_env);
//char *find_var(char *var, t_env *new_env);
//char *replace_var(char *tmp, int *i, int start, t_env *new_env);
void append_to_str(char **res, char *tmp, int end, int start);
void handle_nq(char **res, char *tmp, int *i, t_env *new_env, t_lexems *lexeme);
void process_HRDOC(t_lexems *lexeme);
void dup_word(char **res, char *str, int *i);

// Env
t_env	*init_env(char **original_env);
void	add_env_var(t_env **env, const char *var_name, const char *var_val,
		int index);
char	*get_env_var(t_env *env, const char *var_name);
t_env	*create_env_node(const char *var_name, const char *var_val, int index);
void	free_env(t_env *env);

#endif