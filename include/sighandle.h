/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/11/15 09:34:45 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

// signals.c
int		change_term_attr(void);
int		*sig_status(void);
void	sig_handler_child(int signum);
void	sig_handler_main(int signum);
void	sig_handler_hrdoc(int signum);

// signals2.c
void	newline_hook(int sig);

#endif
