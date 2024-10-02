/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/02 16:24:17 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the cmd string is empty, if it is not then it is added to history.
void	ft_add_cmd_to_history(char *cmd)
{
	if (cmd && *cmd)
		add_history(cmd);
}

void	ft_printarray(char **lexems)
{
	int	i;

	i = 0;
	while (lexems[i])
	{
		printf("%s\n", lexems[i]);
		i++;
	}
}

/*
enum lex_types
{
	INPUT = 0,
	OUTPUT = 1,
	HD_DELIMITER = 2,
	OUT_APPEND = 3,
	SQ_STRING = 4,
	DQ_STRING = 5,
	OPERATOR = 6,
	EXEC = 7,
	ARGS = 8
};

typedef struct s_lexems
{
	int		index;
	char 	*value;
	int		type;
}	t_lexems;
*/

typedef struct s_cmd_data
{
	int				bool_in_sq;
	int				bool_in_dq;
	int				bool_endq_sep;
	int				bool_endstr;
	int				bool_delimit_tok;
	int				bool_tok_in_progress;
	int				tok_id;
	int				tok_len;
	unsigned int	tok_start;
}	t_cmd_data;

void	init_cmd_data(t_cmd_data *data)
{
	data->bool_in_sq = 0;
	data->bool_in_dq = 0;
	data->bool_endq_sep = 0;
	data->bool_endstr = 0;
	data->bool_delimit_tok = 0;
	data->bool_tok_in_progress = 0;
	data->tok_id = 0;
	data->tok_len = 0;
	data->tok_start = 0;
}

static int	char_in_set(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	is_operator(char c)
{
	char	*set;

	set = "<|>";
	return (char_in_set(set, c));
}

t_list	*ft_tokenize(char *cmd)
{
	int					i;
	t_cmd_data			data;
	char				*lexem;
	t_list				*list_lexems;
	char				*templexem;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	i = 0;
	list_lexems = NULL;
	while (cmd[i])
	{
		// handle_operators();
		// handle_spaces();
		// handle_quotes();
		// create_node();
		if (is_operator(cmd[i]))
		{
			if (data.bool_in_sq == 0 && data.bool_in_dq == 0)
			{
				if (i > 0 && !is_operator(cmd[i - 1]))
					data.bool_delimit_tok = 1;
				else if (i > 0 && is_operator(cmd[i - 1]) && cmd[i - 1] != cmd[i])
					data.bool_delimit_tok = 1;
				//if (cmd[i + 1] && is_operator(cmd[i + 1]))
				//	data.tok_len += 1;
			}
			else if (data.bool_in_sq == 1 || data.bool_in_dq == 1)
				data.bool_tok_in_progress = 1;
		}
		else if (i > 0 && is_operator(cmd[i - 1]))
			data.bool_delimit_tok = 1;
		else if (cmd[i] == ' ')
		{
			if (data.bool_tok_in_progress == 1 && data.bool_in_sq == 0 && data.bool_in_dq == 0)
					data.bool_delimit_tok = 1;
			else if (data.bool_tok_in_progress == 0 && data.bool_in_sq == 0 && data.bool_in_dq == 0)
				data.tok_start += 1;
			else if (data.bool_in_sq == 1 || data.bool_in_dq == 1)
				data.bool_tok_in_progress = 1;
		}
		else if (cmd[i] == '\'')
		{
			if (data.bool_in_dq == 0 && data.bool_in_sq == 1)
			{
				data.bool_in_sq = 0;
				data.bool_delimit_tok = 1;
				data.bool_endq_sep = 1;
			}
			else if (data.bool_in_dq == 0 && data.bool_in_sq == 0)
			{
				data.bool_in_sq = 1;
				if (data.bool_tok_in_progress == 1)
					data.bool_delimit_tok = 1;
				else
				{
					data.bool_tok_in_progress = 1;
				}
			}
		}
		else if (cmd[i] == '\"')
		{
			if (data.bool_in_sq == 0 && data.bool_in_dq == 1)
			{
				data.bool_in_dq = 0;
				data.bool_delimit_tok = 1;
				data.bool_endq_sep = 1;
			}
			else if (data.bool_in_sq == 0 && data.bool_in_dq == 0)
			{
				data.bool_in_dq = 1;
				if (data.bool_tok_in_progress == 1)
					data.bool_delimit_tok = 1;
				else
					data.bool_tok_in_progress = 1;
			}
		}
		else
			data.bool_tok_in_progress = 1;
		if (cmd[i + 1] == '\0')
		{
			data.bool_endstr = 1;
			data.bool_delimit_tok = 1;
			if (data.bool_in_sq == 1 || data.bool_in_dq == 1)
				printf("ERROR: unclosed quote.\n");
		}
		if (data.bool_delimit_tok == 1)
		{
			if (&cmd[i] == &cmd[data.tok_start])
				data.tok_len = 1;
			else
				data.tok_len = &cmd[i] - &cmd[data.tok_start];
			if (data.bool_endq_sep == 1)
			{
				data.bool_endq_sep = 0;
				data.tok_len += 1;
			}
			else if (data.bool_endstr == 1)
				data.tok_len += 1;
			templexem = ft_substr(cmd, data.tok_start, (size_t)data.tok_len);
			// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
			lexem = ft_strtrim(templexem, " ");
			// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
			free(templexem);
			if (lexem[0] != '\0')
			{
				if (!list_lexems)
					list_lexems = ft_lstnew(lexem);
				else
					ft_lstadd_back(&list_lexems, ft_lstnew(lexem));
			}
			else
				free(lexem);
			data.tok_start += data.tok_len;
			data.tok_id++;
			data.bool_tok_in_progress = 0;
			data.bool_delimit_tok = 0;
		}
		i++;
	}
	return (list_lexems);
}

void	ft_print_list(t_list *list, char *title)
{
	if (!list)
		return ;
	if (title)
		printf("%s\n", title);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

int	execute(void)
{
	char	*prompt;
	char	*cmd;
	t_list	*lexems;

	printf("\033[0;38;5;214m=== MiNiSHELL v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m ";
	while (1)
	{
		cmd = readline(prompt);
		if (!cmd)
			return (1);
		lexems = ft_tokenize(cmd);
		if (!lexems)
		{
			free(cmd);
			return (1);
		}
		ft_print_list(lexems, "--- List of lexems ---");
		ft_add_cmd_to_history(cmd);
		free(cmd);
	}
	return (0);
}

int	main(void)
{
	if (execute())
		return (1);
	return (0);
}
