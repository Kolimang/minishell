/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/08 10:18:34 by jrichir          ###   ########.fr       */
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
	t_list		*list_lexems;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = 0;
	list_lexems = NULL;
	while (cmd[i])
	{
		lex_handle_operators(cmd, i, &data);
		lex_handle_spaces(cmd, i, &data);
		lex_handle_quotes(cmd, i, &data);
		create_node(cmd, i, &data, &list_lexems);
		i++;
	}
	ft_print("---- Heredoc input ----\n");
	ft_print_list(handle_heredoc(&data, find_delim(list_lexems)), NULL);
	return (list_lexems);
}

// first if-part inside the main "IF" can possibly be removed, must be tested
void	create_node(char *cmd, int i, t_cmd_data *data, t_list	**list_lexems)
{
	char	*templexem;
	char	*lexem;

	if (data->bool_delimit_tok == 1)
	{
		if (&cmd[i] == &cmd[data->tok_start])
			data->tok_len = 1;
		else
			data->tok_len = &cmd[i] - &cmd[data->tok_start];
		if (data->bool_endq_sep == 1)
		{
			data->bool_endq_sep = 0;
			data->tok_len += 1;
		}
		else if (data->bool_endstr == 1)
			data->tok_len += 1;
		templexem = ft_substr(cmd, data->tok_start, (size_t)data->tok_len);
		lexem = ft_strtrim(templexem, " ");
		free(templexem);
		if (lexem[0] != '\0')
		{
			if (!*list_lexems)
				*list_lexems = ft_lstnew(lexem);
			else
				ft_lstadd_back(list_lexems, ft_lstnew(lexem));
		}
		else
			free(lexem);
		data->tok_start += data->tok_len;
		data->tok_id++;
		data->bool_tok_in_progress = 0;
		data->bool_delimit_tok = 0;
	}
}
