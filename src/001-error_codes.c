/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   001-error_codes.c									:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:10:20 by carperez          #+#    #+#             */
/*   Updated: 2023/12/07 11:37:54 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

static void	ft_error_msg_e(int nError)
{
	if (nError == 19)
	{
		ft_printf("\033[1;31mMSG(%d)->Error mapping"
			" the collectable!\n", nError);
	}
}

static void	ft_error_msg_d(int nError)
{
	if (nError == 13)
		ft_printf("\033[1;31m\nMSG(%d)->The map is not closed!\n", nError);
	else if (nError == 14)
		ft_printf("\033[1;31m\nMSG(%d)->Error mapping the walls!\n", nError);
	else if (nError == 15)
	{
		ft_printf("\033[1;31m\nMSG(%d)->There is no way"
			" to the exit!\n", nError);
	}
	else if (nError == 16)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Some collectibles"
			" are unreachable!\n", nError);
	}
	else if (nError == 17)
		ft_printf("\033[1;31m\nMSG(%d)->Error generating the list!\n", nError);
	else if (nError == 18)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Error mapping"
			" the collectable!\n", nError);
	}
	else
		ft_error_msg_e(nError);
}

static void	ft_error_msg_c(int nError)
{
	if (nError == 9)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Map template with wrong"
			" character!\n", nError);
	}
	else if (nError == 10)
	{
		ft_printf("\033[1;31m\nMSG(%d)->The map don't have exit or"
			" have more than one exit!\n", nError);
	}
	else if (nError == 11)
	{
		ft_printf("\033[1;31m\nMSG(%d)->The map don't have player or"
			" have more than one player!\n", nError);
	}
	else if (nError == 12)
	{
		ft_printf("\033[1;31m\nMSG(%d)->The map don't have"
			" collectables!\n", nError);
	}
	else
		ft_error_msg_d(nError);
}

static void	ft_error_msg_b(int nError)
{
	if (nError == 5)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Error in allocating memory for"
			" p_aux in 'ft_map_layout'!\n", nError);
	}
	else if (nError == 6)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Error in allocating memory"
			" for m_map in 'ft_matrix_init'!\n", nError);
	}
	if (nError == 7)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Error in allocating memory"
			" for m_solution in 'ft_matrix_init'!\n", nError);
	}
	if (nError == 8)
	{
		ft_printf("\033[1;31m\nMSG(%d)->This map template is not"
			" rectangular!\n", nError);
	}

	else
		ft_error_msg_c(nError);
}

// "ft_error_msg": main function to manage program error messages.
void	ft_error_msg(int nError)
{
	if (nError == 1)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Error in allocating memory"
			" for p_map in 'ft_map_init'!\n", nError);
	}
	else if (nError == 2)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Incorrect number of arguments\n",
			nError);
		ft_printf("\033[1;33mPlease introduce ONE file .ber like this"
			" example:\n./so_long map.ber\n");
	}
	else if (nError == 3)
	{
		ft_printf("\033[1;31m\nMSG(%d)->Unsupported file format!\n", nError);
		ft_printf("\033[1;33mPlease introduce ONE file .ber like this"
			" example:\n./so_long map.ber\n", nError);
	}
	else if (nError == 4)
		ft_printf("\033[1;31m\nMSG(%d)->The file cannot be opened!\n", nError);
	else
		ft_error_msg_b(nError);
}

//END

