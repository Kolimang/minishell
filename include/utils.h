/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/11 16:42:38 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// print.c
void	ft_printarray(char **lexemes, char separator);
void	ft_print_list(t_list *list, char *title);
void	ft_print_lexemes(t_list *list, int option, char separator, char *title);

// free.c
void	array_str_free(char **array, int limit);
void	free_lexemes(t_list *ls_lexemes);
void	free_commands(t_list *ls_commands);
void	free_lists(t_list *ls_lexemes, t_list *ls_commands);

// errors.c
int		merror(char *cmd, char *arg, char *arg_q, int type);

// utils.c
int		is_directory(char *path);
int		char_in_set(char *s, char c);
int		ft_arraylen(char **array);
int		ft_check_input_cmd(char **cmdref);

// utils2.c
char	*ft_strtrim_replace(char **str);
int		set_exit_status(int exitcode);

#endif