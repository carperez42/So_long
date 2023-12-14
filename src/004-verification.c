/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   004-verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:23:24 by carperez          #+#    #+#             */
/*   Updated: 2023/12/13 21:00:48 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_exitpath_finder": function to check if there is a path from the player's
// position on the map to the exit.
static void	ft_exitpath_finder(int rPlayer, int cPlayer, t_game *dGame)
{
	if (rPlayer < 0 || cPlayer < 0 || rPlayer == dGame->p_map->m_rc[0]
		|| cPlayer == dGame->p_map->m_rc[1] || dGame->p_map->f_solution)
		return ;
	if (rPlayer == dGame->d_exit.rc[0] && cPlayer == dGame->d_exit.rc[1]
		&& !(dGame->p_map->f_solution))
	{
		dGame->p_map->f_solution = 1;
		return ;
	}
	if (dGame->p_map->m_solution[rPlayer][cPlayer] != '0'
			&& !(dGame->p_map->f_solution))
		return ;
	if (dGame->p_map->m_solution[rPlayer][cPlayer]
			&& !(dGame->p_map->f_solution))
	{
		dGame->p_map->m_solution[rPlayer][cPlayer] = '+';
		ft_exitpath_finder(rPlayer, cPlayer + 1, dGame);
		ft_exitpath_finder(rPlayer, cPlayer - 1, dGame);
		ft_exitpath_finder(rPlayer - 1, cPlayer, dGame);
		ft_exitpath_finder(rPlayer + 1, cPlayer, dGame);
	}
}

//"ft_rewardpath_finder": function to check if there is a path from
// the player's position to the collectible.
static void	ft_rewardpath_finder(int rPlayer, int cPlayer, t_reward *dReward
		, t_game *dGame)
{
	if (rPlayer < 0 || cPlayer < 0 || rPlayer == dGame->p_map->m_rc[0]
		|| cPlayer == dGame->p_map->m_rc[1] || dGame->p_map->f_solution)
		return ;
	if (rPlayer == dReward->rc[0] && cPlayer == dReward->rc[1]
		&& !(dGame->p_map->f_solution))
	{
		dGame->p_map->f_solution = 1;
		return ;
	}
	if (dGame->p_map->m_solution[rPlayer][cPlayer] != '0'
			&& !(dGame->p_map->f_solution))
		return ;
	if (dGame->p_map->m_solution[rPlayer][cPlayer]
			&& !(dGame->p_map->f_solution))
	{
		dGame->p_map->m_solution[rPlayer][cPlayer] = '+';
		ft_rewardpath_finder(rPlayer, cPlayer + 1, dReward, dGame);
		ft_rewardpath_finder(rPlayer, cPlayer - 1, dReward, dGame);
		ft_rewardpath_finder(rPlayer - 1, cPlayer, dReward, dGame);
		ft_rewardpath_finder(rPlayer + 1, cPlayer, dReward, dGame);
	}
}

//"ft_exit_path": function to confirm if there is a path to the exit.
void	ft_exit_path(t_game *dGame)
{
	ft_exitpath_finder(dGame->d_player.rc[0], dGame->d_player.rc[1], dGame);
	if (!(dGame->p_map->f_solution))
		dGame->f_error = 15;
	dGame->p_map->f_solution = 0;
	ft_map_cleaner(dGame);
}

//"ft_reward_path": function to confirm if there is a path to the collectible.
static void	ft_reward_path(t_reward *dReward, t_game *dGame)
{
	ft_rewardpath_finder(dGame->d_player.rc[0], dGame->d_player.rc[1],
		dReward, dGame);
	if (!(dGame->p_map->f_solution))
		dGame->f_error = 16;
	dGame->p_map->f_solution = 0;
	ft_map_cleaner(dGame);
}

//"ft_reward_fullpath": unction to verify the path to all collectibles
// on the map.
void	ft_reward_fullpath(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_reward;
	if (p_aux)
	{
		ft_reward_path(((t_reward *)(p_aux->content)), dGame);
		if (!(dGame->f_error))
		{
			while (p_aux->next != NULL)
			{
				p_aux = p_aux->next;
				ft_reward_path(((t_reward *)(p_aux->content)), dGame);
			}
		}
	}
}

//END