/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 16:13:32 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// add dashes (- & --) or dot/slash in the set ?
int	is_operator(char c)
{
	char	*set;

	set = "<|>";
	return (char_in_set(set, c));
}

void	handle_operators(char *cmd, int i, t_cmd_data *data)
{
	if (is_operator(cmd[i]))
	{
		if (data->bool_in_sq == 0 && data->bool_in_dq == 0)
		{
			if (i > 0 && !is_operator(cmd[i - 1]) && data->bool_tok_in_progress == 1)
				data->bool_delimit_tok = 1;
			else if (i > 0 && is_operator(cmd[i - 1]))
			{
				if (cmd[i - 1] != cmd[i])
					data->bool_delimit_tok = 1;
				else if (cmd[i] == '<')
					data->bool_heredoc = 1;
			}
		}
		else if (data->bool_in_sq == 1 || data->bool_in_dq == 1)
			data->bool_tok_in_progress = 1;
	}
	else if (i > 0 && is_operator(cmd[i - 1]))
		data->bool_delimit_tok = 1;
}

void	handle_spaces(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == ' ')
	{
		if (data->bool_tok_in_progress == 1 && data->bool_in_sq == 0 && data->bool_in_dq == 0)
				data->bool_delimit_tok = 1;
		else if (data->bool_tok_in_progress == 0 && data->bool_in_sq == 0 && data->bool_in_dq == 0)
			data->tok_start += 1;
		else if (data->bool_in_sq == 1 || data->bool_in_dq == 1)
			data->bool_tok_in_progress = 1;
	}
}

void	handle_regular(char *cmd, int i, t_cmd_data *data)
{
	if (!char_in_set("<> '\"", cmd[i]))
		data->bool_tok_in_progress = 1;
}

void	handle_end_of_cmd(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i + 1] == '\0')
	{
		data->bool_endstr = 1;
		data->bool_delimit_tok = 1;
		if (data->bool_in_sq == 1 || data->bool_in_dq == 1)
			printf("ERROR: unclosed quote.\n");
	}
}
