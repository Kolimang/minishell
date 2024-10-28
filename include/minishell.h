/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/28 15:52:13 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//ret val
int	g_ret_value;

// Include library headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// Include project headers
# include "env.h"
# include "tokens.h"
# include "utils.h"
# include "expander.h"
# include "parser.h"
# include "exec.h"
# include "builtin.h"

# define SQ 39
# define DQ 34

# define VERSION "v0.1.38"

int	check_commands(char **cmds, int *i);
int	handle_commands (t_env *env, int *i, char **g_env);
// int	execute(t_env *env, char **g_env);
//int	main(int ac, char **av, char **o_env);
int	ft_check_input_cmd(char **cmdref);
//testlina
t_list *mock_command_line(void);

#endif
