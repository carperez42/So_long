/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   013-draw_items.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:12:05 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 16:28:25 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_enemy_draw": function to display enemies in the Minilibx window.
void	ft_enemy_draw(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_enemy;
	if (p_aux)
	{
		mlx_put_image_to_window(dGame->p_game, dGame->p_win,
			dGame->p_enemy[((t_enemy *)(p_aux->content))->f_status[1]],
			((t_enemy *)(p_aux->content))->rc[1],
			((t_enemy *)(p_aux->content))->rc[0]);
		while (p_aux->next)
		{
			p_aux = p_aux->next;
			mlx_put_image_to_window(dGame->p_game, dGame->p_win,
				dGame->p_enemy[((t_enemy *)(p_aux->content))->f_status[1]],
				((t_enemy *)(p_aux->content))->rc[1],
				((t_enemy *)(p_aux->content))->rc[0]);
		}
	}
}

//"ft_wall_draw": function to display walls in the Minilibx window.
void	ft_wall_draw(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_wall;
	if (p_aux)
	{
		mlx_put_image_to_window(dGame->p_game, dGame->p_win, dGame->p_wall,
			((t_wall *)(p_aux->content))->rc[1],
			((t_wall *)(p_aux->content))->rc[0]);
		while (p_aux->next)
		{
			p_aux = p_aux->next;
			mlx_put_image_to_window(dGame->p_game, dGame->p_win, dGame->p_wall,
				((t_wall *)(p_aux->content))->rc[1],
				((t_wall *)(p_aux->content))->rc[0]);
		}
	}
}

//"ft_reward_animation": function to switch between reward animations.
static void	ft_reward_animation(t_reward *dReward)
{
	if (!(dReward->f_status[2]))
	{
		if (dReward->f_status[0] == MAX_LOOPS)
		{
			dReward->f_status[0] = 0;
			if (dReward->f_status[1])
				dReward->f_status[1] = 0;
			else
				dReward->f_status[1] = 1;
		}
		else
			dReward->f_status[0]++;
	}
	else
		dReward->f_status[1] = 2;
}

//"ft_reward_draw": function to display rewards in the Minilibx window.
void	ft_reward_draw(t_game *dGame)
{
	t_list	*p_aux;

	p_aux = dGame->l_reward;
	if (p_aux)
	{

		ft_reward_animation(((t_reward *)(p_aux->content)));
		mlx_put_image_to_window(dGame->p_game, dGame->p_win,
			dGame->p_reward[((t_reward *)(p_aux->content))->f_status[1]],
			((t_reward *)(p_aux->content))->rc[1],
			((t_reward *)(p_aux->content))->rc[0]);
		while (p_aux->next)
		{
			p_aux = p_aux->next;
			ft_reward_animation(((t_reward *)(p_aux->content)));
			mlx_put_image_to_window(dGame->p_game, dGame->p_win,
				dGame->p_reward[((t_reward *)(p_aux->content))->f_status[1]],
				((t_reward *)(p_aux->content))->rc[1],
				((t_reward *)(p_aux->content))->rc[0]);
		}
	}
}

//"ft_exit_draw": function to display the exit in the Minilibx window.
void	ft_exit_draw(t_game *dGame)
{
	if (dGame->d_exit.f_end == 1)
		dGame->d_exit.f_status = 1;
	mlx_put_image_to_window(dGame->p_game, dGame->p_win,
		dGame->d_exit.p_exit[dGame->d_exit.f_status],
		dGame->d_exit.rc[1], dGame->d_exit.rc[0]);
}

//END


