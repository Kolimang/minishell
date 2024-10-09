/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/09 16:15:56 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

// JP
void	ft_expand_lexeme_list(t_list *list, t_env *env);

// Lina 
void	handle_sq(char **res, char *tmp, int *i, int start);
void	handle_dq(char **res, char *tmp, int *i, t_env *new_env);
char	*handle_exp(char *tmp, t_lexemes *lexeme, t_env *new_env);
void	process_regular(t_lexemes *lexeme, t_env *new_env);
void	expand_lexeme(t_lexemes *lexeme, t_env *new_env);
void	expander(char **res, char *tmp, int *i, t_env *new_env);
//char	*find_var(char *var, t_env *new_env);
//char	*replace_var(char *tmp, int *i, int start, t_env *new_env);
void	append_to_str(char **res, char *tmp, int end, int start);
void	handle_nq(char **res, char *tmp, int *i, t_env *new_env, t_lexemes *lexeme);
//void	process_hrdoc(t_lexemes *lexeme);
void	dup_word(char **res, char *str, int *i);
//HR
void process_hrdoc(t_lexemes *lexeme, t_env *new_env);
#endif