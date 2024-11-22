/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/22 11:10:29 by jrichir          ###   ########.fr       */
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
	t_list		*ls_lxm;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = -1;
	ls_lxm = NULL;
	while (++i <= (int)ft_strlen(cmd))
	{
		lex_handle_operators(cmd, i, &data);
		//lex_handle_post_operator(cmd, i, &data);//DEBUG added
		lex_handle_spaces(cmd, i, &data);
		lex_handle_quotes(cmd, i, &data);
		lex_handle_regular(cmd, i, &data);
		if (lex_handle_end_of_cmd(cmd, i, &data))
			return (NULL);
		if (create_node(cmd, i, &data, &ls_lxm) == -1)
			return (NULL);
	}
	return (ls_lxm);
}

int	create_node(char *cmd, int i, t_cmd_data *data, t_list	**ls_lxm)
{
	char		*temp_lex_str;
	char		*lex_str;

	if (data->bool_delimit_tok == 1)
	{
		set_token_len(cmd, i, data);
		temp_lex_str = ft_substr(cmd, data->tok_start, (size_t)data->tok_len);
		lex_str = ft_strtrim(temp_lex_str, " ");
		free(temp_lex_str);
		temp_lex_str = NULL;
		if (lex_str[0] != '\0')
		{
			if (init_lexeme(lex_str, data, ls_lxm) == -1)
				return (-1);
		}
		else
			free(lex_str);
		reset_token_data(data, cmd, i);//DEBUG test, before  reset_token_data(data, cmd[i]);
	}
	return (0);
}

//void	reset_token_data(t_cmd_data *data, char c)//DEBUG changed
void	reset_token_data(t_cmd_data *data, char *cmd, int i)//DEBUG changed
{
	if (!data)
		return ;
	if (i > 0)// DEBUG test
		cmd[i - 1] = ' ';//DEBUG test
	data->tok_start += data->tok_len;
	data->tok_id++;
	if (cmd[i] == ' ')
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
