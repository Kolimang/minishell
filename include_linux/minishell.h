/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 12:50:43 by jrichir          ###   ########.fr       */
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

// Declare global var
extern int	g_ret_val;

int	handle_commands(t_envs *envs, char **cmds, int *i);
int	minishell(t_envs *envs);
int	main(int ac, char **av, char **o_env);

// Commented out bcz conflict with different prototype found in PATH on Ubuntu/Mint
//int	rl_replace_line(char *, int);

#endif
