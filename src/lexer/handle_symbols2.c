/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 17:19:47 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_quotes(char *cmd, int i, t_cmd_data *data)
{
	handle_sq(cmd, i, data);
	handle_dq(cmd, i, data);
}

void	handle_sq(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == '\'')
	{
		if (data->bool_in_dq == 0 && data->bool_in_sq == 1)
		{
			data->bool_in_sq = 0;
			data->bool_delimit_tok = 1;
			data->bool_endq_sep = 1;
		}
		else if (data->bool_in_dq == 0 && data->bool_in_sq == 0)
		{
			data->bool_in_sq = 1;
			if (data->bool_tok_in_progress == 1)
				data->bool_delimit_tok = 1;
			else
			{
				data->bool_tok_in_progress = 1;
			}
		}
	}
}

void	handle_dq(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == '\"')
	{
		if (data->bool_in_sq == 0 && data->bool_in_dq == 1)
		{
			data->bool_in_dq = 0;
			data->bool_delimit_tok = 1;
			data->bool_endq_sep = 1;
		}
		else if (data->bool_in_sq == 0 && data->bool_in_dq == 0)
		{
			data->bool_in_dq = 1;
			if (data->bool_tok_in_progress == 1)
				data->bool_delimit_tok = 1;
			else
				data->bool_tok_in_progress = 1;
		}
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
