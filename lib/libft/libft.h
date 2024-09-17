/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:41:06 by jrichir           #+#    #+#             */
/*   Updated: 2024/09/17 10:41:13 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>

// ------------------------------ FT_PRINTF -----------------------------------

# include <stdarg.h>

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

// --------------------------------- GNL --------------------------------------

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 19
# endif

int		del(char **str);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_gnl_strjoin(char **s1, char **s2, int free_param);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_gnl_strdup(char **s);

// -------------------------------- LIBFT -------------------------------------

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_itoa(int n);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *pas2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strrchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);

#endif
