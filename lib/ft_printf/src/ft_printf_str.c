/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:58:37 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:05:22 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_str(char *str, int c_count)
{
	ssize_t	result;

	if (!str)
	{
		result = ft_printf_putstr_fd("(null)", 1);
		if (result == -1)
			return (-1);
		c_count += 6;
	}
	else
	{
		result = ft_printf_putstr_fd(str, 1);
		if (result == -1)
			return (-1);
		c_count += (int)ft_printf_strlen(str);
	}
	if (result == -1)
		return (result);
	else
		return (c_count);
}
