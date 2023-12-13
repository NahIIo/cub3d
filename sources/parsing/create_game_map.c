/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_game_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:23:30 by jchauvet          #+#    #+#             */
/*   Updated: 2023/12/11 14:31:26 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_map_lines(t_data *data, char **file, int i)
{
	int	index_value;

	index_value = i;
	while (file[i])
	{
		if (file[i][0] && file[i][0] == '\n')
		{
			i++;
			if (!file[i])
				break ;
		}
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
		j = -1;
		map_tab[i] = malloc(sizeof(char) * (mapinfo->width + 1));
		if (!map_tab[i])
			return (err_msg(NULL, ERR_MALLOC, FAILURE));
		while (mapinfo->file[index][++j] && mapinfo->file[index][j] != '\n')
			map_tab[i][j] = mapinfo->file[index][j];
		while (j < mapinfo->width)
		{
			map_tab[i][j] = '1';
			j++;
		}
		map_tab[i][j] = '\0';
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
		while (data->map[i][j])
		{
			if (is_a_white_space(data->map[i][j]) == SUCCESS
				&& j != data->map[i][ft_strlen(data->map[i]) - 1])
				data->map[i][j] = '1';
			j++;
		}
		i++;
	}
}

int	create_map(t_data *data, char **file, int i)
{
	int	copy;

	copy = i;
	if (get_map_info(data, file, i) == FAILURE)
		return (FAILURE);
	if (last_check(&data->mapinfo, copy) == FAILURE)
		return (FAILURE);
	change_space_into_wall(data);
	return (SUCCESS);
}
