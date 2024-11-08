/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/08 15:26:59 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	nofileordir(char *cmd, char *arg, int type)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 3);
	}
	perror(NULL);
	return (set_exit_status(type));
}

static int	cmdnotfound(char *cmd, int type)
{
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	write(2, "command not found\n", 18);
	return (set_exit_status(type));
}

static int	syntaxerror(char *arg_q, int type)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token `", 36);
	write(2, arg_q, 1);
	write(2, "'\n", 2);
	return (set_exit_status(type));
}

int	merror(char *cmd, char *arg, char *arg_q, int type)
{
	if (type == 1)
		return(nofileordir(cmd, arg, type));
	else if (type == 258)
		return(syntaxerror(arg_q, type));
	else if (type == 127)
		return(cmdnotfound(cmd, type));
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, "`", 1);
		write(2, arg, ft_strlen(arg));
		write(2, "': ", 3);
	}
	write(2, "\n", 1);
	return (set_exit_status(type));
}
