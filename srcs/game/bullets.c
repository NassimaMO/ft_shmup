#include "shmup.h"

void    spawn_bullet(t_game *game, int p)
{
    t_bullet *next;
    t_bullet *tmp;

    next = game->bullets;
    if (!next)
    {
        next = malloc(sizeof(t_bullet));
        if (p == -1)
        {
            next->dir_x = game->player.dir_x;
            next->dir_y = game->player.dir_y;
            next->pos_x = game->player.pos_x + next->dir_x;
            next->pos_y = game->player.pos_y + next->dir_y;
        }
        else
        {
            next->dir_x = game->enemies[p].dir_x;
            next->dir_y = game->enemies[p].dir_y;
            next->pos_x = game->enemies[p].pos_x + next->dir_x;
            next->pos_y = game->enemies[p].pos_y + next->dir_y;
        }
        next->next = NULL;
    }
    else
    {
        while (next)
        {
            tmp = next;
            next = next->next;
        }
        next = malloc(sizeof(t_bullet));
        if (p == -1)
        {
            next->dir_x = game->player.dir_x;
            next->dir_y = game->player.dir_y;
            next->pos_x = game->player.pos_x + next->dir_x;
            next->pos_y = game->player.pos_y + next->dir_y;
        }
        else
        {
            next->dir_x = game->enemies[p].dir_x;
            next->dir_y = game->enemies[p].dir_y;
            next->pos_x = game->enemies[p].pos_x + next->dir_x;
            next->pos_y = game->enemies[p].pos_y + next->dir_y;
        }
        tmp->next = next;
    }
}

void    enemies_attack(t_game *game)
{
    int i;

    i = 0;
    while (i < game->nb_enemies)
    {
        if (rand() % 2 == 1)
            spawn_bullet(game, i);
        i++;
    }
}