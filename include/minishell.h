/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/15 18:44:35 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Include library headers
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
#include <stdbool.h>
#include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// Include project headers
# include "env.h"
# include "tokens.h"
# include "utils.h"
# include "expander.h"
#include "exec.h"

int	g_ret_value;
# define SQ 39
# define DQ 34
//SQ DQ changed
# define VERSION "v0.1.2"
#endif