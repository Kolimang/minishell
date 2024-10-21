/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:17:47 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/21 13:03:41 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check EXIIIIIIT attention 
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

int	execute_nofork(t_command *cmd, t_env *l_env, char **g_env)
{
	int ret_value;
	//check redirection
	if (execute_redir(cmd, cmd->io)== -1)
	{	
		reset_io(cmd);
		return(-1);
	}
	//execute cmd 
	ret_value = exec_builtin(cmd, l_env, g_env);
	return(ret_value);
}
int exec_builtin(t_command *cmd, t_env *l_env, char **g_env)
{
	int res;
	//revoir les inputs pour chaque function
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
        res = -1;  // Error: unknown built-in command
    return res;
}