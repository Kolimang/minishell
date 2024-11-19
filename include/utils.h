/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/19 15:03:02 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

// free.c
void	free_arr(char **array, int limit);
void	free_ls(t_list *ls_lxm);
void	free_commands(t_list *ls_cmds);
void	free_lists(t_list *ls_lxm, t_list *ls_cmds);

// errors.c
int		merror(char *cmd, char *arg, char *arg_q, int type);

// errors2.c
int		syntaxerror(char *arg_q, int type);
int		invalid_identifier(char *cmd, char *arg);
int		fail_current_dir(void);

// utils.c
int		is_directory(char *path);
int		char_in_set(char *s, char c);
int		array_len(char **array);
int		ft_check_input_cmd(char **cmdref);

// utils2.c
char	*ft_strtrim_replace(char **str);
char	*ft_strjoin_replace(char *s1, char *s2, char autoref_string);
int		set_exit_status(int exitcode);

// print.c
void	ft_printarray(char **lexemes, char separator);
void	ft_print_list(t_list *list, char *title);
void	ft_print_lexemes(t_list *list, int option, char separator, char *title);
void	ft_print_cmd(t_cmd *command);
void	ft_print_redir(t_cmd *command);

#endif