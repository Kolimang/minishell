char	*get_real_value(char *str, t_env *new_env)
{
	//search if VAR de $VAR exists
	//search if 1st char is digit
		//if its only digit ->empty
		//otherwise return line after 
	//otherwise return empty string
}
void	expand(t_lexems *lexeme, t_env *new_env)
{
	char *str;
	int i;
	//attention echo "$"USER"" is 3 independant tokens
	i =0;
	if(str[i] = SQ || str[i] == DQ)
	{
		str = get_clear_str(lexeme->str); // malloc str
		lexeme->value = str;
	}
	else if (str[i] == '?' && !str[i++])
		lexeme->value = get_exit_status();
	else 
		lexeme->value = get_real_value(str,new_env);
	if(str)
		free(str);
}
// revoyer un flag si HR ou non 
void expand_lexer(t_lexems *lexeme, t_env *new_env, int flag)
{
	
	//the $ is already detected 
	t_lexems *tmp;
	tmp = lexeme;
		//do nthg
	if((lexeme->str) == '$' && !(lexeme->str))
		return;
	if(flag == 1) // normal
	{	
		if (lexeme->str[0] == "'") 
			printf("value == str");
		else
			// substr $ 
			printf("expand(lexeme, new_env)");
	}
	else
		
		printf("expand_HR(lexeme)");
	return;
}