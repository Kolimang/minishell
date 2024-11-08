/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:19:56 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/25 10:30:58 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_strings(char const *s, char c)
{
	unsigned int	i;
	unsigned int	str_count;

	str_count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
				i++;
			str_count++;
		}
	}
	return (str_count);
}

static int	ft_word_len(char const *s, char c, unsigned int word_id)
{
	unsigned int	i;
	unsigned int	char_count;
	unsigned int	word;

	char_count = 0;
	word = 0;
	i = 0;
	while (s[i])
	{
		while ((char)s[i] == c)
			i++;
		if ((char)s[i] != '\0' && (char)s[i] != c)
		{
			word++;
			char_count = 0;
			while ((char)s[i] != '\0' && (char)s[i] != c)
			{
				i++;
				char_count++;
			}
		}
		if (word == word_id)
			return (char_count);
	}
	return (0);
}

static char	*ft_get_word_ptr(char const *s, char c, unsigned int word_id)
{
	unsigned int	i;
	unsigned int	char_count;
	unsigned int	word;

	char_count = 0;
	i = 0;
	word = 0;
	while (s[i])
	{
		while ((char)s[i] == c)
			i++;
		if ((char)s[i] != '\0' && (char)s[i] != c)
		{
			word++;
			if (word == word_id)
				return ((char *)&s[i]);
			while ((char)s[i] != '\0' && (char)s[i] != c)
			{
				i++;
				char_count++;
			}
		}
	}
	return (0);
}

static char	*ft_fill_word(char const *s, char c, unsigned int word_id)
{
	unsigned int	i;
	unsigned int	word_len;
	char			*word_ptr;
	char			*malloc_word;

	word_len = ft_word_len(s, c, word_id);
	word_ptr = ft_get_word_ptr(s, c, word_id);
	malloc_word = malloc((word_len + 1) * sizeof(char));
	if (!malloc_word)
		return (NULL);
	i = 0;
	while (word_ptr[i] != '\0' && word_ptr[i] != c)
	{
		malloc_word[i] = word_ptr[i];
		i++;
	}
	malloc_word[i] = '\0';
	return (malloc_word);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	nb_words;
	int				i;
	char			**strings;

	if (!s)
		return (NULL);
	nb_words = ft_count_strings((char *)s, c);
	strings = malloc((nb_words + 1) * sizeof(char *));
	if (!strings)
		return (NULL);
	i = 0;
	while (nb_words--)
	{
		strings[i] = ft_fill_word((char *)s, c, i + 1);
		if (strings[i] == NULL)
		{
			while (i >= 0)
				free(strings[i--]);
			free(strings);
			return (NULL);
		}
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
