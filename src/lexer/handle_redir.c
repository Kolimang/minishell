/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_symbols1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/27 14:36:11 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_redir_chr(char c)
{
	char	*set;

	set = "<&>|";
	return (char_in_set(set, c));
}

void	lex_matching_operators(char *cmd, int i, t_cmd_data *data)
{
	if ((i > 0 && cmd[i - 1] == '>' && cmd[i] == '<')
		|| (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '&')
		|| (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '&')
		|| (i > 1 && cmd[i - 2] == '&' && cmd[i - 1] == '>')
		|| (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '|')
		|| (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '>')
		|| (i > 2 && cmd[i - 3] == '<' && cmd[i - 2] == '<'
			&& cmd[i - 1] == '<')
		|| (i > 1 && cmd[i - 2] == '<' && cmd[i - 1] == '<'
			&& cmd[i] != '<')
		|| (i > 1 && cmd[i - 2] == '>' && cmd[i - 1] == '>')
		|| (i > 0 && cmd[i - 1] == '<' && cmd[i] == '|')
		|| (is_redir_chr(cmd[i - 1]) && !is_redir_chr(cmd[i])))
		data->bool_delimit_tok = 1;
	else if (cmd[i - 1] == '<' && cmd[i] == '<')
		if ((!cmd[i + 1] || (cmd[i + 1] && cmd[i + 1] != '<'))
			&& (!cmd[i - 2] || (cmd[i - 2] && cmd[i - 2] != '<')))
			data->bool_heredoc = 1;
}

void	lex_handle_operators(char *cmd, int i, t_cmd_data *data)
{
	if (!in_quotes(data))
	{
		if (is_redir_chr(cmd[i]) && i > 0 && !is_redir_chr(cmd[i - 1])
			&& data->bool_tok_in_progress == 1)
			data->bool_delimit_tok = 1;
		else if (i > 0 && is_redir_chr(cmd[i - 1]))
			lex_matching_operators(cmd, i, data);
	}
	data->bool_tok_in_progress = 1;
}
