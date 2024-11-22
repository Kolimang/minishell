/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/22 02:41:32 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operator(char c)
{
	char	*set;

	set = "<>";
	return (char_in_set(set, c));
}

void	lex_handle_operators(char *cmd, int i, t_cmd_data *data)
{
	if (!is_operator(cmd[i]))
		return ;
	if (data->bool_in_sq == 0 && data->bool_in_dq == 0)
	{
		if (i > 0 && !is_operator(cmd[i - 1])
			&& data->bool_tok_in_progress == 1)
			data->bool_delimit_tok = 1;
		else if (i > 0 && is_operator(cmd[i - 1]))
		{
			if (cmd[i - 1] == '>' && cmd[i] == '<')
				data->bool_delimit_tok = 1;
			else if (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '>')
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

void	lex_handle_post_operator(char *cmd, int i, t_cmd_data *data)
{
	if (!is_operator(cmd[i]) && i > 0 && is_operator(cmd[i - 1]))
	{
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
}

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
