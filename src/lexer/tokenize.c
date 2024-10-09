/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/09 12:35:45 by jrichir          ###   ########.fr       */
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

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = 0;
	list_lexemes = NULL;
	while (i <= (int)ft_strlen(cmd))
	{
		lex_handle_operators(cmd, i, &data);
		lex_handle_spaces(cmd, i, &data);
		lex_handle_quotes(cmd, i, &data);
		lex_handle_regular(cmd, i, &data);
		if (lex_handle_end_of_cmd(cmd, i, &data))
			return (NULL);
		create_node(cmd, i, &data, &list_lexemes);
		i++;
	}
	//ft_print_lexemes(list_lexemes, 1, ' ', "\033[0;33m[command ]\033[0m"); //Used for debugging
	//ft_printf("hd_delimiter: %s\n", find_delim(list_lexemes)); //Used for debugging
	ft_print_list(lex_handle_heredoc(&data, find_delim(list_lexemes)), "[hd:]");
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
		templexeme_str = ft_substr(cmd, data->tok_start, (size_t)data->tok_len);
		lexeme_str = ft_strtrim(templexeme_str, " ");
		free(templexeme_str);
		if (lexeme_str[0] != '\0')
		{
			lexeme = malloc(sizeof(t_lexemes));
			lexeme->index = data->tok_id;
			lexeme->str = lexeme_str;
			lexeme->value = NULL;
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

void	reset_token_data(t_cmd_data *data, char current)
{
	if (!data)
		return ;
	data->tok_start += data->tok_len;
	data->tok_id++;
	//if (current == ' ')
	//	data->bool_tok_in_progress = 0;  --> problem with "lina"'bou'
	(void)current; // just added for debug
	data->bool_tok_in_progress = 0;
	data->bool_delimit_tok = 0;
}

// second IF-part can possibly be removed, must be tested
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
	//else if (data->bool_endstr == 1 )
	//	data->tok_len += 1;
}
