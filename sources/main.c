/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchauvet <jchauvet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 10:24:24 by jchauvet          #+#    #+#             */
/*   Updated: 2023/11/28 10:07:56 by jchauvet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	print_controls(void)
{
	printf("\n");
	printf("\e[91m╔═══════════════════════════════════");
	printf("═══════════════════════════════════╗\n");
	if (BONUS)
	{
		printf("║\e[0m                                 BONUS            ");
		printf("                    \e[91m║\n");
	}
	else
	{
		printf("║\e[0m                               NO BONUS            ");
		printf("                   \e[91m║\n");
	}
	printf("║                           W\e[0m: Move Forward            ");
	printf("                \e[91m║\n");
	printf("║     A\e[0m: Move Left          \e[91mS\e[0m: ");
	printf("Move Backward         \e[91mD\e[0m: Move Right     \e[91m║\n");
	printf("║     <\e[0m: Turn Left             \e[91mEsc\e[0m: Quit    ");
	printf("         \e[91m>\e[0m: Turn Right     \e[91m║\n");
	printf("╚════════════════════════════════════════");
	printf("══════════════════════════════╝\e[0m\n");
}

static int	parse_args(t_data *data, char **av)
{
	if (check_file(av[1], true) == FAILURE)
		clean_exit(data, FAILURE);
	parse_data(av[1], data);
	if (get_file_data(data, data->mapinfo.file) == FAILURE)
		return (free_data(data));
	if (check_map_validity(data, data->map) == FAILURE)
		return (free_data(data));
	if (check_textures_validity(data, &data->texinfo) == FAILURE)
		return (free_data(data));
	init_player_direction(data);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (err_msg("Usage", ERR_USAGE, 1));
	init_data(&data);
	if (parse_args(&data, av) != 0)
		return (1);
	init_mlx(&data);
	init_textures(&data);
	print_controls();
	render_raycast(&data);
	listen_for_input(&data);
	mlx_loop_hook(data.mlx, render, &data);
	mlx_loop(data.mlx);
	return (0);
}
