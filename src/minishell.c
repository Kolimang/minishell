/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/16 11:40:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	printf("=== MiNiSHELL v0.1 ===\n\n");
	prompt = NULL;
	prompt = readline("minishell>");
	while (prompt)
	{
		printf("Last input: %s\n", prompt);
		prompt = readline("minishell>");
	}
	return (0);
}
