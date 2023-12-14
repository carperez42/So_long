/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   015-player_enemy.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 00:43:21 by carperez          #+#    #+#             */
/*   Updated: 2023/12/12 22:00:09 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_rl_enemy": function to detect collision between the player and
// the enemy from the right and left sides.
static void	ft_player_rl_enemy(t_enemy *dEnemy, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[0] > dEnemy->rc[0] && p_aux->rc[0] < (dEnemy->rc[0]
				+ IMG_SIZE)) || ((p_aux->rc[0] + IMG_SIZE) < (dEnemy->rc[0]
				+ IMG_SIZE) && (p_aux->rc[0] + IMG_SIZE) > dEnemy->rc[0])
		|| ((p_aux->rc[0] + IMG_SIZE) == (dEnemy->rc[0] + IMG_SIZE)
			&& p_aux->rc[0] == dEnemy->rc[0]))
	{
		if ((p_aux->rc[1] + IMG_SIZE) > (dEnemy->rc[1] + (IMG_SIZE / 2))
			&& (p_aux->rc[1] + IMG_SIZE) < (dEnemy->rc[1] + IMG_SIZE))
			dGame->d_exit.f_end = 3;
		else if (p_aux->rc[1] < (dEnemy->rc[1] + (IMG_SIZE / 2))
			&& p_aux->rc[1] > dEnemy->rc[1])
			dGame->d_exit.f_end = 3;
	}
}

//"ft_player_rl_enemy": function to detect collision between the player and
// the enemy from the top and bottom sides.
static void	ft_player_du_enemy(t_enemy *dEnemy, t_game *dGame)
{
	t_player	*p_aux;

	p_aux = &(dGame->d_player);
	if ((p_aux->rc[1] > dEnemy->rc[1] && p_aux->rc[1] < (dEnemy->rc[1]
				+ IMG_SIZE)) || ((p_aux->rc[1] + IMG_SIZE) < (dEnemy->rc[1]
				+ IMG_SIZE) && (p_aux->rc[1] + IMG_SIZE) > dEnemy->rc[1])
		|| ((p_aux->rc[1] + IMG_SIZE) == (dEnemy->rc[1] + IMG_SIZE)
			&& p_aux->rc[1] == dEnemy->rc[1]))
	{
		if ((p_aux->rc[0] + IMG_SIZE) > (dEnemy->rc[0] + (IMG_SIZE / 2))
			&& (p_aux->rc[0] + IMG_SIZE) < (dEnemy->rc[0] + IMG_SIZE))
			dGame->d_exit.f_end = 3;
		else if (p_aux->rc[0] < (dEnemy->rc[0] + (IMG_SIZE / 2))
			&& p_aux->rc[0] > dEnemy->rc[0])
			dGame->d_exit.f_end = 3;
	}
	if (dGame->d_exit.f_end == 3)
		ft_printf("\033[1;31m\n~ **************************************** ~\n"
			"\n~\t\tOooUch No!\t\t   ~\n~ \tYou was Busted by a woman!\t   ~"
			"\n\n~ **************************************** ~\n\n\033[1;33mCl"
			"ose the game with ESC or close the window\n\n");
}

//"ft_player_collision_enemy": function to detect collision between the player
// and an enemy.
void	ft_player_collision_enemy(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_enemy;
	if (p_aux)
	{
		ft_player_rl_enemy(((t_enemy *)(p_aux->content)), dGame);
		ft_player_du_enemy(((t_enemy *)(p_aux->content)), dGame);
		if (dGame->d_exit.f_end != 3)
		{
			while (p_aux->next && (dGame->d_exit.f_end != 3))
			{
				p_aux = p_aux->next;
				ft_player_rl_enemy(((t_enemy *)(p_aux->content)), dGame);
				ft_player_du_enemy(((t_enemy *)(p_aux->content)), dGame);
			}
		}
	}
}

//END