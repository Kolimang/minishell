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

static int	write_msg(int type)
{
	if (type == 1 || type == 381)
		write(2, "No such file or directory\n", 26);
	else if (type == 11)
		write(2, "Not a directory\n", 16);
	else if (type == 127)
		write(2, "command not found\n", 18);
	else if (type == 12)
		write(2, "no environment set\n", 19);
	else if (type == 13)
		write(2, "too many arguments\n", 19);
	else if (type == 14)
		write(2, "HOME not set\n", 13);
	else if (type == 15)
		write(2, "Permission denied\n", 18);
	else if (type == 16)
		write(2, "error retrieving current directory\n", 35);
	else if (type == 17)
		write(2, "cannot change directory\n", 24);
	else if (type == 18)
		write(2, "OLDPWD not set\n", 15);
	else if (type == 19)
		write(2, "no option supported\n", 20);
	else if (type == 20)
		write(2, "error retrieving new directory\n", 31);
	return (0);
}

static int	write_msg2(int type)
{
	if (type == 381)
		write(2, "No such file or directory\n", 26);
	else if (type == 127)
		write(2, "command not found\n", 18);
	else if (type == 21)
		write(2, "not enough arguments\n", 21);
	else if (type == 22)
		write(2, "numeric argument required\n", 26);
	else if (type == 774)
		write(2, "syntax error: unclosed quote\n", 29);
	return (0);
}

static int	generic(char *cmd, char *arg, int type)
{
	int	ret;

	if (type > 100 && type <= 258)
		ret = type;
	else if (type > 258)
		ret = type / 3;
	else
		ret = 1;
	write(2, "minishell: ", 11);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 2);
	}
	if (type <= 20)
		write_msg(type);
	else
		write_msg2(type);
	return (set_exit_status(ret));
}

int	merror(char *cmd, char *arg, char *arg_q, int type)
{
	if (type == 10)
		return (invalid_identifier(cmd, arg_q, type));
	else if (type == 258)
		return (syntaxerror(arg_q, type));
	else
		return (generic(cmd, arg, type));
}
