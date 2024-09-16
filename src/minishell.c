/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:11:01 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/16 12:03:08 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	main(int argc, char **argv)
{
	char	*prompt;

	(void)argc;
	(void)argv;
	prompt = NULL;
	printf("Hello world!\n");
	prompt = readline("minishell>");
	printf("User input was: %s\n", prompt);
/*
	if(mini_loop () == -1)
		return failure/exit;
*/
	return (0);
}
