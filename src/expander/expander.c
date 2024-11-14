/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/11/14 17:02:25 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_sq(char **res, char *tmp, int *i, int start)
{
	(*i)++;
	while (tmp[*i])
	{
		if (tmp[*i] == SQ)
		{
			append_to_str(res, tmp, *i, start + 1);
			(*i)++;
			return ;
		}
		(*i)++;
	}
}

void	handle_dq(char **res, char *tmp, int *i, t_env *new_env)
{
	int	start;

	start = 0;
	(*i)++;
	while (tmp[*i])
	{
		start = *i;
		while (tmp[*i] != DQ && tmp[*i])
		{
			if (tmp[*i] == '$' && tmp[*i + 1] != '\'')
				break ;
			(*i)++;
		}
		if (tmp[*i] == DQ)
		{
			append_to_str(res, tmp, *i, start);
			(*i)++;
			return ;
		}
		if (tmp[*i] == '$')
		{
			append_to_str(res, tmp, *i, start);
			expander(res, tmp, i, new_env);
		}
	}
}

void	handle_nq(char **res, char *tmp, int *i, t_env *new_env)
{
	int	start;

	start = *i;
	if (tmp[*i] == '$' && (tmp[*i + 1] == DQ || tmp[*i + 1] == SQ))
	{
		if (tmp[*i + 1] == DQ)
			dup_word(res, tmp, i);
		else if (tmp[*i + 1] == SQ)
			handle_sq(res, tmp, i, start + 1);
		return ;
	}
	else if (tmp[*i] == '$')
	{
		expander(res, tmp, i, new_env);
		return ;
	}
	else
	{
		while (tmp[*i] && tmp[*i] != '$' && tmp[*i] != SQ && tmp[*i] != DQ)
			(*i)++;
		append_to_str(res, tmp, *i, start);
	}
}

char	*handle_exp(char *tmp, t_lexeme *lex, t_env *new_env)
{
	char	*res;
	char	*final_res;
	int		i;
	int		start;

	res = ft_calloc(sizeof(char), 1);
	final_res = ft_calloc(sizeof(char), 1);
	i = 0;
	while (tmp[i])
	{
		start = i;
		if (tmp[i] == SQ)
			handle_sq(&res, tmp, &i, start);
		else if (tmp[i] == DQ)
			handle_dq(&res, tmp, &i, new_env);
		else
			handle_nq(&res, tmp, &i, new_env);
	}
	final_res = ft_strjoin(final_res, res);
	free(res);
	return (final_res);
}

void	expand_lexeme(t_lexeme *lex, t_env *new_env)
{
	char	*tmp;
	char	*clean_str;

	tmp = 0;
	clean_str = 0;
	if (!lex || lex->str == NULL)
		exit(EXIT_FAILURE);
	tmp = ft_strdup(lex->str);
	if (!tmp)
		exit(EXIT_FAILURE);
	clean_str = handle_exp(tmp, lex, new_env);
	if (lex->value)
		free(lex->value);
	lex->value = ft_strdup(clean_str);
	free(tmp);
	free(clean_str);
}
