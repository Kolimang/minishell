/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 14:27:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	updt_quote_status(char c, int *in_sq, int *in_dq)
{
	if (c == '\'' && !*in_dq)
		switch_bool(in_sq);
	else if (c == '\"' && !*in_sq)
		switch_bool(in_dq);
}

int	in_quotes(t_cmd_data *data)
{
	return (data->bool_in_dq || data->bool_in_sq);
}

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
		}
		else if (data->bool_in_dq == 0 && data->bool_in_sq == 0)
		{
			data->bool_in_sq = 1;
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
		}
		else if (data->bool_in_sq == 0 && data->bool_in_dq == 0)
		{
			data->bool_in_dq = 1;
		}
	}
}
