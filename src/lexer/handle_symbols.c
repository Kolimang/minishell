/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 14:35:11 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	lex_handle_regular(char *cmd, int i, t_cmd_data *data)
{
	if (!char_in_set("<> \'\"", cmd[i]))
		data->bool_tok_in_progress = 1;
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

int	lex_handle_end_of_cmd(char *cmd, int i, t_cmd_data *data)
{
	if (cmd[i] == '\0')
	{
		data->bool_endstr = 1;
		data->bool_delimit_tok = 1;
		if (data->bool_in_sq == 1 || data->bool_in_dq == 1)
			return (merror(NULL, NULL, NULL, 774));
	}
	return (0);
}
