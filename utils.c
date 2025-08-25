/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 13:50:07 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 13:09:57 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	cleanup_images(t_game *g)
{
	if (g->img_player)
		mlx_delete_image(g->mlx, g->img_player);
	if (g->img_floor)
		mlx_delete_image(g->mlx, g->img_floor);
	if (g->img_wall)
		mlx_delete_image(g->mlx, g->img_wall);
	if (g->img_exit)
		mlx_delete_image(g->mlx, g->img_exit);
	if (g->img_exit_open)
		mlx_delete_image(g->mlx, g->img_exit_open);
	if (g->img_collect)
		mlx_delete_image(g->mlx, g->img_collect);
}

static void	cleanup_textures(t_game *g)
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
}

void	cleanup_game(t_game *g)
{
	if (!g)
		return ;
	cleanup_images(g);
	cleanup_textures(g);
	if (g->map)
		free_map(g->map);
	if (g->mlx)
		mlx_terminate(g->mlx);
}

void	error_exit(const char *message, t_game *g)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd((char *)message, 2);
	ft_putstr_fd("\n", 2);
	if (g)
		cleanup_game(g);
	exit(1);
}
