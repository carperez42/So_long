/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   003-verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:39:48 by carperez          #+#    #+#             */
/*   Updated: 2023/12/13 22:53:26 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_map_template": function to generate a matrix equivalent to the game map.
int	ft_map_template(int dFile, t_game *dGame)
{
	char	*s_file;
	char	*p_aux;

	s_file = NULL;
	p_aux = get_next_line(dFile);
	if (p_aux)
	{
		while (p_aux)
		{
			s_file = ft_map_strjoin(s_file, p_aux);
			free(p_aux);
			p_aux = NULL;
			p_aux = get_next_line(dFile);
		}
		ft_map_init(s_file, dGame);
	}
	else
		dGame->f_error = 5;
	return (dGame->f_error);
}

//"t_map_sizer": function to obtain the dimensions of the game map matrix and
// verify that it is rectangular.
int	ft_map_sizer(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	dGame->p_map->m_rc[1] = ft_strlen(dGame->p_map->m_map[0]);
	while (dGame->p_map->m_map[ir])
	{
		dGame->p_map->m_rc[0]++;
		ic = ft_strlen(dGame->p_map->m_map[ir]);
		if (ic != dGame->p_map->m_rc[1] && !(dGame->f_error))
			dGame->f_error = 8;
		ir ++;
	}
	if (!(dGame->f_error))
	{
		dGame->g_size[0] = ic * IMG_SIZE;
		dGame->g_size[1] = (ir + 1) * IMG_SIZE;
	}
	return (dGame->f_error);
}

//"ft_items_counter": function to count the number of items in the map.
static int	ft_items_counter(char cItem, t_game *dGame)
{
	int	f_aux;

	f_aux = 0;
	if (cItem == 'C')
	{
		dGame->d_items.n_reward ++;
		f_aux ++;
	}
	else if (cItem == 'E')
	{
		dGame->d_items.n_exit ++;
		f_aux ++;
	}
	else if (cItem == 'P')
	{
		dGame->d_items.n_player ++;
		f_aux ++;
	}
	else if (cItem == 'H')
	{
		dGame->d_items.n_enemy ++;
		f_aux ++;
	}
	return (f_aux);
}

//"ft_items_finder": function to detect items within the map.
int	ft_items_finder(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (dGame->p_map->m_map[ir])
	{
		ic = 0;
		while (dGame->p_map->m_map[ir][ic])
		{
			if (!(ft_items_counter(dGame->p_map->m_map[ir][ic], dGame)))
			{
				if ((dGame->p_map->m_map[ir][ic] != '1')
					&& (dGame->p_map->m_map[ir][ic] != '0'))
					dGame->f_error = 9;
			}
			ic++;
		}
		ir ++;
	}
	return (dGame->f_error);
}

//"ft_items_validator": function to check if any item of the map does not
// meet the requirements.
int	ft_items_validator(t_game *dGame)
{
	if (dGame->d_items.n_exit != 1)
		dGame->f_error = 10;
	else if (dGame->d_items.n_player != 1)
		dGame->f_error = 11;
	else if (dGame->d_items.n_reward < 1)
		dGame->f_error = 12;
	else
	{
		ft_exit_finder(dGame);
		ft_player_finder(dGame);
		ft_rewards_finder(dGame);
	}
	return (dGame->f_error);
}

//END