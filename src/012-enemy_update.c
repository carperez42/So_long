/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   012-enemy_update.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:28:47 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 16:59:47 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_enemy_rl_wall": function to detect collision of the enemy from the right
// and left sides of a wall.
static void	ft_enemy_rl_wall(t_enemy *dEnemy, t_wall *dWall)
{
	if ((dEnemy->rc[0] >= dWall->rc[0] && dEnemy->rc[0]
			< (dWall->rc[0] + IMG_SIZE)) || ((dEnemy->rc[0] + IMG_SIZE)
			<= (dWall->rc[0] + IMG_SIZE) && (dEnemy->rc[0] + IMG_SIZE)
			> dWall->rc[0]))
	{
		if ((dEnemy->rc[1] + IMG_SIZE) > dWall->rc[1]
			&& (dEnemy->rc[1] + IMG_SIZE) < (dWall->rc[1] + IMG_SIZE))
		{
			dEnemy->rc[1] = dWall->rc[1] - IMG_SIZE;
			dEnemy->f_shift[1] = 0;
			dEnemy->f_status[1] = 2;
			dEnemy->f_status[0] = 0;
		}
		else if (dEnemy->rc[1] < (dWall->rc[1] + IMG_SIZE)
			&& dEnemy->rc[1] > dWall->rc[1])
		{
			dEnemy->rc[1] = dWall->rc[1] + IMG_SIZE;
			dEnemy->f_shift[1] = 1;
			dEnemy->f_status[1] = 1;
			dEnemy->f_status[0] = 0;
		}
	}
}

//"ft_enemy_du_wall": function to detect enemy collision from the top and
// bottom sides of a wall.
static void	ft_enemy_du_wall(t_enemy *dEnemy, t_wall *dWall)
{
	if ((dEnemy->rc[1] >= dWall->rc[1] && dEnemy->rc[1]
			< (dWall->rc[1] + IMG_SIZE)) || ((dEnemy->rc[1] + IMG_SIZE)
			<= (dWall->rc[1] + IMG_SIZE) && (dEnemy->rc[1] + IMG_SIZE)
			> dWall->rc[1]))
	{
		if ((dEnemy->rc[0] + IMG_SIZE) > dWall->rc[0]
			&& (dEnemy->rc[0] + IMG_SIZE) < (dWall->rc[0] + IMG_SIZE))
		{
			dEnemy->rc[0] = dWall->rc[0] - IMG_SIZE;
			dEnemy->f_shift[0] = 0;
			dEnemy->f_status[0] = 4;
			dEnemy->f_status[0] = 0;
		}
		else if (dEnemy->rc[0] < (dWall->rc[0] + IMG_SIZE)
			&& dEnemy->rc[0] > dWall->rc[0])
		{
			dEnemy->rc[0] = dWall->rc[0] + IMG_SIZE;
			dEnemy->f_shift[0] = 1;
			dEnemy->f_status[0] = 6;
			dEnemy->f_status[0] = 0;
		}
	}
}

//"ft_enemy_rectification": function to correct the position of the enemies when
// colliding with a wall.
static void	ft_enemy_rectification(t_enemy *dEnemy, t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_wall;
	if (p_aux)
	{
		ft_enemy_rl_wall(dEnemy, ((t_wall *)(p_aux->content)));
		ft_enemy_du_wall(dEnemy, ((t_wall *)(p_aux->content)));
		while (p_aux->next)
		{
			p_aux = p_aux->next;
			ft_enemy_rl_wall(dEnemy, ((t_wall *)(p_aux->content)));
			ft_enemy_du_wall(dEnemy, ((t_wall *)(p_aux->content)));
		}
	}
}

//"ft_enemy_update": function to handle collisions of enemies when they collide
// with any wall on the map.
void	ft_enemy_update(t_game *dGame)
{
	t_list	*p_aux;

	if (dGame->d_exit.f_end != 3)
	{
		p_aux = dGame->l_enemy;
		if (p_aux)
		{
			ft_enemy_shift(p_aux);
			ft_enemy_rectification(((t_enemy *)(p_aux->content)), dGame);
			while (p_aux->next)
			{
				p_aux = p_aux->next;
				ft_enemy_shift(p_aux);
				ft_enemy_rectification(((t_enemy *)(p_aux->content)), dGame);
			}
		}
	}
}

//END