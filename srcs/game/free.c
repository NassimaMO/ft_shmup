/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:57:21 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 14:02:33 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void	free_game(t_game *game);

static void	free_bullets(t_bullet **bullets)
{
	t_bullet	*tmp;

	if (bullets)
	{
		while (*bullets)
		{
			tmp = (*bullets)->next;
			free(bullets);
			(*bullets) = tmp;
		}
	}
}

void	free_game(t_game *game)
{
	if (game->nb_enemies)
		free(game->enemies);
	if (game->bullets)
		free_bullets(&game->bullets);
}
