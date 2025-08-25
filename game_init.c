/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:50:00 by sadegh            #+#    #+#             */
/*   Updated: 2025/08/25 13:00:07 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_exit_position(t_game *g)
{
	int	y;
	int	x;
	int	found;

	y = 0;
	found = 0;
	while (y < g->rows && !found)
	{
		x = 0;
		while (x < g->cols && !found)
		{
			if (g->map[y][x] == 'E')
			{
				g->exit_x = x;
				g->exit_y = y;
				found = 1;
			}
			x++;
		}
		y++;
	}
}

static void	init_basic_vars(t_game *g, t_map_info *info)
{
	g->rows = 0;
	while (g->map[g->rows])
		g->rows++;
	g->cols = ft_strlen(g->map[0]);
	g->collected = 0;
	g->total_collectibles = info->collectible_count;
	g->moves = 0;
	g->player_x = info->player_x;
	g->player_y = info->player_y;
	g->player_on_exit = 0;
	if (g->map[g->player_y][g->player_x] == 'P')
		g->map[g->player_y][g->player_x] = '0';
}

static void	init_game_variables(t_game *g, t_map_info *info)
{
	init_basic_vars(g, info);
	find_exit_position(g);
}

int	init_game(t_game *g, t_map_info *info)
{
	init_game_variables(g, info);
	g->mlx = mlx_init(g->cols * TILE_SIZE, g->rows * TILE_SIZE,
			"so_long", true);
	if (!g->mlx)
		error_exit("Failed to initialize MLX", g);
	if (!load_game_images(g))
		error_exit("Failed to load images", g);
	return (1);
}
