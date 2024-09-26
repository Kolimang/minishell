/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboumahd <lboumahd@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 16:10:04 by lboumahd          #+#    #+#             */
/*   Updated: 2024/09/26 16:17:18 by lboumahd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*expand $ and ~ 
gets a linked list from lexer () 
 ->receiving the arg to expand only 
 $ cases :	
	"$VAR" || $VAR : <user_name>
	'$VAR' : $VAR
	$?
	$VAR$USER$HOME 
~ cases: 
	cd ~/fd/fd1 : cd /USERS/user_name/fd/fd1
	---- The expansion happens in 2 caes : D_Quotes and No_Quotes
	---- The expansion in here_doc : both '' and ""
	
*/
//returns cleaned str without SQ 
void *handle_SQ(char **res, char *tmp, int *i)
{
	int start;

	start = *i;
	while((tmp)[(*i)++])
	{
		if((*tmp) == SQ)
			return(append_to_str(res, tmp, *i, start));
	}
	exit(EXIT_FAILURE); //no ' found
}

void	handle_DQ(char **res, char *tmp, int *i, t_env *new_env)
{
	//SQ is treated as literal characters
	int start = 0;
	while (tmp[(*i)])
	{
		start = i;
		//append no $ or ' after $
		while((tmp[*i] != '$' && tmp[*i]) ||(tmp[*i] == '$') && tmp[*i + 1] == SQ)
			i++;
		append_to_str(res, tmp, *i, start);
		//start = i;
		if(tmp[*i] == '$')
			expander(res, tmp, *i, new_env);
	}
}

char *handle_exp(char *tmp, t_lexems *lexeme, t_env *new_env)
{
	//set flag for SQ/NQ/DQ
	//process each case
	//colelct and append the str
	char *res;
	char *final_res;
	//calloc str;
	//calloc final_str????
	int i;
	i = 0;
	while(tmp[i++])
	{
		if(tmp[i] == SQ)
			handle_SQ(&res, &tmp, &i);
		else if(tmp[i] == DQ)
			handle_DQ(&res, tmp, &i, new_env); 
		else
			handle_NQ(&res, tmp, &i, new_env);
		final_res = ft_strjoin(final_res, res);
	}
	return(final_res);
}

void process_regular(t_lexems *lexeme, t_env *new_env)
{
    char	*tmp;
	char *clean_str;
	if (!lexeme)
		exit(EXIT_FAILURE);
	if (lexeme->str == NULL)
        return;
	tmp = ft_strdup(lexeme->str);
	clean_str = handle_exp(tmp, lexeme, new_env);
	free(tmp);
}

void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag)
{
	//traverse tte la liste, avec ou sans $
    while(lexeme)
	{
		if (flag == 1)  // Normal exp case
			process_regular(lexeme, new_env);
    	else
			process_HRDOC(lexeme);
		if(lexeme)
			lexeme = lexeme->next;
	//error ?? 
}
void	expander(char **res, char *tmp, int *i, t_env *new_env)
{
	int start;

	*i++;
	start = *i;
	if((tmp[(*i)] == ' ') ||(tmp[(*i)] == '\0'))
		return (append_to_str(res, tmp, *i - 1, start));			
	else if(ft_isdigit(tmp[*i]))//digit 0 - 9 -> skip num then append to str
		// return (append_to_str(res, tmp, *i + 1));
	echo
		//case of only 1 digit :
	else if (tmp[*i] == '?') //mise a jour du code d erreur 
		return (); // find exit error 
	else
		replace_var(&);//fetch var in env
		append_to_str();
		//var found -> expand then append to str 
}
//oblige de rajouter un espace
void	append_to_str()
//TESTS 
/*

bash-3.2$ echo $USER
lboumahd
bash-3.2$ echo '$USERl'
$USERl
bash-3.2$ echo $'$USERl'
$USERl
bash-3.2$ echo $'$USER'
$USER
bash-3.2$ echo $"$USER"
lboumahd
bash-3.2$ echo $'$USER'
$USER
bash-3.2$ echo $'$'$USER'' woowwww
$lboumahd
bash-3.2$ 
*/