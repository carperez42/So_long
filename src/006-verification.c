/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   006-verification.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:23:24 by carperez          #+#    #+#             */
/*   Updated: 2023/12/07 11:35:31 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_wall_creator": function to create wall nodes.
static void	*ft_wall_creator(int rWall, int cWall, t_game *dGame)
{
	t_list	*p_nodo;

	p_nodo = ft_lstnew(NULL);
	if (p_nodo)
	{
		p_nodo->content = (void *)malloc(sizeof(t_wall));
		if (p_nodo->content)
		{
			((t_wall *)(p_nodo->content))->rc[0] = rWall;
			((t_wall *)(p_nodo->content))->rc[1] = cWall;
		}
	}
	else
		dGame->f_error = 14;
	return (p_nodo);
}

//"ft_list_wall_init": function to initialize and create
// the wall list.
static void	ft_list_walls_init(int rPosition, int cPosition, t_game *dGame)
{
	t_list	*p_aux;

	p_aux = ft_wall_creator(rPosition, cPosition, dGame);
	if (!(dGame->f_error))
		ft_lstadd_back(&(dGame->l_wall), p_aux);
	else
		dGame->f_error = 17;
}

//"ft_wall_finder": function to locate the coordinates of
// each wall and store it in the list.
void	ft_walls_finder(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (dGame->p_map->m_map[ir] && !(dGame->f_error))
	{
		ic = 0;
		while (dGame->p_map->m_map[ir][ic] && !(dGame->f_error))
		{
			if (dGame->p_map->m_map[ir][ic] == '1')
				ft_list_walls_init((ir * IMG_SIZE), (ic * IMG_SIZE), dGame);
			ic++;
		}
		ir ++;
	}
}

//"ft_boundary_checker": function to confirm if the map
// borders are closed.
int	ft_boundary_checker(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (!(dGame->f_error) && dGame->p_map->m_map[ir])
	{
		ic = 0;
		while (!(dGame->f_error) && dGame->p_map->m_map[ir][ic])
		{
			if (dGame->p_map->m_map[ir][ic] != '1')
			{
				if (ir == 0 || ir == (dGame->p_map->m_rc[0] - 1))
					dGame->f_error = 13;
				else if (ic == 0 || ic == (dGame->p_map->m_rc[1] - 1))
					dGame->f_error = 13;
			}
			ic ++;
		}
		ir ++;
	}
	if (!(dGame->f_error))
		ft_walls_finder(dGame);
	return (dGame->f_error);
}

//END