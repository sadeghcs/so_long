/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:17:36 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 12:59:03 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// moved to movement.c

// moved to interactions.c

// moved to interactions.c

// moved to movement.c

static void	update_display(t_game *g)
{
	mlx_delete_image(g->mlx, g->img_player);
	g->img_player = mlx_texture_to_image(g->mlx, g->texture_player);
	if (!g->img_player)
	{
		ft_putstr_fd("Error recreating player image\n", 2);
		return ;
	}
	if (mlx_image_to_window(g->mlx, g->img_player,
			g->player_x * TILE_SIZE, g->player_y * TILE_SIZE) < 0)
	{
		ft_putstr_fd("Error placing player image\n", 2);
		return ;
	}
}

void	handle_key(mlx_key_data_t keydata, void *param)
{
	t_game	*g;
	int		nx;
	int		ny;

	g = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(g->mlx);
		free_map(g->map);
		exit(0);
	}
	nx = g->player_x;
	ny = g->player_y;
	if (!handle_movement_keys(keydata, &nx, &ny))
		return ;
	if (g->map[ny][nx] == '1')
		return ;
	handle_collectible(g, nx, ny);
	handle_exit(g, nx, ny);
	update_player_position(g, nx, ny);
	update_display(g);
}
