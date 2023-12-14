/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   008-game_load.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:50:53 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 10:18:42 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_load": function to load player animations into the program.
static void	ft_player_load(t_game *dGame)
{
	int	i_size[2];

	dGame->d_player.p_player[0] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_STOP, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[1] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN01RIGHT, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[2] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN02RIGHT, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[3] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN01LEFT, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[4] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN02LEFT, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[5] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN01UP, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[6] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN02UP, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[7] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN01DOWN, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[8] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_RUN02DOWN, &i_size[0], &i_size[1]);
	dGame->d_player.p_player[9] = mlx_xpm_file_to_image(dGame->p_game,
			PLAYER_DEAD, &i_size[0], &i_size[1]);
}

//"ft_enemy_load": function to load enemy animations into the program.
static void	ft_enemy_load(t_game *dGame)
{
	int	i_size[2];

	dGame->p_enemy[0] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN01RIGHT, &i_size[0], &i_size[1]);
	dGame->p_enemy[1] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN02RIGHT, &i_size[0], &i_size[1]);
	dGame->p_enemy[2] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN01LEFT, &i_size[0], &i_size[1]);
	dGame->p_enemy[3] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN02LEFT, &i_size[0], &i_size[1]);
	dGame->p_enemy[4] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN01UP, &i_size[0], &i_size[1]);
	dGame->p_enemy[5] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN02UP, &i_size[0], &i_size[1]);
	dGame->p_enemy[6] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN01DOWN, &i_size[0], &i_size[1]);
	dGame->p_enemy[7] = mlx_xpm_file_to_image(dGame->p_game,
			ENEMY_RUN02DOWN, &i_size[0], &i_size[1]);
}

//"ft_item_load": function to load animations for items such as the exit,
// rewards, and walls into the program.
static void	ft_item_load(t_game *dGame)
{
	int	i_size[2];
	int	ia;

	dGame->p_wall = NULL;
	ia = (rand() % 2);
	if (ia)
		dGame->p_wall = mlx_xpm_file_to_image(dGame->p_game,
				WALL_01, &i_size[0], &i_size[1]);
	else
		dGame->p_wall = mlx_xpm_file_to_image(dGame->p_game,
				WALL_02, &i_size[0], &i_size[1]);
	dGame->d_exit.p_exit[0] = mlx_xpm_file_to_image(dGame->p_game,
			EXIT_START, &i_size[0], &i_size[1]);
	dGame->d_exit.p_exit[1] = mlx_xpm_file_to_image(dGame->p_game,
			EXIT_END, &i_size[0], &i_size[1]);
	dGame->p_reward[0] = mlx_xpm_file_to_image(dGame->p_game,
			REWARD_01, &i_size[0], &i_size[1]);
	dGame->p_reward[1] = mlx_xpm_file_to_image(dGame->p_game,
			REWARD_02, &i_size[0], &i_size[1]);
	dGame->p_reward[2] = mlx_xpm_file_to_image(dGame->p_game,
			REWARD_03, &i_size[0], &i_size[1]);
}

//"ft_load_images": function to load all necessary images for visualizing
// the game.
void	ft_load_images(t_game *dGame)
{
	ft_player_load(dGame);
	ft_item_load(dGame);
	ft_enemy_load(dGame);
}

//"ft_unload_images": function to unload all the previously loaded images.
void	ft_unload_images(t_game *dGame)
{
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[0]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[1]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[2]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[3]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[4]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[5]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[6]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[7]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[8]);
	mlx_destroy_image(dGame->p_game, dGame->d_player.p_player[9]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[0]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[1]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[2]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[3]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[4]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[5]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[6]);
	mlx_destroy_image(dGame->p_game, dGame->p_enemy[7]);
	mlx_destroy_image(dGame->p_game, dGame->p_wall);
	mlx_destroy_image(dGame->p_game, dGame->d_exit.p_exit[0]);
	mlx_destroy_image(dGame->p_game, dGame->d_exit.p_exit[1]);
	mlx_destroy_image(dGame->p_game, dGame->p_reward[0]);
	mlx_destroy_image(dGame->p_game, dGame->p_reward[1]);
	mlx_destroy_image(dGame->p_game, dGame->p_reward[2]);
}
//END