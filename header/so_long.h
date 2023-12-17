/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 18:33:36 by carperez          #+#    #+#             */
/*   Updated: 2023/12/17 15:59:57 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "../libft/header/libft.h"
# include "../get_next_line/header/get_next_line.h"
# include "../mlx/mlx.h"

# define PLAYER_STOP		"./images/PlayerStop00.xpm"
# define PLAYER_RUN01RIGHT	"./images/PlayerRun01.xpm"
# define PLAYER_RUN02RIGHT	"./images/PlayerRun02.xpm"
# define PLAYER_RUN01LEFT	"./images/PlayerRun03.xpm"
# define PLAYER_RUN02LEFT	"./images/PlayerRun04.xpm"
# define PLAYER_RUN01UP		"./images/PlayerRun05.xpm"
# define PLAYER_RUN02UP		"./images/PlayerRun06.xpm"
# define PLAYER_RUN01DOWN	"./images/PlayerRun07.xpm"
# define PLAYER_RUN02DOWN	"./images/PlayerRun08.xpm"
# define PLAYER_DEAD		"./images/PlayerKill09.xpm"
# define WALL_01			"./images/Wall01.xpm"
# define WALL_02			"./images/Wall02.xpm"
# define EXIT_START			"./images/ExitStart.xpm"
# define EXIT_END			"./images/ExitEnd.xpm"
# define REWARD_01			"./images/Collectable01.xpm"
# define REWARD_02			"./images/Collectable02.xpm"
# define REWARD_03			"./images/Collectable03.xpm"
# define ENEMY_RUN01RIGHT	"./images/EnemyRun01.xpm"
# define ENEMY_RUN02RIGHT	"./images/EnemyRun02.xpm"
# define ENEMY_RUN01LEFT	"./images/EnemyRun03.xpm"
# define ENEMY_RUN02LEFT	"./images/EnemyRun04.xpm"
# define ENEMY_RUN01UP		"./images/EnemyRun05.xpm"
# define ENEMY_RUN02UP		"./images/EnemyRun06.xpm"
# define ENEMY_RUN01DOWN	"./images/EnemyRun07.xpm"
# define ENEMY_RUN02DOWN	"./images/EnemyRun08.xpm"
# define ENEMY_SPEED		10
# define PLAYER_SPEED		10
# define MAX_LOOPS			15
# define IMG_SIZE			50
//********************************
//The s_player structure contains:
//*p_player: vector of pointers for player's animations
//f_status: vector of flags for player status
//	[0]--> player moving/player standing
//	[1]--> player's activated animation
//n_steps: number of player movements
//rc: player's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_player
{
	void	*p_player[10];
	int		f_status[2];
	int		n_steps;
	int		rc[2];
}	t_player;
//********************************
//The s_exit structure contains:
//*p_exit: vector of pointers for exit's animations
//f_status: flags for exit status
//f_end: flags for game status
//rc: exit's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_exit
{
	void	*p_exit[2];
	int		f_status;
	int		f_end;
	int		rc[2];
}	t_exit;
//********************************
//The s_reward structure contains:
//f_status: vector of flags for reward status
//	[0]--> reward's animation duration
//	[1]--> reward's activated animation
//	[2]--> Enable or disable animation visibility
//rc: reward's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_reward
{
	int		f_status[3];
	int		rc[2];
}	t_reward;
//********************************
//The s_wall structure contains:
//rc: reward's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_wall
{
	int	rc[2];
}	t_wall;
//********************************
//The s_enemy structure contains:
//f_status: vector of flags for enemy status
//	[0]--> enemy's animation duration
//	[1]--> enemy's activated animation
//f_shift: vector of flags for enemy status
//	[0]--> enemy's direction
//	[1]--> enemy's orientation
//rc: enemy's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_enemy
{
	int		f_status[2];
	int		f_shift[2];
	int		rc[2];
}	t_enemy;
//********************************
//The s_items structure contains:
//n_player: number of players
//n_enemy: number of enemies
//n_exit: number of exits
//n_reward: number of collectables
typedef struct s_items
{
	int		n_player;
	int		n_enemy;
	int		n_exit;
	int		n_reward;
}	t_items;
//********************************
//The s_map structure contains:
//**m_map: matrix to store the map file information
//**m_solution: matrix clon of m_map to detect viable paths
//f_solution: flag to confirm path to the item exists
//rc: map's coordinates
//	[0]--> row number
//	[1]--> column number
typedef struct s_map
{
	char		**m_map;
	char		**m_solution;
	int			f_solution;
	int			m_rc[2];
}	t_map;
//********************************
//The s_game structure contains:
//*p_game: function management pointer of the minilibx library
//*p_win: graphic window management pointer
//g_size[2]: dimensions of the graphic window
//	[0]--> width
//	[1]--> height
//f_error: flag of error codes
//f_pause: flag of Start, Pause and Resume the game
//*p_map: pointer to map structure
//d_items: structure of type item
//d_player: structure of type player
//d_exit: structure of type exit
//*p_reward: vector of pointers for reward's animations
//l_reward: Pointer of type list to store the rewards
//*p_wall: vector of pointers for wall's imagen
//*l_wall: Pointer of type list to store the walls
//*p_enemy: vector of pointers for enemy's animations
//l_enemy: Pointer of type list to store the enemies
typedef struct s_game
{
	void		*p_game;
	void		*p_win;
	int			g_size[2];
	int			f_error;
	int			f_pause;
	t_map		*p_map;
	t_items		d_items;
	t_player	d_player;
	t_exit		d_exit;
	void		*p_reward[3];
	t_list		*l_reward;
	void		*p_wall;
	t_list		*l_wall;
	void		*p_enemy[8];
	t_list		*l_enemy;

}	t_game;

void	ft_error_msg(int nError);
int		ft_file_checker(char *fMap, t_game *dGame);
void	ft_map_init(char *sFile, t_game *dGame);
char	*ft_map_strjoin(char *sResult, char const *sAdd);
int		ft_map_template(int dFile, t_game *dGame);
int		ft_map_sizer(t_game *dGame);
int		ft_items_finder(t_game *dGame);
int		ft_items_validator(t_game *dGame);
int		ft_boundary_checker(t_game *dGame);
void	ft_exit_path(t_game *dGame);
void	ft_map_cleaner(t_game *dGame);
void	ft_reward_fullpath(t_game *dGame);
int		ft_map_solution(t_game *dGame);
void	ft_player_finder(t_game *dGame);
void	ft_exit_finder(t_game *dGame);
void	ft_rewards_finder(t_game *dGame);
void	ft_walls_finder(t_game *dGame);
void	ft_enemies_finder(t_game *dGame);
void	ft_list_rewards_normalization(t_game *dGame);

void	ft_load_images(t_game *dGame);
void	ft_unload_images(t_game *dGame);
int		ft_show_game(t_game *dGame);
int		ft_game_exit(t_game *dGame);
void	ft_game_loop(t_game *dGame);
void	ft_game_pause(t_game *dGame);
int		ft_key_capturer(int keycode, t_game *dGame);

void	ft_player_collision_enemy(t_game *dGame);
void	ft_player_rectification(t_game *dGame);
void	ft_player_reward_collect(t_game *dGame);
void	ft_enemy_shift(t_list *dEnemy);
void	ft_enemy_update(t_game *dGame);
void	ft_player_update(t_game *dGame);

void	ft_enemy_draw(t_game *dGame);
void	ft_wall_draw(t_game *dGame);
void	ft_reward_draw(t_game *dGame);
void	ft_exit_draw(t_game *dGame);
void	ft_player_draw(t_game *dGame);
#endif
//END