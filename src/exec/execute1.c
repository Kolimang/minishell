/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:51:12 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/30 09:55:49 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// int	execute_nofork(t_command *cmd, t_io_fd *io, t_env *l_env, char **g_env)
// {
// 	//void or int ?? what about g_ret_val??
// 	int	ret_value;
// 	//check redirection
// 	if (set_fds(cmd, io)== -1)
// 	{	
// 		reset_io(io, cmd);
// 		return (-1);
// 	}
// 	//execute cmd 
// 	ret_value = exec_builtin(cmd, l_env, g_env);
// 	if (cmd->fd_hrdoc != -3)
// 		close(cmd->fd_hrdoc);
// 	return (ret_value);
// }
int	execute_nofork(t_command *cmd, t_io_fd *io, t_env **l_env, char **g_env)
{
	int	ret_value;

	// Set up redirections
	if (set_fds(cmd, io) == -1)
	{
		//reset_io(io, cmd);
		return (-1);
	}
	// Execute builtin
	ret_value = exec_builtin(cmd, l_env, g_env);
	if (cmd->fd_hrdoc != -3)
		close(cmd->fd_hrdoc);
	return (ret_value);
}

int	exec_builtin(t_command *cmd, t_env **l_env, char **g_env)
{
	int	res;
	//revoir les inputs pour chaque function
	//revoir si les builtin renvoie une valeur d erreur 
	if (cmd->builtin == 1)
		res = ft_echo(cmd->args);
	else if (cmd->builtin == 2)
		res = ft_cd(cmd->args, *l_env);
	else if (cmd->builtin == 3)
		res = ft_pwd(cmd->args, *l_env);
	else if (cmd->builtin == 4)
		res = ft_export(cmd->args, l_env);
	else if (cmd->builtin == 5)
		res = ft_unset(cmd->args, l_env);
	else if (cmd->builtin == 6)
		res = ft_env(cmd->args, *l_env);
	else if (cmd->builtin == 7)
	   res = ft_exit(cmd->args, *l_env);
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

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

// Helper function to locate command in PATH (find_command_path)
char *find_command_path(const char *cmd, char **g_env)
{
	char *path_env = getenv("PATH");  // Alternatively, parse `g_env` for PATH
	char *path_dup = strdup(path_env);
	char *dir = strtok(path_dup, ":");
	char *full_path = NULL;

	// Check each directory in PATH
	while (dir)
	{
		// Allocate memory for full path (directory + command)
		full_path = malloc(strlen(dir) + strlen(cmd) + 2);  // +1 for '/' and +1 for '\0'
		sprintf(full_path, "%s/%s", dir, cmd);

		// Check if the command exists in this directory
		if (access(full_path, X_OK) == 0)
		{
			free(path_dup);
			return full_path;  // Command found
		}

		free(full_path);  // Clean up and check next directory
		dir = strtok(NULL, ":");
	}
	free(path_dup);
	return NULL;  // Command not found in PATH
}

// Function to locate and execute the command
// int exec_cmd(t_command *cmd, t_env *l_env, char **g_env)
// {
//     char *command_path;

//     // Step 1: Search for the command in the environment paths
//     command_path = find_command_path(cmd->args[0], g_env);
// 	if (!command_path)
//     {
//         perror("Command not found");
//         return -1;
//     }

//     // Step 2: Execute the command using execve
//     if (execve(command_path, cmd->args, g_env) == -1)
//     {
//         perror("Execution failed");
//         free(command_path);  // Clean up if execve fails
//         exit(EXIT_FAILURE);
//     }
// 	 eprintf("here\n");
//     return 0;  // Should never reach this if execve succeeds
// }
int exec_cmd(t_command *cmd, t_env *l_env, char **g_env)
{
	char *command_path;
	
	dprintf(2, "Executing command: %s\n", cmd->args[0]);
	debug_print_fds("Before exec_cmd", cmd, NULL);

	// Search for command in PATH
	command_path = find_command_path(cmd->args[0], g_env);
	if (!command_path)
	{
		dprintf(2, "Command not found: %s\n", cmd->args[0]);
		return -1;
	}

	// Verify file descriptors before execve
	int stdin_status = fcntl(STDIN_FILENO, F_GETFD);
	int stdout_status = fcntl(STDOUT_FILENO, F_GETFD);
	
	dprintf(2, "Before execve - stdin_status: %d, stdout_status: %d\n", 
			stdin_status, stdout_status);
	
	if (execve(command_path, cmd->args, g_env) == -1)
	{
		perror("Execution failed");
		free(command_path);
		exit(EXIT_FAILURE);
	}
	// Should never reach here
	free(command_path);
	return 0;
}