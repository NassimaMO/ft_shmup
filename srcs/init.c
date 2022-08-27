/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 05:23:59 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 18:06:22 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

static void	resize_sig(int sig)
{
	static enum e_gamestate	prevstate = GAME_INIT;

	(void)sig;
	endwin();
	refresh();
	if (g_gamestate != GAME_SCREEN_SIZE)
		prevstate = g_gamestate;
	if (COLS < MINSX || LINES < MINSY)
	{
		erase();
		mvprintw(0, 0, SCREEN_SIZE_WARN, MINSX, MINSY, COLS, LINES);
		refresh();
		if (g_gamestate == GAME_LOOP)
			toggle_pause();
		g_gamestate = GAME_SCREEN_SIZE;
	}
	else if (g_gamestate == GAME_SCREEN_SIZE)
	{
		if (prevstate == GAME_LOOP)
			toggle_pause();
		g_gamestate = prevstate;
	}
}

int	init_ncurses(void)
{
	initscr();
	def_prog_mode();
	if (has_colors() == FALSE)
		exit(1);
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);
	bkgdset(COLOR_PAIR(1));
	signal(SIGINT, exit);
	keypad(stdscr, TRUE);
	nonl();
	cbreak();
	noecho();
	curs_set(0);
	scrollok(stdscr, TRUE);
	signal(SIGWINCH, resize_sig);
	g_gamestate = GAME_SCREEN_SIZE;
	resize_sig(0);
	return (0);
}

void	init_timer(int fps)
{
	struct itimerval	itv;
	struct sigaction	sa;

	itv.it_interval.tv_sec = 0;
	itv.it_interval.tv_usec = 1000000 / fps;
	itv.it_value.tv_sec = itv.it_interval.tv_sec;
	itv.it_value.tv_usec = itv.it_interval.tv_usec;
	setitimer(ITIMER_REAL, &itv, NULL);
	sa.sa_handler = &handle_tick;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGALRM, &sa, NULL);
	handle_tick(0);
}
