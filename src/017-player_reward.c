/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   017-player_reward.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:23:13 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 17:12:42 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_rl_reward": function to detect collision between the player and
// the reward from the right and left sides.
static void	ft_player_rl_reward(t_reward *dReward, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[0] > dReward->rc[0] && p_aux->rc[0] < (dReward->rc[0]
				+ IMG_SIZE)) || ((p_aux->rc[0] + IMG_SIZE) < (dReward->rc[0]
				+ IMG_SIZE) && (p_aux->rc[0] + IMG_SIZE) > dReward->rc[0])
		|| ((p_aux->rc[0] + IMG_SIZE) == (dReward->rc[0] + IMG_SIZE)
			&& p_aux->rc[0] == dReward->rc[0]))
	{
		if ((p_aux->rc[1] + IMG_SIZE) > (dReward->rc[1] + (IMG_SIZE
					- (IMG_SIZE / 3))) && (p_aux->rc[1] + IMG_SIZE)
			< (dReward->rc[1] + IMG_SIZE))
			dReward->f_status[2] = 1;
		else if (p_aux->rc[1] < (dReward->rc[1] + (IMG_SIZE / 3))
			&& p_aux->rc[1] > dReward->rc[1])
			dReward->f_status[2] = 1;
	}
	if (dReward->f_status[2])
		dGame->d_items.n_reward --;
}

//"ft_player_du_reward": function to detect collision between the player and
// the reward from the top and bottom sides.
static void	ft_player_du_reward(t_reward *dReward, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[1] > dReward->rc[1] && p_aux->rc[1] < (dReward->rc[1]
				+ IMG_SIZE)) || ((p_aux->rc[1] + IMG_SIZE) < (dReward->rc[1]
				+ IMG_SIZE) && (p_aux->rc[1] + IMG_SIZE) > dReward->rc[1])
		|| ((p_aux->rc[1] + IMG_SIZE) == (dReward->rc[1] + IMG_SIZE)
			&& p_aux->rc[1] == dReward->rc[1]))
	{
		if ((p_aux->rc[0] + IMG_SIZE) > (dReward->rc[0] + (IMG_SIZE
					- (IMG_SIZE / 3))) && (p_aux->rc[0] + IMG_SIZE)
			< (dReward->rc[0] + IMG_SIZE))
			dReward->f_status[2] = 1;
		else if (p_aux->rc[0] < (dReward->rc[0] + (IMG_SIZE / 3))
			&& p_aux->rc[0] > dReward->rc[0])
			dReward->f_status[2] = 1;
	}
	if (dReward->f_status[2])
		dGame->d_items.n_reward --;
}

//"ft_player_reward_collect": function to detect collision between the player
// and an reward.
void	ft_player_reward_collect(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_reward;
	if (p_aux)
	{
		if (!(((t_reward *)(p_aux->content))->f_status[2]))
		{
			ft_player_rl_reward(((t_reward *)(p_aux->content)), dGame);
			if (!(((t_reward *)(p_aux->content))->f_status[2]))
				ft_player_du_reward(((t_reward *)(p_aux->content)), dGame);
		}
		while (p_aux->next && (dGame->d_exit.f_end != 3))
		{
			p_aux = p_aux->next;
			if (!(((t_reward *)(p_aux->content))->f_status[2]))
			{
				ft_player_rl_reward(((t_reward *)(p_aux->content)), dGame);
				if (!(((t_reward *)(p_aux->content))->f_status[2]))
					ft_player_du_reward(((t_reward *)(p_aux->content)), dGame);
			}
		}
	}
}

//END