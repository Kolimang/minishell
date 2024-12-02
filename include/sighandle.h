/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sighandle.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrichir <jrichir@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 14:08:51 by jrichir           #+#    #+#             */
/*   Updated: 2024/12/02 09:38:48 by jrichir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGHANDLE_H
# define SIGHANDLE_H

// signals.c
int		change_term_attr(void);
void	set_signals_parent(void);
void	set_signals_child(void);
void	set_signals_hrdoc(void);
void	sig_handler_main(int signum);
//void	sig_handler_child(int signum);

// signals2.c
void	unset_signals(void);
void	sig_handler_hrdoc(int signum);

#endif
