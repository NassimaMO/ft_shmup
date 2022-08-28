/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:57:47 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 16:46:17 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void	move_player(t_game *game)
{
	if (game->player.dir_y < 0 && game->player.dir_x == 0)
		game->player.pos_y--;
	else if (game->player.dir_y > 0 && game->player.dir_x == 0)
		game->player.pos_y++;
	else if (game->player.dir_y == 0 && game->player.dir_x < 0)
		game->player.pos_x--;
	else if (game->player.dir_y == 0 && game->player.dir_x > 0)
		game->player.pos_x++;
}

void	move_bullets(t_game *game)
{
	t_bullet	*bullet;

	bullet = game->bullets;
	while (bullet)
	{
		if (bullet->dir_y < 0)
			bullet->pos_y--;
		else if (bullet->dir_y > 0)
			bullet->pos_y++;
		if (bullet->dir_x < 0)
			bullet->pos_x--;
		else if (bullet->dir_x > 0)
			bullet->pos_x++;
		bullet = bullet->next;
	}
}

void	move_enemies(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_enemies)
	{
		if (game->enemies[i].lives <= 0)
		{
			i++;
			continue ;
		}
		if (game->enemies[i].dir_y < 0 && game->enemies[i].dir_x == 0)
			game->enemies[i].pos_y--;
		else if (game->enemies[i].dir_y > 0 && game->enemies[i].dir_x == 0)
			game->enemies[i].pos_y++;
		else if (game->enemies[i].dir_y == 0 && game->enemies[i].dir_x < 0)
			game->enemies[i].pos_x--;
		else if (game->enemies[i].dir_y == 0 && game->enemies[i].dir_x > 0)
			game->enemies[i].pos_x++;
		i++;
	}
}

void	rotate_player(t_game *game, int dir)
{
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	if (dir == KEY_UP)
		game->player.dir_y = -1;
	else if (dir == KEY_DOWN)
		game->player.dir_y = 1;
	if (dir == KEY_LEFT)
		game->player.dir_x = -1;
	else if (dir == KEY_RIGHT)
		game->player.dir_x = 1;
}

/*void	gen_enemy_dir(t_enemy *enemy)
{
	int	x;
	int	tmp;

	x = rand() % 100;
	if (enemy->type == 0)
	{
		tmp = rand() % 10;
		if (tmp >= x)
		{
			if (tmp >= 5)
			{
				enemy->dir_x = 0;
				enemy->dir_y = 1;
			}
			else
			{
				enemy->dir_x = 0;
				enemy->dir_y = -1;
			}
		}
		else
		{
			enemy->dir_x = 1;
			enemy->dir_y = 0;
		}
	}
	else if (enemy->type == 1)
	{
		tmp = rand() % 50;
		if (tmp >= x)
		{
			enemy->dir_x = 0;
			enemy->dir_y = 1;
		}
		else
		{
			enemy->dir_x = 1;
			enemy->dir_y = 0;
		}
	}
	else if (enemy->type == 2)
	{
		tmp = rand() % 100;
		if (tmp >= x)
		{
			enemy->dir_x = 0;
			enemy->dir_y = 1;
		}
		else
		{
			enemy->dir_x = 1;
			enemy->dir_y = 0;
		}
	}
}*/