/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   005-verification.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 20:23:24 by carperez          #+#    #+#             */
/*   Updated: 2023/12/07 11:35:31 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_map_solution": function to check if the map has a solution.
int	ft_map_solution(t_game *dGame)
{
	ft_exit_path(dGame);
	if (!(dGame->f_error))
	{
		ft_reward_fullpath(dGame);
		dGame->d_player.rc[0] *= IMG_SIZE;
		dGame->d_player.rc[1] *= IMG_SIZE;
		dGame->d_exit.rc[0] *= IMG_SIZE;
		dGame->d_exit.rc[1] *= IMG_SIZE;
		ft_list_rewards_normalization(dGame);
	}
	return (dGame->f_error);
}

//"ft_reward_creator": function to create reward nodes.
static void	*ft_reward_creator(int rReward, int cReward, t_game *dGame)
{
	t_list	*p_nodo;

	p_nodo = ft_lstnew(NULL);
	if (p_nodo)
	{
		p_nodo->content = (void *)malloc(sizeof(t_reward));
		if (p_nodo->content)
		{
			((t_reward *)(p_nodo->content))->f_status[0] = 0;
			((t_reward *)(p_nodo->content))->f_status[1] = rand() % 2;
			((t_reward *)(p_nodo->content))->f_status[2] = 0;
			((t_reward *)(p_nodo->content))->rc[0] = rReward;
			((t_reward *)(p_nodo->content))->rc[1] = cReward;
		}
	}
	else
		dGame->f_error = 18;
	return (p_nodo);
}

//"ft_list_rewards_init": function to initialize and create
// the reward list.
static void	ft_list_rewards_init(int rPosition, int cPosition, t_game *dGame)
{
	t_list	*p_aux;

	p_aux = ft_reward_creator(rPosition, cPosition, dGame);
	if (!(dGame->f_error))
		ft_lstadd_back(&(dGame->l_reward), p_aux);
	else
		dGame->f_error = 17;
}

//"ft_rewards_finder": function to locate the coordinates of
// each reward and store it in the list.
void	ft_rewards_finder(t_game *dGame)
{
	int	ia;
	int	ib;

	ia = 0;
	while (dGame->p_map->m_map[ia] && !(dGame->f_error))
	{
		ib = 0;
		while (dGame->p_map->m_map[ia][ib] && !(dGame->f_error))
		{
			if (dGame->p_map->m_map[ia][ib] == 'C')
				ft_list_rewards_init(ia, ib, dGame);
			ib++;
		}
		ia ++;
	}
}

//"ft_list_rewards_normalization": function to conver the coordinates
// of each reward to minilibx window pixels
void	ft_list_rewards_normalization(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_reward;
	if (p_aux)
	{
		((t_reward *)(p_aux->content))->rc[0] *= IMG_SIZE;
		((t_reward *)(p_aux->content))->rc[1] *= IMG_SIZE;
		if (!(dGame->f_error))
		{
			while (p_aux->next)
			{
				p_aux = p_aux->next;
				((t_reward *)(p_aux->content))->rc[0] *= IMG_SIZE;
				((t_reward *)(p_aux->content))->rc[1] *= IMG_SIZE;
			}
		}
	}
}

//END