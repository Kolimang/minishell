/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 17:36:03 by jrichir           #+#    #+#             */
/*   Updated: 2023/11/20 12:10:45 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	ft_printf_u(unsigned int u, int c_count)
{
	ssize_t	result;

	c_count += ft_unsnbrlen_base((unsigned int)u, 10);
	result = ft_putunsnbr_base((unsigned int)u, "0123456789");
	if (result == -1)
		return (result);
	else
		return (c_count);
}
