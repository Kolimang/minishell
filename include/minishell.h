/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:16:57 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/08 10:14:25 by jrichir          ###   ########.fr       */
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
# include "tokens.h"
# include "utils.h"
# include "expander.h"
# include "env.h"

int	g_ret_value;
# define SQ 39
# define DQ 34
//SQ DQ changed

#endif