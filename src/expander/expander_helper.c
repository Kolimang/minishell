/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:34 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/07 17:06:35 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_word(char **res, char *str, int *i)
{
	int	start;

	if (!str || !i)
		exit(EXIT_FAILURE);
	start = *i;
	while (str[*i])
	{
		if (!ft_isalnum(str[*i]) && *i != start && str[*i] != '?')
		{
			append_to_str(res, str, *i, start + 1);
			return ;
		}
		(*i)++;
	}
	append_to_str(res, str, *i, start);
}

// char	*var = 0;
void	expander(char **res, char *tmp, int *i, t_env *new_env)
{
	int		start;
	char	*var;
	char	*exit_code_str;

	(void)new_env;
	(*i)++;
	var = 0;
	start = *i;
	if ((tmp[start] == ' ') || (tmp[start] == '\0') || (tmp[start] == DQ))
		return (append_to_str(res, tmp, *i, start - 1));
	else if (ft_isdigit(tmp[*i])) //digit 0 - 9 -> skip num then append to str
	{
		while (tmp[*i] && tmp[*i] != DQ && tmp[*i] != ' ')
			(*i)++;
		return (append_to_str(res, tmp, *i, start + 1));
	}
	else if (tmp[*i] == '?') //mise a jour du code d erreur
	{
		exit_code_str = ft_itoa(g_ret_value);
		*res = ft_strjoin(*res, exit_code_str);
		free(exit_code_str);// Move past the '?'
		(*i)++;
		return ;//move past the ?
	}// find exit error
	else
	{ ///BUUUG  = SEGmentation fault
		while (ft_isalnum(tmp[*i]))
			(*i)++;
		append_to_str(&var, tmp, *i, start);
		if (get_env_var(new_env, var))
			*res = ft_strjoin(*res, get_env_var(new_env, var)); //GET REAL VALUE
		else
			*res = ft_strjoin("", *res);
		return ;
	}
}

void	append_to_str(char **res, char *tmp, int end, int start)
{
	char	*new_part;
	char	*new_res;

	new_part = malloc((end - start + 1) * sizeof(char));
	if (!new_part)
		return ;
	ft_strlcpy(new_part, tmp + start, end - start + 1);
	if (*res)
	{
		new_res = ft_strjoin(*res, new_part);
		*res = new_res;
	}
	else
	{
		*res = new_part;
		new_part = NULL;
	}
	if (new_part)
		free(new_part);
}
