/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 11:34:09 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the cmd string is empty, if it is not then it is added to history.
void	ft_add_cmd_to_history(char *cmd)
{
	if (cmd && *cmd)
		add_history(cmd);
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
		printf("Last input: %s\n", cmd);
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
