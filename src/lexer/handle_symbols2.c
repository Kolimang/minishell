/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/09 12:31:15 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lex_handle_quotes(char *cmd, int i, t_cmd_data *data)
{
	lex_handle_sq(cmd, i, data);
	lex_handle_dq(cmd, i, data);
}

void	lex_handle_sq(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == '\'')
	{
		if (data->bool_in_dq == 0 && data->bool_in_sq == 1)
		{
			data->bool_in_sq = 0;
			//data->bool_delimit_tok = 1;
			//data->bool_endq_sep = 1;
		}
		else if (data->bool_in_dq == 0 && data->bool_in_sq == 0)
		{
			data->bool_in_sq = 1;
			//if (data->bool_tok_in_progress == 1)
			//	data->bool_delimit_tok = 1;
			//else
			//{
			//	data->bool_tok_in_progress = 1;
			//}
		}
	}
}

void	lex_handle_dq(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == '\"')
	{
		if (data->bool_in_sq == 0 && data->bool_in_dq == 1)
		{
			data->bool_in_dq = 0;
			//data->bool_delimit_tok = 1;
			//data->bool_endq_sep = 1;
		}
		else if (data->bool_in_sq == 0 && data->bool_in_dq == 0)
		{
			data->bool_in_dq = 1;
			//if (data->bool_tok_in_progress == 1)
			//	data->bool_delimit_tok = 1;
			//else
			//	data->bool_tok_in_progress = 1;
		}
	}
}
