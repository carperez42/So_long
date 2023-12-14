/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   018-player_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:25:33 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 17:15:13 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_rl_exit": function to detect collision between the player and
// the exit from the right and left sides.
static void	ft_player_rl_exit(t_exit *dexit, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[0] > dexit->rc[0] && p_aux->rc[0] < (dexit->rc[0]
				+ IMG_SIZE)) || ((p_aux->rc[0] + IMG_SIZE) < (dexit->rc[0]
				+ IMG_SIZE) && (p_aux->rc[0] + IMG_SIZE) > dexit->rc[0])
		|| ((p_aux->rc[0] + IMG_SIZE) == (dexit->rc[0] + IMG_SIZE)
			&& p_aux->rc[0] == dexit->rc[0]))
	{
		if ((p_aux->rc[1] + IMG_SIZE) > (dexit->rc[1] + (IMG_SIZE
					- (IMG_SIZE / 3))) && (p_aux->rc[1] + IMG_SIZE)
			< (dexit->rc[1] + IMG_SIZE))
			dGame->d_exit.f_end = 2;
		else if (p_aux->rc[1] < (dexit->rc[1] + (IMG_SIZE / 3))
			&& p_aux->rc[1] > dexit->rc[1])
			dGame->d_exit.f_end = 2;
	}
}

//"ft_player_du_exit": function to detect collision between the player and
// the exit from the right and left sides.
static void	ft_player_du_exit(t_exit *dexit, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[1] > dexit->rc[1] && p_aux->rc[1] < (dexit->rc[1]
				+ IMG_SIZE)) || ((p_aux->rc[1] + IMG_SIZE) < (dexit->rc[1]
				+ IMG_SIZE) && (p_aux->rc[1] + IMG_SIZE) > dexit->rc[1])
		|| ((p_aux->rc[1] + IMG_SIZE) == (dexit->rc[1] + IMG_SIZE)
			&& p_aux->rc[1] == dexit->rc[1]))
	{
		if ((p_aux->rc[0] + IMG_SIZE) > (dexit->rc[0] + (IMG_SIZE
					- (IMG_SIZE / 3))) && (p_aux->rc[0] + IMG_SIZE)
			< (dexit->rc[0] + IMG_SIZE))
			dGame->d_exit.f_end = 2;
		else if (p_aux->rc[0] < (dexit->rc[0] + (IMG_SIZE / 3))
			&& p_aux->rc[0] > dexit->rc[0])
			dGame->d_exit.f_end = 2;
	}
}

//"ft_player_update": function to detect and update player interactions with
// the rest of the map.
void	ft_player_update(t_game *dGame)
{
	if (dGame->d_exit.f_end != 3)
	{
		ft_player_reward_collect(dGame);
		ft_player_collision_enemy(dGame);
		ft_player_rectification(dGame);
		if (!(dGame->d_items.n_reward))
		{
			if (dGame->d_exit.f_end != 3)
			{
				dGame->d_exit.f_end = 1;
				ft_player_rl_exit(&(dGame->d_exit), dGame);
				ft_player_du_exit(&(dGame->d_exit), dGame);
				if (dGame->d_exit.f_end == 2)
					ft_printf("\033[1;32m\n~ *********************************"
						"******* ~\n\n~\t\t Well done!\t\t   ~\n~ \t      You "
						"hit the road!\t           ~\n\n~ ********************"
						"******************** ~\n\n\033[1;33mClose the game wi"
						"th ESC or close the window\n\n");
			}
		}
	}
}

//"ft_player_draw": function to display the player in the Minilibx window.
void	ft_player_draw(t_game *dGame)
{
	if (dGame->d_player.f_status[0] && (dGame->d_exit.f_end != 3))
	{
		mlx_put_image_to_window(dGame->p_game, dGame->p_win,
			dGame->d_player.p_player[dGame->d_player.f_status[1]],
			dGame->d_player.rc[1], dGame->d_player.rc[0]);
		dGame->d_player.f_status[0] = 0;
	}
	else if (!(dGame->d_player.f_status[0]) && (dGame->d_exit.f_end != 3))
		mlx_put_image_to_window(dGame->p_game, dGame->p_win,
			dGame->d_player.p_player[0], dGame->d_player.rc[1],
			dGame->d_player.rc[0]);
	else if (dGame->d_exit.f_end == 3)
		mlx_put_image_to_window(dGame->p_game, dGame->p_win,
			dGame->d_player.p_player[9], dGame->d_player.rc[1],
			dGame->d_player.rc[0]);
}

//END