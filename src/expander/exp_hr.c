/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_hr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:04:41 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/15 15:45:03 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void handle_hrdoc_exp(char **res, char *tmp, int *i, t_env *new_env)
{
    int start;
	char *var_name;
	char *var_value;

	start = *i;
    if (tmp[*i] == '$' && ft_isalnum(tmp[*i + 1]))
    {
        (*i)++;
        start = *i;
        while (ft_isalnum(tmp[*i]) || tmp[*i] == '_')
            (*i)++;
        var_name = ft_substr(tmp, start, *i - start);
        var_value = get_env_val(new_env, var_name);
        if (var_value)
            *res = ft_strjoin(*res, var_value);
        free(var_name);
    }
    else
    {
        (*i)++;
        append_to_str(res, tmp, *i, start);
    }
}

static char *expand_hrdoc(char *tmp, t_env *new_env)
{
    char *res;
    int i;

    res = ft_calloc(sizeof(char), 1);
    if (!res)
        return (NULL);
    i = 0;
    while (tmp[i])
    {
        if (tmp[i] == '$')
            handle_hrdoc_exp(&res, tmp, &i, new_env);
        else
        {
            append_to_str(&res, tmp, i + 1, i);
            i++;
        }
    }
    return (res);
}

void process_hrdoc(char *line, t_env *new_env)
{
    char *tmp;
    char *expanded_str;

    if (!line)
        return ;
    tmp = ft_strdup(line);
    if (!tmp)
        return ;
    expanded_str = expand_hrdoc(tmp, new_env);
    free(tmp);
    // if (expanded_str)
    // {
    //     free(line);
    //     lexeme->value = expanded_str;
    // }
}