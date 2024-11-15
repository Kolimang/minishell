/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 12:25:03 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// [str]   Original string
// [value] Value after expansion
// [type]  If heredoc token, then type = 1;
// 			else if command arg, then type = 2;
// 			else type = 0
typedef struct s_lexeme
{
	int					index;
	char				*str;
	char				*value;
	int					type;
	int					hd_group;
}	t_lexeme;

typedef struct s_cmd_data
{
	int				bool_in_sq;
	int				bool_in_dq;
	int				bool_heredoc;
	int				bool_endq_sep;
	int				bool_endstr;
	int				bool_delimit_tok;
	int				bool_tok_in_progress;
	int				tok_id;
	int				tok_len;
	unsigned int	tok_start;
}	t_cmd_data;

// check_input.c
int			ft_check_input_cmd(char **cmdref);
int			check_commands(char **cmds, int *i);

// lexemes.c
t_lexeme	*create_lexeme(char *str);
int			init_lexeme(char *lex_str, t_cmd_data *data, t_list	**ls_lxm);

// ... .c
void		init_cmd_data(t_cmd_data *data);
void		ft_add_cmd_to_history(char *cmd);
int			is_operator(char c); // add dashes (- & --) in the set ?
char		*find_delim(t_list *tokens);
t_list		*ft_tokenize(char *cmd);
void		lex_handle_operators(char *cmd, int i, t_cmd_data *data);
void		lex_handle_spaces(char *cmd, int i, t_cmd_data *data);
void		lex_handle_quotes(char *cmd, int i, t_cmd_data *data);
void		lex_handle_sq(char *cmd, int i, t_cmd_data *data);
void		lex_handle_dq(char *cmd, int i, t_cmd_data *data);
void		lex_handle_regular(char *cmd, int i, t_cmd_data *data);
int			lex_handle_end_of_cmd(char *cmd, int i, t_cmd_data *data);
t_list		*lex_handle_heredoc(t_cmd_data *dt, char *delim);
//void		lex_handle_dashes(char *cmd, int i, t_cmd_data *data);
int			create_node(char *cmd, int i, t_cmd_data *data, t_list	**ls_lxm);
void		reset_token_data(t_cmd_data *data, char c);
void		set_token_len(char *cmd, int i, t_cmd_data *data);

#endif
