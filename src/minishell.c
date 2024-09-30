/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/30 17:16:44 by jrichir          ###   ########.fr       */
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
	int	flag_delimit_token;
	int token_in_progress;
	int token_id;
}	t_cmd_data;

void init_cmd_data(t_cmd_data *data)
{
	data->flag_in_sq = 0;
	data->flag_in_dq = 0;
	data->flag_delimit_token = 0;
	data->token_in_progress = 0;
	data->token_id = 0;
}

char	**ft_tokenize(char *cmd)
{
	int					i;
	int					len;
	unsigned int		tokenstart;
	t_cmd_data			data;

	if (ft_strlen(cmd) <= 0)
		return (NULL);
	init_cmd_data(&data);
	tokenstart = 0;
	len = 0;
	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == ' ')
		{
			if (data.token_in_progress == 1 && data.flag_in_sq == 0 && data.flag_in_dq == 0)
				data.flag_delimit_token = 1;
			else if (data.token_in_progress == 0 && data.flag_in_sq == 0 && data.flag_in_dq == 0) // MODIFIED
			{
				tokenstart += 1;
				len = -1;
			}
			else if (data.flag_in_sq == 1 || data.flag_in_dq == 1) // NEW
			{
				data.token_in_progress = 1; // NEW
			}
		}
		else if (cmd[i] == '\'')
		{
			if (data.flag_in_dq == 0 && data.flag_in_sq == 1)
			{
				data.flag_in_sq = 0;
				data.flag_delimit_token = 1;
				len += 1;
			}
			else if (data.flag_in_dq == 0 && data.flag_in_sq == 0)
			{
				data.flag_in_sq = 1;
				if (data.token_in_progress == 1)
				{
					data.flag_delimit_token = 1;
					len -= 1;
				}
				else
				{
					data.token_in_progress = 1; //new
				}
			}
		}
		else if (cmd[i] == '\"')
		{
			if (data.flag_in_sq == 0 && data.flag_in_dq == 1)
			{
				data.flag_in_dq = 0;
				data.flag_delimit_token = 1;
				len += 1;
			}
			else if (data.flag_in_sq == 0 && data.flag_in_dq == 0)
			{
				data.flag_in_dq = 1;
				if (data.token_in_progress == 1)
				{
					data.flag_delimit_token = 1;
					len -= 1;
				}
				else
				{
					data.token_in_progress = 1; //new
				}
			}
		}
		else // ni espace, ni SQ, ni DQ
		{
			data.token_in_progress = 1;
			if (len < 1)
				len = 1;
		}
		if (cmd[i + 1] == '\0')
		{
			len += 1;
			data.flag_delimit_token = 1;
			if (data.flag_in_sq == 1 || data.flag_in_dq == 1)
				printf("ERROR: unclosed quote.\n");
		}
		len++; // alpha
		if (data.flag_delimit_token == 1)
		{
			printf("%d (len: %d): %s\n", data.token_id, len, ft_substr(cmd, tokenstart, (size_t)len));
			//tokenstart += len; // alpha
			tokenstart += len - 1; // alpha
			//len = -1; // alpha
			len = 0;
			data.token_id++;			
			data.token_in_progress = 0;
			data.flag_delimit_token = 0;
		}
		// len++; // alpha
		i++;
		// printf("len: %d\n", len);
		// printf("inSQ: %d\n", data.flag_in_sq);
		// printf("cuttok: %d\n", data.flag_delimit_token);
		// printf("-- -- --\n");
	}
	return (NULL);
}

int	execute(void)
{
	char	*prompt;
	char	*cmd;

	printf("\033[0;38;5;214m=== MiNishell v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m ";
	while (1)
	{
		cmd = readline(prompt);
		ft_tokenize(cmd);
		ft_add_cmd_to_history(cmd);
		free(cmd);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	if (execute())
		return (execute());
	return (0);
}
