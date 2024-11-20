/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/20 12:26:28 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntaxerror(char *arg_q, int type)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token `", 36);
	write(2, arg_q, ft_strlen(arg_q));
	write(2, "'\n", 2);
	return (set_exit_status(type));
}

// error 16
int	fail_current_dir(void)
{
	write(2, "cd: error retrieving current directory: ", 40);
	write(2, "getcwd: cannot access parent directories: ", 42);
	write(2, "No such file or directory\n", 26);
	return (set_exit_status(0));
}

int	invalid_identifier(char *cmd, char *arg)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, "'", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "' : ", 4);
	}
	write(2, "not a valid identifier\n", 23);
	return (set_exit_status(1));
}
