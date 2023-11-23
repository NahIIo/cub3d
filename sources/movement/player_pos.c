/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_pos.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:22:43 by jchauvet          #+#    #+#             */
/*   Updated: 2023/11/23 12:38:43 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_pos_in_map(t_data *data, double x, double y)
{
	if (x < 0 || x >= data->mapinfo.width - 1)
		return (false);
	if (y < 0 || y >= data->mapinfo.height)
		return (false);
	return (true);
}
/*
static bool is_colliding_with_wall(t_data *data, double x, double y)
{
	if (data->map[(int)y][(int)x] == '0')
		return (false);
	return (true);
}
*/

static bool	is_valid_pos(t_data *data, double x, double y)
{
	if (is_valid_pos_in_map(data, x, y))
		return (true);
	return (false);
}

int	validate_move(t_data *data, double new_x, double new_y)
{
	int	moved;

	moved = 0;
	if (is_valid_pos(data, new_x, data->player.pos_y))
	{
		data->player.pos_x = new_x;
		moved = 1;
	}
	if (is_valid_pos(data, data->player.pos_x, new_y))
	{
		data->player.pos_y = new_y;
		moved = 1;
	}
	return (moved);
}
