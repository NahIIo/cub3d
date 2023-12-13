/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 14:44:57 by jchauvet          #+#    #+#             */
/*   Updated: 2023/12/11 11:22:28 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_a_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\r'
		|| c == '\n' || c == '\v' || c == '\f' || c == ' ')
		return (SUCCESS);
	else
		return (FAILURE);
}

size_t	find_biggest_len(t_mapinfo *map, int i)
{
	size_t	biggest_len;

	biggest_len = ft_strlen(map->file[i]);
	while (map->file[i])
	{
		if (ft_strlen(map->file[i]) > biggest_len)
			biggest_len = ft_strlen(map->file[i]);
		i++;
	}
	return (biggest_len);
}

static int	last_check_utils(char **map, int i, int j)
{
	if (map[i][j + 1] && !ft_strchr("01NSWE", map[i][j + 1]))
		return (FAILURE);
	if (map[i][j - 1] && !ft_strchr("01NSWE", map[i][j - 1]))
		return (FAILURE);
	if (map[i + 1] && map[i + 1][j] && !ft_strchr("01NSWE", map[i + 1][j]))
		return (FAILURE);
	if (map[i - 1] && map[i - 1][j] && !ft_strchr("01NSWE", map[i - 1][j]))
		return (FAILURE);
	return (SUCCESS);
}

int	last_check(t_mapinfo *mapinfo, int i)
{
	int	j;

	while (mapinfo->file[i])
	{
		j = 0;
		while (mapinfo->file[i][j])
		{
			if (mapinfo->file[i][j] && ft_strchr("0NSWE", mapinfo->file[i][j]))
			{
				if ((int)ft_strlen(mapinfo->file[i - 1]) < j)
					return (FAILURE);
				if (j == 0 || !mapinfo->file[i + 1])
					return (FAILURE);
				if (mapinfo->file[i + 1]
					&& (int)ft_strlen(mapinfo->file[i + 1]) <= j)
					return (FAILURE);
				if (last_check_utils(mapinfo->file, i, j) == FAILURE)
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	check_whitespaces(char *string)
{
	int	j;

	j = 0;
	if (string[j])
		while (string[j] == ' ' || string[j] == '\t' || string[j] == '\r'
			|| string[j] == '\v' || string[j] == '\f')
			j++;
	return (j);
}
