
// static char	*expand(char *str, t_env **local_env)
// {
// 	char	*var;
// 	char	*to_join;

// 	if (!str)
// 		exit(EXIT_FAILURE);
// 	var = ft_getenv(str, local_env);
// 	if (var)
// 		to_join = ft_strdup(var);
// 	else
// 		to_join = ft_strdup("");
// 	return (to_join);
// }
// static char	*handle_dollar(char *str, int *i, t_env **local_env)
// {
// 	int		save_i;
// 	char	*tmp;
// 	char	*to_join;

// 	if (!str || !i)
// 		exit(EXIT_FAILURE);
// 	if (str[++(*i)] == ' ' || str[*i] == '\0')
// 		to_join = ft_strldup(&str[*i - 1], 1);
// 	else if (ft_isdigit(str[*i]) || str[*i] == '?')
// 	{
// 		tmp = ft_strldup(&str[(*i)++], 1);
// 		to_join = expand(tmp, local_env);
// 		free(tmp);
// 	}
// 	else
// 	{
// 		save_i = *i;
// 		while (ft_isalnum(str[*i]))
// 			(*i)++;
// 		tmp = ft_strldup(&str[save_i], *i - save_i);
// 		to_join = expand(tmp, local_env);
// 		free(tmp);
// 	}
// 	return (to_join);
// }
// char	*no_quotes_handling(char *to_join, char **cleaned,
// 		t_lexer **lexer, t_prevhead *ph)
// {
// 	char	**tab;
// 	int		j;
// 	t_lexer	*tmp;

// 	if (*to_join == '\0')
// 		return (set_check(to_join, ph));
// 	tab = ft_split(to_join, ' ');
// 	free(to_join);
// 	j = -1;
// 	while (tab[++j])
// 	{
// 		if (j == 0)
// 			to_join = tab[j];
// 		else
// 		{
// 			free((*lexer)->str);
// 			(*lexer)->str = ft_strjoin_ff(*cleaned, to_join);
// 			*cleaned = ft_strdup("");
// 			lexer_insert(lexer);
// 			to_join = tab[j];
// 		}
// 	}
// 	free(tab);
// 	return (to_join);
// }
// char	*expaner(char *str, int quote_type, t_env **local_env)
// {
// 	char	*expanded;
// 	char	*to_join;
// 	int		save_i;
// 	int		i;

// 	if (!str)
// 		exit(EXIT_FAILURE);
// 	reassign_global(local_env);
// 	i = 0;
// 	expanded = ft_calloc_exit(sizeof(char), 1);
// 	while (str[i])
// 	{
// 		save_i = i;
// 		while ((str[i] && str[i] != '$') || (quote_type == D_QUOTE
// 				&& str[i] == '$' && str[i + 1] == S_QUOTE))
// 			i++;
// 		to_join = ft_strldup(&str[save_i], i - save_i);
// 		expanded = ft_strjoin_ff(expanded, to_join);
// 		if (str[i] == '$')
// 		{
// 			to_join = handle_dollar(str, &i, local_env);
// 			expanded = ft_strjoin_ff(expanded, to_join);
// 		}
// 	}
// 	return (expanded);
// }
// char	*dup_word(char *str, int *i)
// {
// 	int		tmp;

// 	if (!str || !i)
// 		exit(EXIT_FAILURE);
// 	tmp = *i;
// 	while (str[++(*i)])
// 	{
// 		if (!ft_isalnum(str[*i]) && *i != tmp && str[*i] != '?')
// 		{
// 			*i = *i - 1;
// 			return (ft_strldup(&str[tmp], *i - tmp + 1));
// 		}
// 		else if ((ft_isdigit(str[*i]) || str[*i] != '?') && *i == tmp)
// 		{
// 			*i = *i - 1;
// 			return (ft_strldup(&str[tmp], *i - tmp + 1));
// 		}
// 	}
// 	*i = *i - 1;
// 	return (ft_strdup(&str[tmp]));
// }
// static char	*to_expand(char *str, int *i, int quote_type, t_env **local_env)
// {
// 	char	*to_join;
// 	char	*tmp;

// 	if (str[*i] == '$' && (str[*i + 1] == 34 || str[*i + 1] == 39))
// 		return (ft_strdup(""));
// 	if (quote_type == -1)
// 		tmp = dup_word(str, i);
// 	else
// 		tmp = strdup_in_quotes(str, i, quote_type);
// 	to_join = expaner(tmp, quote_type, local_env);
// 	free(tmp);
// 	return (to_join);
// }
// char	*while_str(char *str, t_lexer **lexer,
// 		t_env **local_env, t_prevhead *ph)
// {
// 	char	*to_join;
// 	int		i;
// 	char	*cleaned;

// 	i = -1;
// 	cleaned = ft_calloc_exit(sizeof(char), 1);
// 	while (str[++i])
// 	{
// 		if (str[i] == D_QUOTE)
// 			to_join = to_expand(str, &i, D_QUOTE, local_env);
// 		else if (str[i] == S_QUOTE)
// 			to_join = strdup_in_quotes(str, &i, S_QUOTE);
// 		else
// 		{
// 			ph->check = 0;
// 			to_join = to_expand(str, &i, -1, local_env);
// 			to_join = no_quotes_handling(to_join, &cleaned, lexer, ph);
// 		}
// 		cleaned = ft_strjoin_ff(cleaned, to_join);
// 	}
// 	return (cleaned);
// }