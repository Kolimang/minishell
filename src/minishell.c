/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/16 14:46:22 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// Checks if the cmd string is empty, if it is not then it is added to history.
void	ft_add_cmd_to_history(char *cmd)
{
	if (cmd && *cmd)
		add_history(cmd);
}

int	main(int argc, char **argv)
{
	char	*prompt;
	char	*cmd;

	(void)argc;
	(void)argv;
	printf("\033[0;38;5;214m=== MiNishell v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m";
	cmd = readline(prompt);
	ft_add_cmd_to_history(cmd);
	while (1)
	{
		printf("Last input: %s\n", cmd);
		free(cmd);
		cmd = readline(prompt);
		ft_add_cmd_to_history(cmd);
	}
	free(cmd);
	return (0);
}
