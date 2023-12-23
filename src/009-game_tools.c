/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   009-game_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 10:28:18 by carperez          #+#    #+#             */
/*   Updated: 2023/12/23 11:11:28 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_game_end": function to display the end of the game
// in the Minilibx window.
static void	ft_game_end(t_game *dGame)
{
	char	*p_steps;

	p_steps = NULL;
	mlx_clear_window(dGame->p_game, dGame->p_win);
	ft_exit_draw(dGame);
	if (dGame->d_exit.f_end == 2)
		mlx_string_put(dGame->p_game, dGame->p_win, 15, (dGame->g_size[1] / 2)
			- 75, 0x00FF00, "You Win!!");
	else if (dGame->d_exit.f_end == 3)
	{
		mlx_string_put(dGame->p_game, dGame->p_win, 15, (dGame->g_size[1] / 2)
			- 75, 0xFF0000, "You Lost!!");
		ft_player_draw(dGame);
	}
	mlx_string_put(dGame->p_game, dGame->p_win, 10, (dGame->g_size[1] / 2) + 25,
		0xFFFF00, "Press ESC or close the window!!");
	p_steps = ft_itoa(dGame->d_player.n_steps);
	mlx_string_put(dGame->p_game, dGame->p_win, 10, dGame->g_size[1] - 25,
		0x00FF00, "Stride counter:");
	mlx_string_put(dGame->p_game, dGame->p_win, 130, dGame->g_size[1] - 25,
		0xFF0000, p_steps);
	free(p_steps);
	p_steps = NULL;
}

//"ft_game_draw": function to display all items during
// the game in the Minilibx window.
static void	ft_game_draw(t_game *dGame)
{
	ft_wall_draw(dGame);
	ft_exit_draw(dGame);
	ft_reward_draw(dGame);
	ft_enemy_draw(dGame);
	ft_player_draw(dGame);
}

//"ft_game_text": function to display text during
// the game in the Minilibx window.
static void	ft_game_text(t_game *dGame)
{
	char	*p_steps;

	p_steps = NULL;
	p_steps = ft_itoa(dGame->d_player.n_steps);
	mlx_string_put(dGame->p_game, dGame->p_win, 10, dGame->g_size[1] - 25,
		0x00FF00, "Stride counter:");
	mlx_string_put(dGame->p_game, dGame->p_win, 130, dGame->g_size[1] - 25,
		0xFF0000, p_steps);
	if (!(dGame->f_pause))
		mlx_string_put(dGame->p_game, dGame->p_win, 300, dGame->g_size[1] - 25,
			0xFFFF00, "\"Press Space to PAUSE the game\"");
	else if (dGame->f_pause == 1)
		mlx_string_put(dGame->p_game, dGame->p_win, 300, dGame->g_size[1] - 25,
			0xFFFF00, "\"Press Space to RESUME the game\"");
	else
		mlx_string_put(dGame->p_game, dGame->p_win, 300, dGame->g_size[1] - 25,
			0x00FFFF, "\"Press Space to START the game\"");
	free(p_steps);
	p_steps = NULL;
}

//"ft_show_game": function to display and update the Minilibx
// window in each execution loop.
int	ft_show_game(t_game *dGame)
{
	if ((dGame->d_exit.f_end == 1) || !(dGame->d_exit.f_end))
	{
		mlx_clear_window(dGame->p_game, dGame->p_win);
		if (!(dGame->f_pause))
		{
			ft_enemy_update(dGame);
			ft_player_update(dGame);
		}
		ft_game_draw(dGame);
		ft_game_text(dGame);
	}
	else if (dGame->d_exit.f_end == 2 || dGame->d_exit.f_end == 3)
		ft_game_end(dGame);
	return (0);
}

//"ft_game_pause": function to pause or resume the game.
void	ft_game_pause(t_game *dGame)
{
	if (!(dGame->f_pause))
		dGame->f_pause = 1;
	else
		dGame->f_pause = 0;
	dGame->d_player.rc[1] += PLAYER_SPEED;
}

//END