/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shmup.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 05:23:04 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 17:58:51 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHMUP_H
# define SHMUP_H

# define __USE_XOPEN_EXTENDED
# define _XOPEN_SOURCE_EXTENDED
# include <sys/ioctl.h>
# include <sys/time.h>
# include <time.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <ncurses.h>
# include "game.h"

# define MINSX 120
# define MINSY 30
# define SCREEN_SIZE_WARN "Screen too small min(%dx%d) cur(%dx%d)"

enum e_gamestate {
	GAME_INIT = 0,
	GAME_SCREEN_SIZE,
	GAME_LOOP,
	GAME_PAUSED,
	GAME_OVER,
	GAME_EXIT,
};

extern int				g_gamestate;
extern t_game			*g_game;
extern struct timeval	g_time_start;

void		init_timer(int fps);
int			init_ncurses(void);
void		handle_tick(int sig);
void		toggle_pause(void);


#endif
