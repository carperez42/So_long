/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   014-player_motion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:10:20 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 16:42:36 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_up_shift": function to switch between player animations when
// moving upwards.
static void	ft_up_shift(t_game *dGame)
{
	if (dGame->d_player.f_status[1] == 5)
		dGame->d_player.f_status[1] = 6;
	else
		dGame->d_player.f_status[1] = 5;
	dGame->d_player.rc[0] -= PLAYER_SPEED;
}

//"ft_down_shift": function to switch between player animations when
// moving downwards.
static void	ft_down_shift(t_game *dGame)
{
	if (dGame->d_player.f_status[1] == 7)
		dGame->d_player.f_status[1] = 8;
	else
		dGame->d_player.f_status[1] = 7;
	dGame->d_player.rc[0] += PLAYER_SPEED;
}

//"ft_left_shift": function to switch between player animations when
// moving to the left.
static void	ft_left_shift(t_game *dGame)
{
	if (dGame->d_player.f_status[1] == 3)
		dGame->d_player.f_status[1] = 4;
	else
		dGame->d_player.f_status[1] = 3;
	dGame->d_player.rc[1] -= PLAYER_SPEED;
}

//"ft_left_shift": function to switch between player animations when
// moving to the right.
static void	ft_right_shift(t_game *dGame)
{
	if (dGame->d_player.f_status[1] == 1)
		dGame->d_player.f_status[1] = 2;
	else
		dGame->d_player.f_status[1] = 1;
	dGame->d_player.rc[1] += PLAYER_SPEED;
}

//"ft_key_capturer": function to perform the corresponding action based
// on the keyboard input.
int	ft_key_capturer(int keycode, t_game *dGame)
{
	dGame->d_player.f_status[0] = 1;
	if (keycode == 53)
		ft_game_exit(dGame);
	else if (keycode == 49)
		ft_game_pause(dGame);
	else if (keycode == 13 || keycode == 126 || keycode == 1 || keycode == 125
		|| keycode == 0 || keycode == 123 || keycode == 2 || keycode == 124)
	{
		if (dGame->d_exit.f_end != 2 && dGame->d_exit.f_end != 3
			&& !(dGame->f_pause))
		{
			dGame->d_player.n_steps ++;
			ft_printf("\033[1;34m\nsteps: %d	key: %d",
				dGame->d_player.n_steps, keycode);
			if (keycode == 13 || keycode == 126)
				ft_up_shift(dGame);
			else if (keycode == 1 || keycode == 125)
				ft_down_shift(dGame);
			else if (keycode == 0 || keycode == 123)
				ft_left_shift(dGame);
			else if (keycode == 2 || keycode == 124)
				ft_right_shift(dGame);
		}
	}
	return (0);
}

//END