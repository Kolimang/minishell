/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:41:15 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:03:01 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
ssize_t	ft_printf_int(int nb, int c_count);
ssize_t	ft_printf_char(char c, int c_count);
ssize_t	ft_printf_str(char *str, int c_count);
ssize_t	ft_printf_u(unsigned int u, int c_count);
ssize_t	ft_printf_ptr(unsigned long ptr, int c_count);
ssize_t	ft_printf_hex(unsigned int hex, char letter_case, int c_count);
ssize_t	ft_printf_putchar_fd(char c, int fd);
ssize_t	ft_printf_strlen(const char *s);
ssize_t	ft_printf_putstr_fd(char *s, int fd);
int		ft_toupper(int c);
int		ft_tolower(int c);
int		ft_valid_base(char *base);
ssize_t	ft_putnbr_base(long long int nbr, char *base);
ssize_t	ft_putunsnbr_base(unsigned long int ulnbr, char *base);
int		ft_nbrlen_base(long long int nb, int radix);
int		ft_unsnbrlen_base(unsigned long int nb, int radix);

#endif
