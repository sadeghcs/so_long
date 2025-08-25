/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 12:50:00 by sadegh            #+#    #+#             */
/*   Updated: 2025/08/25 12:59:57 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	load_textures(t_game *g)
{
	g->texture_floor = mlx_load_png("images/floor.png");
	g->texture_wall = mlx_load_png("images/wall.png");
	g->texture_player = mlx_load_png("images/player.png");
	g->texture_exit = mlx_load_png("images/exit.png");
	g->texture_exit_open = mlx_load_png("images/exit_open.png");
	g->texture_collect = mlx_load_png("images/collectible.png");
	if (!g->texture_floor || !g->texture_wall || !g->texture_player
		|| !g->texture_exit || !g->texture_exit_open || !g->texture_collect)
		error_exit("Failed to load PNG texture files", g);
}

static void	build_images(t_game *g)
{
	g->img_floor = mlx_texture_to_image(g->mlx, g->texture_floor);
	g->img_wall = mlx_texture_to_image(g->mlx, g->texture_wall);
	g->img_player = mlx_texture_to_image(g->mlx, g->texture_player);
	g->img_exit = mlx_texture_to_image(g->mlx, g->texture_exit);
	g->img_exit_open = mlx_texture_to_image(g->mlx, g->texture_exit_open);
	g->img_collect = mlx_texture_to_image(g->mlx, g->texture_collect);
	if (!g->img_floor || !g->img_wall || !g->img_player || !g->img_exit
		|| !g->img_exit_open || !g->img_collect)
		error_exit("Failed to create images from textures", g);
}

static void	free_non_player_textures(t_game *g)
{
	if (g->texture_floor)
		mlx_delete_texture(g->texture_floor);
	if (g->texture_wall)
		mlx_delete_texture(g->texture_wall);
	if (g->texture_exit)
		mlx_delete_texture(g->texture_exit);
	if (g->texture_exit_open)
		mlx_delete_texture(g->texture_exit_open);
	if (g->texture_collect)
		mlx_delete_texture(g->texture_collect);
	g->texture_floor = NULL;
	g->texture_wall = NULL;
	g->texture_exit = NULL;
	g->texture_exit_open = NULL;
	g->texture_collect = NULL;
}

int	load_game_images(t_game *g)
{
	load_textures(g);
	build_images(g);
	free_non_player_textures(g);
	return (1);
}

void	put_img_instanced(t_game *g, mlx_image_t *img, int x, int y)
{
	if (img)
		mlx_image_to_window(g->mlx, img, x * TILE_SIZE, y * TILE_SIZE);
}
