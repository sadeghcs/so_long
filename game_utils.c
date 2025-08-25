/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:17:36 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 13:09:57 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	draw_floor_layer(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			put_img_instanced(g, g->img_floor, x, y);
			x++;
		}
		y++;
	}
}

static void	draw_exit(t_game *g, int x, int y)
{
	if (g->collected == g->total_collectibles)
		put_img_instanced(g, g->img_exit_open, x, y);
	else
		put_img_instanced(g, g->img_exit, x, y);
}

static void	draw_static_layer(t_game *g)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < g->rows)
	{
		x = 0;
		while (x < g->cols)
		{
			c = g->map[y][x];
			if (c == '1')
				put_img_instanced(g, g->img_wall, x, y);
			else if (c == 'C')
				put_img_instanced(g, g->img_collect, x, y);
			else if (c == 'E')
				draw_exit(g, x, y);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *g)
{
	draw_floor_layer(g);
	draw_static_layer(g);
	put_img_instanced(g, g->img_player, g->player_x, g->player_y);
}
