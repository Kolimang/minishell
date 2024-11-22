/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/22 11:50:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redir_chr(char c)
{
	char	*set;

	set = "<&>|";// DEBUG added pipe for test
	return (char_in_set(set, c));
}

int	in_quotes(t_cmd_data *data)
{
	return (data->bool_in_dq || data->bool_in_sq);
}

void	lex_handle_operators(char *cmd, int i, t_cmd_data *data)
{
	if (!in_quotes(data))
	{
		if (is_redir_chr(cmd[i]) && i > 0 && !is_redir_chr(cmd[i - 1])
			&& data->bool_tok_in_progress == 1)
			data->bool_delimit_tok = 1;
		else if (i > 0 && is_redir_chr(cmd[i - 1]))
		{
			if (i > 0 && cmd[i - 1] == '>' && cmd[i] == '<')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '&')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '&')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '&' && cmd[i - 1] == '>')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '|')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '>')
				data->bool_delimit_tok = 1;
			else if (i > 2 && cmd[i - 3] == '<' && cmd[i - 2] == '<'
						&& cmd[i - 1] == '<')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '<'
						&& cmd[i] != '<')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '>')
				data->bool_delimit_tok = 1;
			else if (cmd[i - 1] == '<' && cmd[i] == '<')
				if ((!cmd[i + 1] || (cmd[i + 1] && cmd[i + 1] != '<'))
					&& (!cmd[i - 2] || (cmd[i - 2] && cmd[i - 2] != '<')))
				data->bool_heredoc = 1;
		}
	}
	data->bool_tok_in_progress = 1;
}
/*
void	lex_handle_post_operator(char *cmd, int i, t_cmd_data *data)
{
	if (!in_quotes(data))
	{
		data->bool_tok_in_progress = 1;
		return ;
	}
	if (!in_quotes(data) && !is_redir_chr(cmd[i]) && i > 0
		&& is_redir_chr(cmd[i - 1]))
	{
		data->bool_tok_in_progress = 1;
		if (cmd[i] != '&' && cmd[i] != '|')
			data->bool_delimit_tok = 1;
		else if (cmd[i] == '|')
		{
			if (cmd[i -1] != '>')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i -2] == '>')
				data->bool_delimit_tok = 1;
		}
	}
	else if (!in_quotes(data) && i > 1 && char_in_set("&|", cmd[i - 1])
				&& is_redir_chr(cmd[i -2]))
		ft_printf("Pouet\n");//DEBUG
		if (!(cmd[i - 1] == '|' && cmd[i - 2] == '<'))
			data->bool_delimit_tok = 1;
	// else precedent == &...
}
*/
void	lex_handle_spaces(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == ' ')
	{
		if (data->bool_tok_in_progress == 1
			&& data->bool_in_sq == 0
			&& data->bool_in_dq == 0)
			data->bool_delimit_tok = 1;
		else if (data->bool_tok_in_progress == 0
			&& data->bool_in_sq == 0
			&& data->bool_in_dq == 0
			&& cmd[i + 1] != '\0')
			data->tok_start += 1;
		else if (data->bool_in_sq == 1 || data->bool_in_dq == 1)
			data->bool_tok_in_progress = 1;
	}
}

void	lex_handle_regular(char *cmd, int i, t_cmd_data *data)
{
	if (!char_in_set("<> \'\"", cmd[i]))
		data->bool_tok_in_progress = 1;
}
