/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   002-verification.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carperez <carperez@student.45madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 21:39:48 by carperez          #+#    #+#             */
/*   Updated: 2023/12/13 22:53:10 by carperez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/so_long.h"

//"ft_format_checker": function to check if the map has the correct
// format.
static int	ft_format_checker(const char *sMain, const char *sSub
			, t_game *dGame)
{
	char	*p_aux;

	if ((sMain != sSub) && *sSub)
	{
		while (*sMain != '\0')
		{
			p_aux = (char *)sSub;
			while (*sMain == *p_aux && *sMain)
			{
				sMain ++;
				p_aux ++;
			}
			if (*p_aux == '\0')
				return (dGame->f_error);
			sMain ++;
		}
	}
	return (dGame->f_error = 3, dGame->f_error);
}

//"ft_file_checker": function to check if the map can be opened.
int	ft_file_checker(char *fMap, t_game *dGame)
{
	if (open(fMap, O_RDONLY) > 0)
		ft_format_checker(fMap, ".ber", dGame);
	else
		dGame->f_error = 4;
	return (dGame->f_error);
}

//"ft_map_cleaner": function to convert all values in the matrix that
// are different from 1 to 0.
void	ft_map_cleaner(t_game *dGame)
{
	int	ir;
	int	ic;

	ir = 0;
	while (dGame->p_map->m_solution[ir])
	{
		ic = 0;
		while (dGame->p_map->m_solution[ir][ic])
		{
			if (dGame->p_map->m_map[ir][ic] != '1')
				dGame->p_map->m_solution[ir][ic] = '0';
			ic ++;
		}
		ir ++;
	}
}

//"ft_map_init": function to initialize the matrix values with the values
// from the map.
void	ft_map_init(char *sFile, t_game *dGame)
{
	if (sFile)
		dGame->p_map->m_map = ft_split(sFile, '\n');
	if (dGame->p_map->m_map)
	{
		dGame->p_map->m_solution = ft_split(sFile, '\n');
		if (dGame->p_map->m_solution)
			ft_map_cleaner(dGame);
		else
			dGame->f_error = 7;
		free(sFile);
	}
	else
		dGame->f_error = 6;
}

//"ft_map_strjoin": function to concatenate two different strings.
char	*ft_map_strjoin(char *sResult, char const *sAdd)
{
	char	*p_newbuff;
	int		l_front;
	int		l_back;

	p_newbuff = NULL;
	if (sResult)
		l_front = ft_strlen(sResult);
	else
		l_front = 0;
	l_back = ft_strlen(sAdd);
	p_newbuff = malloc (sizeof(char) * (l_front + l_back + 1));
	if (p_newbuff != NULL)
	{
		if (l_front == 0)
			ft_memcpy(p_newbuff, sAdd, l_back + 1);
		else
		{
			ft_memcpy(p_newbuff, sResult, l_front);
			ft_memcpy(&p_newbuff[l_front], sAdd, l_back + 1);
		}
	}
	return (p_newbuff);
}

//END