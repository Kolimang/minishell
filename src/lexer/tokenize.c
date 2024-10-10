/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/10 17:01:36 by jrichir          ###   ########.fr       */
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
	t_list		*list_lexemes;
	t_list		*list_hd_lexemes;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = -1;
	list_lexemes = NULL;
	list_hd_lexemes = NULL;
	while (++i <= (int)ft_strlen(cmd))
	{
		lex_handle_operators(cmd, i, &data);
		lex_handle_spaces(cmd, i, &data);
		lex_handle_quotes(cmd, i, &data);
		lex_handle_regular(cmd, i, &data);
		if (lex_handle_end_of_cmd(cmd, i, &data))
			return (NULL);
		create_node(cmd, i, &data, &list_lexemes);
	}
	list_hd_lexemes = lex_handle_heredoc(&data, find_delim(list_lexemes));
	if (list_hd_lexemes)
		ft_lstadd_back(&list_lexemes, list_hd_lexemes);
	return (list_lexemes);
}

void	create_node(char *cmd, int i, t_cmd_data *data, t_list	**list_lexemes)
{
	char		*templexeme_str;
	char		*lexeme_str;
	t_lexemes	*lexeme;

	if (data->bool_delimit_tok == 1)
	{
		set_token_len(cmd, i, data);
		// printf("i: %d - tokenlen: %d\n", i, data->tok_len); // For DEBUGGING
		templexeme_str = ft_substr(cmd, data->tok_start, (size_t)data->tok_len);
		lexeme_str = ft_strtrim(templexeme_str, " ");
		free(templexeme_str);
		if (lexeme_str[0] != '\0')
		{
			lexeme = malloc(sizeof(t_lexemes));
			lexeme->index = data->tok_id;
			lexeme->str = lexeme_str;
			lexeme->value = NULL;
			lexeme->type = 0;
			if (!*list_lexemes)
				*list_lexemes = ft_lstnew(lexeme);
			else
				ft_lstadd_back(list_lexemes, ft_lstnew(lexeme));
		}
		else
			free(lexeme_str);
		reset_token_data(data, cmd[i]);
	}
}

void	reset_token_data(t_cmd_data *data, char c)
{
	if (!data)
		return ;
	data->tok_start += data->tok_len;
	data->tok_id++;
	if (c == ' ')	// ou faudra peut-etre ajouter aussi si is_operator(c, set), en tt cas si je reset d'office tok_in_progress a 0, la cmd [<f c] (sans les brackets) foire et le token f disparait
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
