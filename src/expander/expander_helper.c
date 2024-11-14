/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 19:40:34 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/14 17:01:19 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

void	expander(char **res, char *tmp, int *i, t_env *new_env)
{
	int	start;
	char *var_name;

	(*i)++;
	start = *i;
	if (tmp[start] == ' ' || tmp[start] == '\0' || tmp[start] == DQ)
		return (append_to_str(res, tmp, *i, start - 1));
	else if (ft_isdigit(tmp[*i]) || tmp[*i] == '?')
		return (handle_special_cases(res, tmp, i));
	else
	{
		while (ft_isalnum(tmp[*i]) || tmp[*i] == '_')
			(*i)++;
		var_name = ft_substr(tmp, start, *i - start);
		handle_variable(res, var_name, new_env);
		free(var_name);
	}
}

void	handle_special_cases(char **res, char *tmp, int *i)
{
	char	*exit_code_str;

	if (ft_isdigit(tmp[*i]))
	{
		int start = *i;
		while (tmp[*i] && tmp[*i] != DQ && tmp[*i] != ' ')
			(*i)++;
		append_to_str(res, tmp, *i, start + 1);
	}
	else if (tmp[*i] == '?')
	{
		exit_code_str = ft_itoa(g_ret_value);
		*res = ft_strjoin(*res, exit_code_str);
		free(exit_code_str);
		(*i)++;
	}
}

void	handle_variable(char **res, char *var_name, t_env *new_env)
{
	if (get_env_val(new_env, var_name))
		*res = ft_strjoin(*res, get_env_val(new_env, var_name));
	else
		*res = ft_strjoin(*res, "");
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
		free(*res);//ADDED - fixing leaks
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
