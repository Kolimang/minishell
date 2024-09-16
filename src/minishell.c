/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/16 11:52:07 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	printf("\033[0;38;5;214m=== MiNiSHELL v0.1 ===\033[0m\n\n");
	prompt = NULL;
	prompt = readline("\033[0;32mminishell>\033[0m");
	while (prompt)
	{
		printf("Last input: %s\n", prompt);
		prompt = readline("\033[0;32mminishell>\033[0m");
	}
	return (0);
}
