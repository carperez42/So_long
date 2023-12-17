/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   000-main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:36:17 by carperez          #+#    #+#             */
/*   Updated: 2023/12/17 15:52:58 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_map_liberator": memory liberation function for arrays of pointers
// (matrix).
static void	ft_map_liberator(char **pMap, int nDim)
{
	int	ia;

	ia = 0;
	while (ia < nDim)
		free(pMap[ia++]);
	free(pMap);
	pMap = NULL;
}

//"ft_game_init": function to initialize the main parameters of the game.
static void	ft_game_init(t_game *dGame)
{
	dGame->p_map = malloc(sizeof(t_map));
	if (dGame->p_map)
	{
		dGame->f_error = 0;
		dGame->f_pause = 2;
		dGame->p_game = NULL;
		dGame->p_win = NULL;
		dGame->p_map->m_map = NULL;
		dGame->p_map->m_solution = NULL;
		dGame->p_map->f_solution = 0;
		dGame->p_map->m_rc[0] = 0;
		dGame->p_map->m_rc[1] = 0;
		dGame->l_reward = NULL;
		dGame->l_wall = NULL;
		dGame->l_enemy = NULL;
		dGame->d_items.n_player = 0;
		dGame->d_items.n_enemy = 0;
		dGame->d_items.n_exit = 0;
		dGame->d_items.n_reward = 0;
	}
	else
		dGame->f_error = 1;
}

//"ft_map_cheker": function to verify that the map intended for play meets all
// the requirements to be playable.
static int	ft_map_cheker(char	*fMap, t_game *dGame)
{
	int	fd;

	fd = open(fMap, O_RDONLY);
	if (!(ft_map_template(fd, dGame)))
		if (!(ft_map_sizer(dGame)))
			if (!(ft_items_finder(dGame)))
				if (!(ft_items_validator(dGame)))
					if (!(ft_boundary_checker(dGame)))
						if (!(ft_map_solution(dGame)))
							ft_enemies_finder(dGame);
	close(fd);
	return (dGame->f_error);
}

//"ft_game_exit": function that releases all memory allocations during
// the program's execution before terminating.
int	ft_game_exit(t_game *dGame)
{
	if (dGame->l_reward)
		ft_lstclear(&(dGame->l_reward), &free);
	if (dGame->l_wall)
		ft_lstclear(&(dGame->l_wall), &free);
	if (dGame->l_enemy)
		ft_lstclear(&(dGame->l_enemy), &free);
	if (dGame->p_map->m_map)
		ft_map_liberator(dGame->p_map->m_map, dGame->p_map->m_rc[0]);
	if (dGame->p_map->m_solution)
		ft_map_liberator(dGame->p_map->m_solution, dGame->p_map->m_rc[0]);
	if (dGame->p_game)
		mlx_destroy_window(dGame->p_game, dGame->p_win);
	exit(EXIT_SUCCESS);
}

// Main function that initiates the program and is responsible for executing
// each phase of the game sequentially.
int	main(int nImputs, char **vMap)
{
	t_game	d_game;

	ft_game_init(&d_game);
	if (nImputs == 2)
	{
		if (!(ft_file_checker(vMap[1], &d_game)))
		{
			if (!(ft_map_cheker(vMap[1], &d_game)))
			{
				ft_printf("\033[1;32m\n**********	START	**********\n");
				ft_game_loop(&d_game);
			}
		}
	}
	else
		d_game.f_error = 2;
	if (d_game.f_error)
	{
		ft_error_msg(d_game.f_error);
		ft_game_exit(&d_game);
	}
	return (0);
}

//END
