/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 03:02:44 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Include library headers
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "../lib/libft/libft.h"

// Include project headers
# include "sighandle.h"
# include "env.h"
# include "tokens.h"
# include "parser.h"
# include "utils.h"
# include "expander.h"
# include "exec.h"
# include "builtin.h"

# define SQ 39
# define DQ 34

# define VERSION "v0.7"
# define DEBUG 0

// Global variable declaration (cannot be defined here, just declared)
extern int	g_ret_value;

int	check_commands(char **cmds, int *i);
int	handle_commands(t_envs *envs, char **cmds, int *i);
//int	handle_commands (t_env **env, char **cmds, int *i, char **g_env);
//int	execute(t_env **env, char **g_env);
int	execute(t_envs *envs);
int	main(int ac, char **av, char **o_env);
int	ft_check_input_cmd(char **cmdref);
//testlina
//t_list *mock_command_line(void);

// Commented out on Linux
int	rl_replace_line(char *, int);

#endif
