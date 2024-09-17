/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 16:54:35 by jrichir          ###   ########.fr       */
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

char	*get_start_substr(char *str)
{
	
}

char	**ft_tokenize(char *cmd)
{
	int		len;
	char	*srch;
	char	*start;
	char	*end;
	char	**substrings;

	len = ft_strlen(cmd);
	srch = cmd;
	start = NULL;
	end = NULL;
	while (ft_strchr(srch, '\''))
	{
		start = ft_strchr(srch, '\'');
		if (start != cmd && *(start - 1) != ' ' && start < &(cmd[len]))
		{
			srch = start + 1;
		}
		else
		{
			srch = NULL;
		}
	}
	if (start)
	{
		if (*(start + 1) != '\0')
		{
			srch = start + 1;
			while (ft_strchr(srch, '\''))
			{
			end = ft_strchr(srch, '\'');
			if (end != &cmd[len] && *(end + 1) != ' ')
				srch = end + 1;
			else
				srch = NULL;
			}
		}
	}
	if (start && end)
	{
		// use ft_substr() instead
		substrings = malloc(4 * sizeof(char *));
		*substrings = malloc((start - cmd + 1) * sizeof(char));
		if (!*substrings)
			return (NULL);
		ft_strlcpy(*substrings, cmd, start - cmd + 1);
		ft_printf("%s\n", *substrings);
		*++substrings = malloc((end - start + 1) * sizeof(char));
		if (!*substrings)
			return (NULL);
		ft_strlcpy(*substrings, start + 1, end - start);
		ft_printf("%s\n", *substrings);
		*++substrings = malloc((&cmd[len] - end + 1) * sizeof(char));
		if (!*substrings)
			return (NULL);
		ft_strlcpy(*substrings, end + 1, &cmd[len] - end);
		ft_printf("%s\n", *substrings);
		*++substrings = NULL;
		ft_printarray(substrings);
	}
	else
	{
		ft_printf("%s\n", cmd);
	}
	return (NULL);
}

int	execute(void)
{
	char	*prompt;
	char	*cmd;

	printf("\033[0;38;5;214m=== MiNishell v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m";
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
