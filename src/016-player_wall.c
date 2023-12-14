/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   016-player_wall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 22:20:55 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 16:58:37 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_rl_wall": function to detect collision of the player from the right
// and left sides of a wall.
static void	ft_player_rl_wall(t_wall *dWall, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[0] > dWall->rc[0] && p_aux->rc[0] < (dWall->rc[0]
				+ IMG_SIZE)) || ((p_aux->rc[0] + IMG_SIZE) < (dWall->rc[0]
				+ IMG_SIZE) && (p_aux->rc[0] + IMG_SIZE) > dWall->rc[0])
		|| ((p_aux->rc[0] + IMG_SIZE) == (dWall->rc[0] + IMG_SIZE)
			&& p_aux->rc[0] == dWall->rc[0]))
	{
		if ((p_aux->rc[1] + IMG_SIZE) > dWall->rc[1]
			&& (p_aux->rc[1] + IMG_SIZE) < (dWall->rc[1] + IMG_SIZE))
		{
			p_aux->rc[1] = dWall->rc[1] - IMG_SIZE;
		}
		else if (p_aux->rc[1] < (dWall->rc[1] + IMG_SIZE)
			&& p_aux->rc[1] > dWall->rc[1])
		{
			p_aux->rc[1] = dWall->rc[1] + IMG_SIZE;
		}
	}
}

//"ft_player_du_wall": function to detect player collision from the top and
// bottom sides of a wall.
static void	ft_player_du_wall(t_wall *dWall, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[1] > dWall->rc[1] && p_aux->rc[1] < (dWall->rc[1]
				+ IMG_SIZE)) || ((p_aux->rc[1] + IMG_SIZE) < (dWall->rc[1]
				+ IMG_SIZE) && (p_aux->rc[1] + IMG_SIZE) > dWall->rc[1])
		|| ((p_aux->rc[1] + IMG_SIZE) == (dWall->rc[1] + IMG_SIZE)
			&& p_aux->rc[1] == dWall->rc[1]))
	{
		if ((p_aux->rc[0] + IMG_SIZE) > dWall->rc[0]
			&& (p_aux->rc[0] + IMG_SIZE) < (dWall->rc[0] + IMG_SIZE))
		{
			p_aux->rc[0] = dWall->rc[0] - IMG_SIZE;
		}
		else if (p_aux->rc[0] < (dWall->rc[0] + IMG_SIZE)
			&& p_aux->rc[0] > dWall->rc[0])
		{
			p_aux->rc[0] = dWall->rc[0] + IMG_SIZE;
		}
	}
}

//"ft_player_rectification": function to correct the position of the player when
// colliding with a wall.
void	ft_player_rectification(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_wall;
	if (p_aux)
	{
		ft_player_rl_wall(((t_wall *)(p_aux->content)), dGame);
		ft_player_du_wall(((t_wall *)(p_aux->content)), dGame);
		while (p_aux->next && (dGame->d_exit.f_end != 3))
		{
			p_aux = p_aux->next;
			ft_player_rl_wall(((t_wall *)(p_aux->content)), dGame);
			ft_player_du_wall(((t_wall *)(p_aux->content)), dGame);
		}
	}
}

//END