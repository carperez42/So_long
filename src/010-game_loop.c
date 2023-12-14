/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   010-game_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 08:53:49 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 09:13:41 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_game_loop": function to initialize Minilibx, create
// the display window, and program its execution loop.
void	ft_game_loop(t_game *dGame)
{
	dGame->p_game = mlx_init();
	dGame->p_win = mlx_new_window(dGame->p_game, dGame->g_size[0],
			dGame->g_size[1], "so_long CPP");
	ft_load_images(dGame);
	mlx_hook(dGame->p_win, 17, 0, ft_game_exit, dGame);
	mlx_hook(dGame->p_win, 02, 0, ft_key_capturer, dGame);
	mlx_loop_hook(dGame->p_game, ft_show_game, dGame);
	mlx_loop(dGame->p_game);
}
