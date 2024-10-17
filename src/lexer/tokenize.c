/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/17 14:23:24 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_cmd_data(t_cmd_data *data)
{
	data->bool_in_sq = 0;
	data->bool_in_dq = 0;
	data->bool_endq_sep = 0;
	data->bool_endstr = 0;
	data->bool_heredoc = 0;
	data->bool_delimit_tok = 0;
	data->bool_tok_in_progress = 0;
	data->tok_id = 0;
	data->tok_len = 0;
	data->tok_start = 0;
}

t_list	*ft_tokenize(char *cmd)
{
	int			i;
	t_cmd_data	data;
	t_list		*ls_lexemes;
	t_list		*ls_hd_lexemes;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = -1;
	ls_lexemes = NULL;
	ls_hd_lexemes = NULL;
	while (++i <= (int)ft_strlen(cmd))
	{
		lex_handle_operators(cmd, i, &data);
		lex_handle_spaces(cmd, i, &data);
		lex_handle_quotes(cmd, i, &data);
		lex_handle_regular(cmd, i, &data);
		if (lex_handle_end_of_cmd(cmd, i, &data))
			return (NULL);
		create_node(cmd, i, &data, &ls_lexemes);
	}
	//ls_hd_lexemes = lex_handle_heredoc(&data, find_delim(ls_lexemes));
	//if (ls_hd_lexemes)
	//	ft_lstadd_back(&ls_lexemes, ls_hd_lexemes);
	return (ls_lexemes);
}

void	create_node(char *cmd, int i, t_cmd_data *data, t_list	**ls_lexemes)
{
	char		*temp_lex_str;
	char		*lex_str;
	t_lexeme	*lex;

	if (data->bool_delimit_tok == 1)
	{
		set_token_len(cmd, i, data);
		temp_lex_str = ft_substr(cmd, data->tok_start, (size_t)data->tok_len);
		lex_str = ft_strtrim(temp_lex_str, " ");
		free(temp_lex_str);
		if (lex_str[0] != '\0')
		{
			lex = malloc(sizeof(t_lexeme));
			lex->index = data->tok_id;
			lex->str = lex_str;
			lex->value = NULL;
			lex->type = 0;
			if (!*ls_lexemes)
				*ls_lexemes = ft_lstnew(lex);
			else
				ft_lstadd_back(ls_lexemes, ft_lstnew(lex));
		}
		else
			free(lex_str);
		reset_token_data(data, cmd[i]);
	}
}

int	init_lexeme()
{
	
	return (0);
}

void	reset_token_data(t_cmd_data *data, char c)
{
	if (!data)
		return ;
	data->tok_start += data->tok_len;
	data->tok_id++;
	if (c == ' ')
		data->bool_tok_in_progress = 0;
	data->bool_delimit_tok = 0;
}

void	set_token_len(char *cmd, int i, t_cmd_data *data)
{
	if (!cmd || !data)
		return ;
	if (&cmd[i] == &cmd[data->tok_start])
		data->tok_len = 1;
	else
		data->tok_len = &cmd[i] - &cmd[data->tok_start];
	if (data->bool_endq_sep == 1)
	{
		data->bool_endq_sep = 0;
		data->tok_len += 1;
	}
}
