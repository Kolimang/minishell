/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 10:46:39 by jrichir          ###   ########.fr       */
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
	int		res;

	(void)argc;
	(void)argv;
	res = ft_isalpha('a');
	printf("%d\n", res);
	printf("\033[0;38;5;214m=== MiNishell v0.1 ===\033[0m\n\n");
	prompt = "\033[0;32mminishell>\033[0m";
	while (1)
	{
		cmd = readline(prompt);
		printf("Last input: %s\n", cmd);
		ft_add_cmd_to_history(cmd);
		free(cmd);
	}
	free(cmd);
	return (0);
}
