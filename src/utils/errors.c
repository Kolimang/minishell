/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/14 13:45:25 by jrichir          ###   ########.fr       */
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
	if (type == 11)
	{
		write(2, "Not a directory\n", 16);
		type = 1;
	}
	else
		write(2, "No such file or directory\n", 26);
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

static int	invalid_identifier(char *cmd, char *arg, int type)
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

int	merror(char *cmd, char *arg, char *arg_q, int type)
{
	if (type == 1)
		return (nofileordir(cmd, arg, type));
	else if (type == 11)
		return (nofileordir(cmd, arg, type));
	else if (type == 10)
		return (invalid_identifier(cmd, arg_q, type));
	else if (type == 258)
		return (syntaxerror(arg_q, type));
	else if (type == 127)
		return (cmdnotfound(cmd, type));
	else if (type == 1271)
		return (nofileordir(cmd, arg, 127));
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
