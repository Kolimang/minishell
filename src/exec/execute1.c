/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:51:12 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/27 18:56:56 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_nofork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
{
	//void or int ?? what about g_ret_val??
	int	ret_value;
	//check redirection
	if (set_fds(cmd, io)== -1)
	{	
		reset_io(io, cmd);
		return (-1);
	}
	//execute cmd 
	ret_value= exec_builtin(cmd, l_env, g_env);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	return (ret_value);
}

int	exec_builtin(t_command *cmd, t_env *l_env, char **g_env)
{
	int	res;
	//revoir les inputs pour chaque function
	//revoir si les builtin renvoie une valeur d erreur 
    if (cmd->builtin == 1)
        res = ft_echo(cmd->args);
    else if (cmd->builtin == 2)
        res = ft_cd(cmd->args, l_env, g_env);
    else if (cmd->builtin == 3)
        res = ft_pwd(cmd->args, l_env, g_env);
    else if (cmd->builtin == 4)
        res = ft_export(cmd->args, l_env, g_env);
    else if (cmd->builtin == 5)
        res = ft_unset(cmd->args, l_env, g_env);
    else if (cmd->builtin == 6)
        res = ft_env(cmd->args, l_env, g_env);
    else if (cmd->builtin == 7)
        res = ft_exit(cmd->args, l_env, g_env);
    else
        res = -1; // Error: unknown built-in command
    return (res);
}

int	is_builtin(char *cmd)
{
	//check EXIIIIIIT attention 
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 3) == 0)
		return (2);
	else if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (3);
	else if (ft_strncmp(cmd, "export", 7) == 0)
		return (4);
	else if (ft_strncmp(cmd, "unset", 6) == 0)
		return (5);
	else if (ft_strncmp(cmd, "env", 4) == 0)
		return (6);
	else if (ft_strncmp(cmd, "exit", 5) == 0)
		return (7);
	return (0);
}
void	exec_cmd(t_command *cmd, t_env *local, char	**global)
{
	char	*full_path;
	char	**full_cmd;

	full_cmd = ft_split(cmd->name, ' ');
	if (cmd->args[0] == '/' || cmd->args[0] == '.')
		full_path = check_path(full_cmd, cmd);
	else
	{	
		full_path = get_full_path(full_cmd, local);
		if (!full_path)
		{
			ft_putstr_fd("Command not found \n", 2);
			ret_value = 127;
			exit(127);
		}
	}
	if (execve(full_path, full_cmd, global) == -1)
	{
		free_tab(full_cmd);
		free(full_path);
		perror("pipex");
		exit(EXIT_FAILURE);
	}
}
