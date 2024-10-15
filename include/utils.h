/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/10/15 12:52:33 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

void	ft_printarray(char **lexemes, char separator);
int		char_in_set(char *s, char c);
void	ft_print_list(t_list *list, char *title);
void	ft_print_lexemes(t_list *list, int option, char separator, char *title);
int		ft_arraylen(char **array);
char	*ft_strtrim_replace(char **str);
int		ft_check_input_cmd(char **cmdref);

#endif