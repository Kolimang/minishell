/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:16:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/07 16:12:13 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_node(char *cmd, int i, t_cmd_data *data, t_list	**list_lexems)
{
	char	*templexem;
	char	*lexem;

	if (data->bool_delimit_tok == 1)
	{
		if (&cmd[i] == &cmd[data->tok_start]) // first if-part can possibly be removed, must be tested
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
		// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
		lexem = ft_strtrim(templexem, " ");
		// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
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
