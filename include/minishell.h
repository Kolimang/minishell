/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/16 12:02:34 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Include library headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// Include project headers
# include "env.h"
# include "tokens.h"
# include "utils.h"
# include "expander.h"
# include "parser.h"

int	g_ret_value;
# define SQ 39
# define DQ 34
//SQ DQ changed

# define VERSION "v0.1.35"

int	check_commands(char **cmds, int *i);
int	handle_commands(char **cmds, t_env *env, int *i);
int	execute(t_env *env);
int	main(int ac, char **av, char **o_env);
int	ft_check_input_cmd(char **cmdref);

#endif