/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:58:02 by jrichir           #+#    #+#             */
/*   Updated: 2024/03/20 14:01:40 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# endif

# include <unistd.h>
# include <stdlib.h>
// # include <fcntl.h>   // for the main(): open function, O_RDWR argument

int		del(char **str);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_gnl_strjoin(char **s1, char **s2, int free_param);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_gnl_strdup(char **s);

#endif
