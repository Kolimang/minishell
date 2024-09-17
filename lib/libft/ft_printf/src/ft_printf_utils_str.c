/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_str.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 16:18:02 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:03:52 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_putstr_fd(char *s, int fd)
{
	ssize_t	count;
	ssize_t	result;

	count = 0;
	result = 0;
	if (!s)
		return (count);
	while (s[count] != '\0')
	{
		result = ft_printf_putchar_fd(s[count], fd);
		if (result == -1)
		{
			return (result);
		}
		count++;
	}
	return (count);
}

ssize_t	ft_printf_putchar_fd(char c, int fd)
{
	ssize_t	result;

	result = write(fd, &c, 1);
	return (result);
}

ssize_t	ft_printf_strlen(const char *s)
{
	ssize_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	else
	{
		return (c);
	}
}

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		return (c + 32);
	}
	else
	{
		return (c);
	}
}
