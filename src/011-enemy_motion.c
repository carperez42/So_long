/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   011-enemy_motion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 23:05:40 by carperez          #+#    #+#             */
/*   Updated: 2023/12/14 16:06:29 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_enemy_motion_set": function to configure the movement of the enemy.
static void	ft_enemy_motion_set(t_list *dEnemy)
{
	int	ia;
	int	ib;

	ia = rand() % 2;
	ib = rand() % 2;
	if (ib == 1)
		((t_enemy *)(dEnemy->content))->rc[ia] += ENEMY_SPEED;
	else
		((t_enemy *)(dEnemy->content))->rc[ia] -= ENEMY_SPEED;
	((t_enemy *)(dEnemy->content))->f_shift[0] = ia;
	((t_enemy *)(dEnemy->content))->f_shift[1] = ib;
	((t_enemy *)(dEnemy->content))->f_status[0] += 1;
}

//"ft_enemy_motion_update": function to update the position of the enemy.
static void	ft_enemy_motion_update(t_list *dEnemy)
{
	int	ia;

	ia = ((t_enemy *)(dEnemy->content))->f_shift[0];
	((t_enemy *)(dEnemy->content))->f_status[0]++;
	if (((t_enemy *)(dEnemy->content))->f_shift[1] == 1)
		((t_enemy *)(dEnemy->content))->rc[ia] += ENEMY_SPEED;
	else
		((t_enemy *)(dEnemy->content))->rc[ia] -= ENEMY_SPEED;
	if (((t_enemy *)(dEnemy->content))->f_status[0] == MAX_LOOPS)
		((t_enemy *)(dEnemy->content))->f_status[0] = 0;
}

//"ft_enemy_image_change": function to alternate between animations in one
// direction of the enemy.
static void	ft_enemy_image_change(t_list *dEnemy, int image_a, int image_b)
{
	if (((t_enemy *)(dEnemy->content))->f_status[1] == image_a)
		((t_enemy *)(dEnemy->content))->f_status[1] = image_b;
	else
		((t_enemy *)(dEnemy->content))->f_status[1] = image_a;
}

//"ft_enemy_image_set": function to set the animations corresponding to
// the current direction of the enemy.
static void	ft_enemy_image_set(t_list *dEnemy)
{
	int	ia;
	int	ib;

	ia = ((t_enemy *)(dEnemy->content))->f_shift[0];
	ib = ((t_enemy *)(dEnemy->content))->f_shift[1];

	if (ia == 0 && ib == 0)
		ft_enemy_image_change(dEnemy, 4, 5);
	else if (ia == 0 && ib == 1)
		ft_enemy_image_change(dEnemy, 6, 7);
	else if (ia == 1 && ib == 1)
		ft_enemy_image_change(dEnemy, 0, 1);
	else if (ia == 1 && ib == 0)
		ft_enemy_image_change(dEnemy, 2, 3);
}

//"ft_enemy_shift": function to manage enemy movement.
void	ft_enemy_shift(t_list *dEnemy)
{
	if (((t_enemy *)(dEnemy->content))->f_status[0] == 0)
		ft_enemy_motion_set(dEnemy);
	else
		ft_enemy_motion_update(dEnemy);
	ft_enemy_image_set(dEnemy);
}

//END