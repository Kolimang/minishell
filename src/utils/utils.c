/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:44:04 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/21 13:57:39 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	char_in_set(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_printarray(char **array, char separator)
{
	int	i;

	i = 0;
	while (array[i])
	{
		ft_printf("%s", array[i]);
		if (i < (ft_arraylen(array) - 1))
			ft_printf("%c", separator);
		i++;
	}
	if (separator != '\n')
		ft_printf("\n");
}

void	ft_print_list(t_list *list, char *title)
{
	if (!list)
		return ;
	if (title && title[0] != '\0')
		printf("%s\n", title);
	while (list)
	{
		printf("%s\n", list->content);
		list = list->next;
	}
}

void	ft_print_lexemes(t_list *list, int option, char separator, char *title)
{
	t_lexeme	*lex;

	if (!list)
		return ;
	if (title && title[0] != '\0')
	{
		if (separator == '\n')
			printf("%s\n", title);
		else
			printf("%s ", title);
	}
	while (list)
	{
		lex = list->content;
		if (option == 1)
			printf("%s", lex->str);
		else if (option == 2)
			printf("%s", lex->value);
		if (list->next)
			printf("%c", separator);
		list = list->next;
	}
	if (separator != '\n')
		printf("\n");
}

int	ft_arraylen(char **array)
{
	int	i;

	if (!array)
		return (-1);
	i = 0;
	while (array[i])
		i++;
	return (i);
}
