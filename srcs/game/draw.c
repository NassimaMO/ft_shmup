/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 13:23:34 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 19:11:15 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

# define OFFX ((COLS - MINSX) / 2)
# define OFFY ((LINES - MINSY) / 2)

static void	draw_enemy(t_enemy *enemy)
{
	chtype		c;

	c = "0123456789ABCDEF"[enemy->type & 0xf];
	attron(COLOR_PAIR(2));
	mvaddch(OFFY + enemy->pos_y, OFFX + enemy->pos_x, c);
	attroff(COLOR_PAIR(2));
}

static void	draw_player(t_game *game)
{
	chtype		c;

	c = ACS_BULLET;
	if (game->player.dir_x > 0)
		c = ACS_RARROW;
	else if (game->player.dir_x < 0)
		c = ACS_LARROW;
	else if (game->player.dir_y > 0)
		c = ACS_DARROW;
	else if (game->player.dir_y < 0)
		c = ACS_UARROW;
	attron(COLOR_PAIR(3));
	mvaddch(OFFY + game->player.pos_y, OFFX + game->player.pos_x, c);
	attroff(COLOR_PAIR(3));
}

static void	draw_bullet(t_game *game, t_bullet *bullet)
{
	chtype		c;

	c = ACS_BULLET;
	if (bullet->dir_x > 0)
		c = ACS_RARROW;
	else if (bullet->dir_x < 0)
		c = ACS_LARROW;
	else if (bullet->dir_y > 0)
		c = ACS_DARROW;
	else if (bullet->dir_y < 0)
		c = ACS_UARROW;
	attron(COLOR_PAIR(5));
	mvaddch(OFFY + bullet->pos_y, OFFX + bullet->pos_x, c);
	attroff(COLOR_PAIR(5));
	(void)game;
}

static void	draw_info(t_game *game)
{
	struct timeval	tv;

	erase();
	mvaddch(OFFY - 01, OFFX - 1, ACS_ULCORNER);
	mvhline(OFFY - 01, OFFX, ACS_HLINE, MINSX);
	mvaddch(OFFY - 01, OFFX + MINSX, ACS_URCORNER);
	mvaddch(OFFY + MINSY, OFFX - 1, ACS_LLCORNER);
	mvhline(OFFY + MINSY, OFFX, ACS_HLINE, MINSX);
	mvaddch(OFFY + MINSY, OFFX + MINSX, ACS_LRCORNER);
	mvvline(OFFY, OFFX - 1, ACS_VLINE, MINSY);
	mvvline(OFFY, OFFX + MINSX, ACS_VLINE, MINSY);
	gettimeofday(&tv, 0);
	if (g_gamestate == GAME_PAUSED)
		mvprintw(OFFY + MINSY - 1, OFFX + 1, "Score: %.6d Time: *paused*",
			game->score);
	else if (g_gamestate == GAME_OVER || g_gamestate == GAME_LOOP)
		mvprintw(OFFY + MINSY - 1, OFFX + 1, "Score: %.6d Time: %.1lf",
			game->score, tv.tv_sec - g_time_start.tv_sec
			+ (tv.tv_usec - g_time_start.tv_usec) * 1e-6);
}

void	draw_scene(t_game *game)
{
	int				i;
	t_bullet		*bullet;

	draw_info(game);
	i = 0;
	while (i < game->nb_enemies)
		draw_enemy(&game->enemies[i++]);
	draw_player(game);
	bullet = game->bullets;
	while (bullet)
	{
		printf("1");
		draw_bullet(game, bullet);
		bullet = bullet->next;
	}
	refresh();
}

void	draw_pause(t_game *game)
{
	draw_scene(game);
	mvprintw(OFFY + MINSY / 2 - 3, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 0, OFFX + MINSX / 2 - 9, "      PAUSED      ");
	mvprintw(OFFY + MINSY / 2 + 1, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 3, OFFX + MINSX / 2 - 9, "                  ");
	mvaddch(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 8, ACS_ULCORNER);
	mvhline(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 7, ACS_HLINE, 14);
	mvaddch(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 + 7, ACS_URCORNER);
	mvaddch(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 8, ACS_LLCORNER);
	mvhline(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 7, ACS_HLINE, 14);
	mvaddch(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 + 7, ACS_LRCORNER);
	mvvline(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 - 8, ACS_VLINE, 3);
	mvvline(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 + 7, ACS_VLINE, 3);
	refresh();
}

void	draw_game_over(t_game *game)
{
	draw_info(game);
	mvprintw(OFFY + MINSY / 2 - 3, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 - 9, "     GAMEOVER     ");
	mvprintw(OFFY + MINSY / 2 + 0, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 1, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 9, "                  ");
	mvprintw(OFFY + MINSY / 2 + 3, OFFX + MINSX / 2 - 9, "                  ");
	mvaddch(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 8, ACS_ULCORNER);
	mvhline(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 - 7, ACS_HLINE, 14);
	mvaddch(OFFY + MINSY / 2 - 2, OFFX + MINSX / 2 + 7, ACS_URCORNER);
	mvaddch(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 8, ACS_LLCORNER);
	mvhline(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 - 7, ACS_HLINE, 14);
	mvaddch(OFFY + MINSY / 2 + 2, OFFX + MINSX / 2 + 7, ACS_LRCORNER);
	mvvline(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 - 8, ACS_VLINE, 3);
	mvvline(OFFY + MINSY / 2 - 1, OFFX + MINSX / 2 + 7, ACS_VLINE, 3);
}
