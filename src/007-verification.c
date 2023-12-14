/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   007-verification.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:23:24 by carperez          #+#    #+#             */
/*   Updated: 2023/12/07 11:35:31 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_player_finder": function to initialize and locate the player.
void	ft_player_finder(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (dGame->p_map->m_map[ir])
	{
		ic = 0;
		while (dGame->p_map->m_map[ir][ic])
		{
			if (dGame->p_map->m_map[ir][ic] == 'P')
			{
				dGame->d_player.n_steps = 0;
				dGame->d_player.f_status[0] = 0;
				dGame->d_player.f_status[1] = 0;
				dGame->d_player.rc[0] = ir;
				dGame->d_player.rc[1] = ic;
			}
			ic++;
		}
		ir ++;
	}
}

//"ft_exit_finder": function to initialize and locate the exit.
void	ft_exit_finder(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (dGame->p_map->m_map[ir])
	{
		ic = 0;
		while (dGame->p_map->m_map[ir][ic])
		{
			if (dGame->p_map->m_map[ir][ic] == 'E')
			{
				dGame->d_exit.f_end = 0;
				dGame->d_exit.f_status = 0;
				dGame->d_exit.rc[0] = ir;
				dGame->d_exit.rc[1] = ic;
			}
			ic++;
		}
		ir ++;
	}
}

//"ft_enemy_creator": function to create enemy nodes.
static void	*ft_enemy_creator(int rEnemy, int cEnemy, t_game *dGame)
{
	t_list	*p_nodo;

	p_nodo = ft_lstnew(NULL);
	if (p_nodo)
	{
		p_nodo->content = (void *)malloc(sizeof(t_enemy));
		if (p_nodo->content)
		{
			((t_enemy *)(p_nodo->content))->f_status[0] = 0;
			((t_enemy *)(p_nodo->content))->f_status[1] = 7;
			((t_enemy *)(p_nodo->content))->f_shift[0] = 0;
			((t_enemy *)(p_nodo->content))->f_shift[1] = 0;
			((t_enemy *)(p_nodo->content))->rc[0] = rEnemy;
			((t_enemy *)(p_nodo->content))->rc[1] = cEnemy;
		}
	}
	else
		dGame->f_error = 19;
	return (p_nodo);
}

//"ft_list_enemies_init": function to initialize and create
// the enemy list.
static void	ft_list_enemies_init(int rPosition, int cPosition, t_game *dGame)
{
	t_list	*p_aux;

	p_aux = ft_enemy_creator(rPosition, cPosition, dGame);
	if (!(dGame->f_error))
		ft_lstadd_back(&(dGame->l_enemy), p_aux);
	else
		dGame->f_error = 17;
}

//"ft_enemies_finder":function to locate the coordinates of
// each enemy and store it in the list.
void	ft_enemies_finder(t_game *dGame)
{
	int	ir;
	int	ic;

	if (dGame->d_items.n_enemy && ((dGame->p_map->m_rc[0] >= 3
				&& dGame->p_map->m_rc[1] >= 5) || (dGame->p_map->m_rc[0]
				>= 5 && dGame->p_map->m_rc[1] >= 3)))
	{
		ir = 0;
		while (dGame->p_map->m_map[ir] && !(dGame->f_error))
		{
			ic = 0;
			while (dGame->p_map->m_map[ir][ic] && !(dGame->f_error))
			{
				if (dGame->p_map->m_map[ir][ic] == 'H')
					ft_list_enemies_init((ir * IMG_SIZE),
						(ic * IMG_SIZE), dGame);
				ic++;
			}
			ir ++;
		}
	}
}

//END