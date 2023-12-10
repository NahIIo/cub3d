/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:23:30 by jchauvet          #+#    #+#             */
/*   Updated: 2023/11/21 10:23:31 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;
	int	j;

	index_value = i;
	while (file[i])
	{
		j = 0;
		while (file[i][j] == ' ' || file[i][j] == '\t' || file[i][j] == '\r'
		|| file[i][j] == '\v' || file[i][j] == '\f'|| file[i][j] == '\n')
			j++;
		if (file[i][0] == '\n')
			i++;
		else if (file[i][j] != '1')
			break ;
		i++;
	}
	data->mapinfo.index_end_of_map = i;
	return (i - index_value);
}

static int	fill_map_tab(t_mapinfo *mapinfo, char **map_tab, int index)
{
	int		i;
	int		j;

	mapinfo->width = find_biggest_len(mapinfo, index);
	i = 0;
	while (i < mapinfo->height)
	{
		j = 0;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (mapinfo->file[index][j] && mapinfo->file[index][j] != '\n')
		{
			map_tab[i][j] = mapinfo->file[index][j];
			j++;
		}	
		while (j < mapinfo->width)
			map_tab[i][j++] = '\0';
		i++;
		index++;
	}
	map_tab[i] = NULL;
	return (SUCCESS);
}

static int	get_map_info(t_data *data, char **file, int i)
{
	data->mapinfo.height = count_map_lines(data, file, i);
	data->map = malloc(sizeof(char *) * (data->mapinfo.height + 1));
	if (!data->map)
		return (err_msg(NULL, ERR_MALLOC, FAILURE));
	if (fill_map_tab(&data->mapinfo, data->map, i) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

static void	change_space_into_wall(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] == ' ' || data->map[i][j] == '\t'
		|| data->map[i][j] == '\r'
		|| data->map[i][j] == '\v' || data->map[i][j] == '\f')
			j++;
		while (data->map[i][++j])
		{
			if (data->map[i][j] == ' '
				&& j != data->map[i][ft_strlen(data->map[i]) - 1])
				data->map[i][j] = '1';
		}
		i++;
	}
}

static int	last_check(t_mapinfo *mapinfo, int i)
{
	int	j;

	while (mapinfo->file[i])
	{
		j = 0;
		while (mapinfo->file[i][j])
		{
			if (mapinfo->file[i][j] && ft_strchr("0NSWE", mapinfo->file[i][j]))
			{
				if ((int)ft_strlen(mapinfo->file[i - 1])< j)
					return (FAILURE);
				if (mapinfo->file[i + 1] && (int)ft_strlen(mapinfo->file[i + 1])< j)
					return (FAILURE);
				if (mapinfo->file[i][j + 1] && !ft_strchr("01NSWE", mapinfo->file[i][j + 1]))
					return (FAILURE);
				if (mapinfo->file[i][j - 1] && !ft_strchr("01NSWE", mapinfo->file[i][j - 1]))
					return (FAILURE);
				if (mapinfo->file[i + 1] && mapinfo->file[i + 1][j] && !ft_strchr("01NSWE", mapinfo->file[i + 1][j]))
					return (FAILURE);
				if (mapinfo->file[i - 1] && mapinfo->file[i - 1][j] && !ft_strchr("01NSWE", mapinfo->file[i - 1][j]))
					return (FAILURE);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

int	create_map(t_data *data, char **file, int i)
{
	int copy;

	copy = i;
	if (get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	if (last_check(&data->mapinfo, copy) == FAILURE)
		return (FAILURE);
	change_space_into_wall(data);
	return (SUCCESS);
}