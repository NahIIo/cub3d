/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:23:17 by jchauvet          #+#    #+#             */
/*   Updated: 2023/12/11 11:48:28 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_top_or_bottom(char **map_tab, int i, int j)
{
	if (!map_tab || !map_tab[i] || !map_tab[i][j])
		return (FAILURE);
	while (map_tab[i][j] == ' ' || map_tab[i][j] == '\t'
	|| map_tab[i][j] == '\r' || map_tab[i][j] == '\v'
	|| map_tab[i][j] == '\f' || map_tab[i][j] == '1')
		j++;
//	if (j < (int)ft_strlen(map_tab[i]))
	//	return (FAILURE);
	return (SUCCESS);
}

int	check_map_sides(t_mapinfo *map, char **map_tab)
{
	int	i;

	if (check_top_or_bottom(map_tab, 0, 0) == FAILURE)
		return (FAILURE);
	i = 1;
	while (i < (map->height - 1))
		i++;
	if (check_top_or_bottom(map_tab, i, 0) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
