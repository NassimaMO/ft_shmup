/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colision.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbailleu <tbailleu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 12:57:30 by tbailleu          #+#    #+#             */
/*   Updated: 2022/08/27 12:57:43 by tbailleu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shmup.h"


int player_colision(t_game *game)
{
    int i;

    i = 0;
    while (i < game->nb_enemies)
    {
        if (game->enemies[i].pos_x == game->player.pos_x && game->enemies[i].pos_y == game->player.pos_y)
            return (i);
        i++;
    }
    return (0);
}

int bullet_colision(t_game *game, t_bullet *bullet)
{
    int i;
    t_bullet *next;

    i = 0;
    if (game->player.pos_x == bullet->pos_x && game->player.pos_y == bullet->pos_y)
        return (1);
    next = game->bullets;
    while (next)
    {
        if (&next != &bullet && next->pos_x == bullet->pos_x && next->pos_y == bullet->pos_y)
            return (2);
        next = next->next;
    }
    while (i < game->nb_enemies)
    {
        if (game->enemies->lives && game->enemies[i].pos_x == bullet->pos_x
            && game->enemies[i].pos_y == bullet->pos_y)
            return (3 + i);
        i++;
    }
    
    return (0);
}

int enemy_colision(t_game *game, int enemy)
{
    if (game->player.pos_x == game->enemies[enemy].pos_x && game->player.pos_y == game->enemies[enemy].pos_y)
        return (1);
    return (0);
}

void colision_bullets(t_game *game)
{
    t_bullet *next;
    int k;

    next = game->bullets;
    while (next)
    {
        k = bullet_colision(game, next);
        if (k == 1)
        {
            game->player.lives--;
            kill_bullet(game, next);
            next = game->bullets;
        }
        else if (k == 2)
        {
            next->dir_x = 0;
            next->dir_y = 0;
            next = next->next;
        }
        else if (k >= 3)
        {
            game->enemies[k - 3].lives--;
            kill_bullet(game, next);
            next = game->bullets;
        }
        else
            next = next->next;
    }
    next = game->bullets;
    while (next)
    {
        if (next->dir_x == 0 && next->dir_y == 0)
        {
            kill_bullet(game, next);
            next = game->bullets;
        }
        else
            next = next->next;
    }
}

void    colision_enemies(t_game *game)
{
    int i;
    int k;

    i = 0;
    while (i < game->nb_enemies)
    {
        k = enemy_colision(game, i);
        if (k == 1)
            game->player.lives = 0;
        i++;
    }
}