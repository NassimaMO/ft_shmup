/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:57:50 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 17:32:39 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

t_game	*init_game(void);

static int	init_enemies(t_game *game)
{
	int	i;

	game->nb_enemies = 30;
	game->enemies = calloc(sizeof(t_enemy), game->nb_enemies);
	if (!game->enemies)
		return (1);
	i = 0;
	while (i < game->nb_enemies)
	{
		game->enemies[i].type = rand() % 3;
		game->enemies[i].pos_x = rand() % MINSX;
		game->enemies[i].pos_y = rand() % (MINSY / 4);
		game->enemies[i].dir_x = 0;
		game->enemies[i].dir_y = 1;
		//gen_enemy_dir(&game->enemies[i]);
		game->enemies[i].lives = 5;
		i++;
	}
	return (0);
}

static int	init_player(t_game *game)
{
	game->player.pos_x = MINSX / 2;
	game->player.pos_y = MINSY / 10 * 8;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.lives = 10;
	return (0);
}

t_game	*init_game(void)
{
	t_game	*game;

	game = (t_game *)calloc(1, sizeof(*game));
	if (game)
	{
		if (init_enemies(game) || init_player(game))
		{
			free_game(game);
			game = NULL;
		}
	}
	return (game);
}
