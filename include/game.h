
#ifndef GAME_H
# define GAME_H

typedef struct s_enemy		t_enemy;
typedef struct s_player		t_player;
typedef struct s_bullet		t_bullet;
typedef struct s_game		t_game;

struct s_enemy
{
	int		type;
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	int		lives;
};

struct s_player
{
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	int		lives;
};

struct s_bullet
{
	int			pos_x;
	int			pos_y;
	int			dir_x;
	int			dir_y;
	t_bullet	*next;
};

struct s_game
{
	int			nb_enemies;
	t_enemy		*enemies;
	t_player	player;
	t_bullet	*bullets;
	int			score;
};

t_game	*init_game(void);
void	free_game(t_game *game);
void	draw_scene(t_game *game);
void	draw_pause(t_game *game);
void	draw_game_over(t_game *game);

void	rotate_player(t_game *game, int dir);

void	kill_bullet(t_game *game, t_bullet *bullet);

void	gen_enemy_dir(t_enemy *enemy);
void colision(t_game *game);
void    spawn_bullet(t_game *game, int p);
void    enemies_attack(t_game *game);
int    colision_enemies(t_game *game);
int colision_bullets(t_game *game);
void	move_player(t_game *game);
void	move_bullets(t_game *game);
void	move_enemies(t_game *game);

#endif
