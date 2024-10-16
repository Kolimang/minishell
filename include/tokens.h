/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/16 13:24:22 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

// if heredoc token --> type = 1; else if command arg --> type = 2; else type = 0
typedef struct s_lexemes
{
	int					index;
	char				*str; //"$USER"
	char				*value; // lboumahd
	int					type;
	int					hd_group;
	struct s_lexemes	*next;
}	t_lexemes;

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

void	init_cmd_data(t_cmd_data *data);
void	ft_add_cmd_to_history(char *cmd);
int		is_operator(char c); // add dashes (- & --) in the set ?
char	*find_delim(t_list *tokens);
t_list	*ft_tokenize(char *cmd);
void	lex_handle_operators(char *cmd, int i, t_cmd_data *data);
void	lex_handle_spaces(char *cmd, int i, t_cmd_data *data);
void	lex_handle_quotes(char *cmd, int i, t_cmd_data *data);
void	lex_handle_sq(char *cmd, int i, t_cmd_data *data);
void	lex_handle_dq(char *cmd, int i, t_cmd_data *data);
void	lex_handle_regular(char *cmd, int i, t_cmd_data *data);
int		lex_handle_end_of_cmd(char *cmd, int i, t_cmd_data *data);
t_list	*lex_handle_heredoc(t_cmd_data *dt, char *delim);
//void	lex_handle_dashes(char *cmd, int i, t_cmd_data *data);
void	create_node(char *cmd, int i, t_cmd_data *data, t_list	**list_lexemes);
void	reset_token_data(t_cmd_data *data, char c);
void	set_token_len(char *cmd, int i, t_cmd_data *data);

#endif
