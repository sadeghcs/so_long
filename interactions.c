/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:52:00 by sadegh            #+#    #+#             */
/*   Updated: 2025/08/25 13:00:37 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(t_game *g, int nx, int ny)
{
	if (g->map[ny][nx] == 'C')
	{
		g->collected++;
		g->map[ny][nx] = '0';
		ft_putstr_fd("Collected: ", 1);
		ft_putnbr_fd(g->collected, 1);
		ft_putstr_fd("\n", 1);
		draw_map(g);
		if (g->collected == g->total_collectibles)
		{
			mlx_image_to_window(g->mlx, g->img_exit_open,
				g->exit_x * TILE_SIZE, g->exit_y * TILE_SIZE);
		}
	}
}

void	handle_exit(t_game *g, int nx, int ny)
{
	if (g->map[ny][nx] == 'E')
	{
		if (g->collected == g->total_collectibles)
		{
			ft_putstr_fd("You won!\n", 1);
			mlx_terminate(g->mlx);
			free_map(g->map);
			exit(0);
		}
	}
}
