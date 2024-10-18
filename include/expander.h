/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/18 15:58:21 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

void	ft_expand_lexeme_list(t_list *list, t_env *env);
void	handle_sq(char **res, char *tmp, int *i, int start);
void	handle_dq(char **res, char *tmp, int *i, t_env *new_env);
char	*handle_exp(char *tmp, t_lexeme *lex, t_env *new_env);
void	process_regular(t_lexeme *lex, t_env *new_env);
void	process_hrdoc(char *line, t_env *new_env);
void	expand_lexeme(t_lexeme *lex, t_env *new_env);
void	expander(char **res, char *tmp, int *i, t_env *new_env);
void	append_to_str(char **res, char *tmp, int end, int start);
void	handle_nq(char **res, char *tmp, int *i, t_env *new_env,
			t_lexeme *lex);
void	dup_word(char **res, char *str, int *i);

#endif
