/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:57:44 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 12:57:46 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"

void	kill_bullet(t_game *game, t_bullet *bullet)
{
	t_bullet    *next;
	t_bullet    *tmp;

	next = game->bullets;
	if (&next == &bullet)
	{
		tmp = next->next;
		free(next);
		game->bullets = tmp;
		return ;
	}
	while (next)
	{
		if (&next == &bullet)
		{
			tmp->next = next->next;
			free(next);
			return ;
		}
			tmp = next;
			next = next->next;
	}
}
