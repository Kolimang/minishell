/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/01 16:41:02 by jrichir          ###   ########.fr       */
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
	int	flag_in_sq;
	int	flag_in_dq;
	int	flag_endq_sep;
	int	flag_endstr;
	int	flag_delimit_token;
	int	token_in_progress;
	int	token_id;
}	t_cmd_data;

void	init_cmd_data(t_cmd_data *data)
{
	data->flag_in_sq = 0;
	data->flag_in_dq = 0;
	data->flag_endq_sep = 0;
	data->flag_endstr = 0;
	data->flag_delimit_token = 0;
	data->token_in_progress = 0;
	data->token_id = 0;
}

t_list	*ft_tokenize(char *cmd)
{
	int					i;
	int					len;
	unsigned int		tokenstart;
	t_cmd_data			data;
	char				*lexem;
	t_list				*list_lexems;
	char				*templexem;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	tokenstart = 0;
	len = 0;
	i = 0;
	list_lexems = NULL;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			if (data.token_in_progress == 1 && data.flag_in_sq == 0 && data.flag_in_dq == 0)
				data.flag_delimit_token = 1;
			else if (data.token_in_progress == 0 && data.flag_in_sq == 0 && data.flag_in_dq == 0)
				tokenstart += 1;
			else if (data.flag_in_sq == 1 || data.flag_in_dq == 1)
				data.token_in_progress = 1;
		}
		else if (cmd[i] == '\'')
		{
			if (data.flag_in_dq == 0 && data.flag_in_sq == 1)
			{
				data.flag_in_sq = 0;
				data.flag_delimit_token = 1;
				data.flag_endq_sep = 1;
			}
			else if (data.flag_in_dq == 0 && data.flag_in_sq == 0)
			{
				data.flag_in_sq = 1;
				if (data.token_in_progress == 1)
					data.flag_delimit_token = 1;
				else
				{
					data.token_in_progress = 1;
				}
			}
		}
		else if (cmd[i] == '\"')
		{
			if (data.flag_in_sq == 0 && data.flag_in_dq == 1)
			{
				data.flag_in_dq = 0;
				data.flag_delimit_token = 1;
				data.flag_endq_sep = 1;
			}
			else if (data.flag_in_sq == 0 && data.flag_in_dq == 0)
			{
				data.flag_in_dq = 1;
				if (data.token_in_progress == 1)
					data.flag_delimit_token = 1;
				else
					data.token_in_progress = 1;
			}
		}
		else
			data.token_in_progress = 1;
		if (cmd[i + 1] == '\0')
		{
			data.flag_endstr = 1;
			data.flag_delimit_token = 1;
			if (data.flag_in_sq == 1 || data.flag_in_dq == 1)
				printf("ERROR: unclosed quote.\n");
		}
		if (data.flag_delimit_token == 1)
		{
			if (&cmd[i] == &cmd[tokenstart])
				len = 1;
			else
				len = &cmd[i] - &cmd[tokenstart];
			if (data.flag_endq_sep == 1)
			{
				data.flag_endq_sep = 0;
				len += 1;
			}
			else if (data.flag_endstr == 1)
				len += 1;
			templexem = ft_substr(cmd, tokenstart, (size_t)(len));
			// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
			lexem = ft_strtrim(templexem, " ");
			// To do: protect outputs from ft_substr and ft_strtrim (mallocs)
			free(templexem);
			printf("[%d] %s\n", data.token_id, lexem);
			if (!list_lexems)
				list_lexems = ft_lstnew(lexem);
			else
				ft_lstadd_back(&list_lexems, ft_lstnew(lexem));
			tokenstart += len;
			data.token_id++;
			data.token_in_progress = 0;
			data.flag_delimit_token = 0;
		}
		i++;
	}
	return (list_lexems);
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
