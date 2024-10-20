/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/10/18 16:15:23 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//WHAT TO DO WHEN !str, NULL of EXIT_FAILURE??

void	handle_sq(char **res, char *tmp, int *i, int start)
{
	(*i)++;
	while (tmp[*i])
	{
		(*i)++;
		if (tmp[*i] == SQ)
		{
			append_to_str(res, tmp, *i, start + 1);
			(*i)++;
			return ;
		}
	}
	// free(res);
	// exit(EXIT_FAILURE);
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
	// free(res);
	// exit(EXIT_FAILURE);
}

void	handle_nq(char **res, char *tmp, int *i, t_env *new_env,
			t_lexeme *lex)
{
	int	start;

	start = *i;
	(void)lex;
	if (tmp[*i] == '$' && (tmp[*i + 1] == DQ || tmp[*i + 1] == SQ))
	{
		if (tmp[*i + 1] == DQ)
			dup_word(res, tmp, i);
		else if (tmp[*i + 1] == SQ)
		{
			handle_sq(res, tmp, i, start);
		}
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
			(*i)++; // Move *i to the end of the current non-special segment
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
			handle_nq(&res, tmp, &i, new_env, lex); //si on rajoute lexer apr. parser
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

// // if heredoc token --> type = 1; else if regular token --> type = 0
// void	expand_lexeme(t_lexeme *lex, t_env *new_env)
// {
// 	if (lex->type == 0) // Normal exp case
// 		process_regular(lex, new_env);
// 	// else
// 	// 	process_hrdoc(line, new_env); // temp, to be replaced by process_hrdoc(lexeme);
// 	// 	//process_hrdoc(ls_hd_lexemes, new_env)
// 	// //error ?? 
// }

// char	*find_var(char *var, t_env *new_env) //getenv
// {
// 	while (new_env) // determiner le new_env structu
// 	{
// 		if (ft_strncmp(new_env->var_name, var, ft_strlen(var) + 1) == 0)
// 		{	
// 			var = new_env->var_val;
// 			return (var);
// 		}
// 		new_env = new_env->next;
// 	}
// 	return (NULL);
// }

// char	*replace_var(char *tmp, int *i, int start, t_env *new_env)
// {
// 	char	*var;

// 	while (ft_isalnum(tmp[*i]))
// 		i++;
// 	var = malloc(*i - start + 1);
// 	if (!var)
// 		return (NULL);
// 	ft_strlcpy(var, tmp, *i - start + 1);
// 	var = find_var(var, new_env);//if not found return NULL
// 	return (var);
// }
// oblige de rajouter un espace
// void append_to_str(char **res, char *tmp, int end, int start)
// {
//     char *new_part;
//     // char *new_res;

//     new_part = malloc((end - start + 1) * sizeof(char)); 
//     if (!new_part)
//         return ;
//     ft_strlcpy(new_part, tmp + start, end - start + 1);
//     if (*res)
//     {
//         *res = ft_strjoin(*res, new_part);
// 		// if (new_res)
// 		// 	free(new_res);
//     }
//     else
//         *res = new_part;
// 	if (new_part)
// 		free(new_part);
// }
