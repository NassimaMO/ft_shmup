/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 05:24:52 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 18:48:40 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

int				g_gamestate = GAME_INIT;
t_game			*g_game = NULL;
struct timeval	g_time_start;

void	end(void) __attribute__((destructor));

void	toggle_pause(void)
{
	static struct timeval	pt = {};
	struct timeval			tv;

	if (g_gamestate == GAME_LOOP)
	{
		gettimeofday(&pt, 0);
		g_gamestate = GAME_PAUSED;
	}
	else if (g_gamestate == GAME_PAUSED || g_gamestate == GAME_SCREEN_SIZE)
	{
		gettimeofday(&tv, 0);
		if (tv.tv_usec < pt.tv_usec)
			tv = (struct timeval){
				.tv_sec = (tv.tv_sec - 1),
				.tv_usec = (tv.tv_usec + 1000000)};
		g_time_start.tv_usec += tv.tv_usec - pt.tv_usec;
		if (g_time_start.tv_usec > 1000000)
			g_time_start = (struct timeval){
				.tv_sec = (g_time_start.tv_sec + 1),
				.tv_usec = (g_time_start.tv_usec - 1000000)};
		g_time_start.tv_sec += tv.tv_sec - pt.tv_sec;
		g_gamestate = GAME_LOOP;
	}
}

void	acquire_input(void)
{
	int	key;

	key = getch();
	if (key == 'p')
		toggle_pause();
	if (key == KEY_DOWN || key == 's')
		rotate_player(g_game, KEY_DOWN);
	if (key == KEY_UP || key == 'w')
		rotate_player(g_game, KEY_UP);
	if (key == KEY_LEFT || key == 'a')
		rotate_player(g_game, KEY_LEFT);
	if (key == KEY_RIGHT || key == 'd')
		rotate_player(g_game, KEY_RIGHT);
	if (key == ' ')
		spawn_bullet(g_game, -1);
	mvprintw(0, 0, "%d,", key);
}

void	handle_tick(int sig)
{
	(void)sig;
	mvprintw(2, 0, "state: %d", g_gamestate);
	if (g_gamestate == GAME_INIT)
	{
		gettimeofday(&g_time_start, 0);
		srand(g_time_start.tv_sec + g_time_start.tv_usec);
		g_game = init_game();
		g_gamestate = GAME_LOOP;
	}
	else if (g_gamestate == GAME_LOOP)
	{
		enemies_attack(g_game);
		move_bullets(g_game);
		colision_bullets(g_game);
		move_enemies(g_game);
		move_player(g_game);
		colision_enemies(g_game);
		colision_bullets(g_game);
		draw_scene(g_game);
	}
	else if (g_gamestate == GAME_PAUSED)
		draw_pause(g_game);
	else if (g_gamestate == GAME_OVER)
		draw_game_over(g_game);
	else if (g_gamestate == GAME_EXIT)
		exit(0);
}

int	main(void)
{
	if (init_ncurses())
		return (1);
	init_timer(3);
	while (1)
		acquire_input();
	return (0);
}

void	end(void)
{
	reset_prog_mode();
	erase();
	refresh();
	endwin();
	delwin(stdscr);
	delscreen(set_term(NULL));
	if (g_gamestate == GAME_INIT)
		dprintf(2, "Init error, exiting...\n");
	else if (g_gamestate != GAME_EXIT)
		dprintf(2, "^c Detected, exiting...\n");
}
