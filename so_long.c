/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:54:48 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 12:33:02 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_extension(char *filename)
{
	char	*ext;

	ext = ft_strrchr(filename, '.');
	if (!ext || ft_strncmp(ext, ".ber", 4) != 0)
	{
		ft_putstr_fd("Error\nMap file must have .ber extension\n", 2);
		return (0);
	}
	return (1);
}

static int	init_and_validate(t_game *g, t_map_info *info, char *filename)
{
	g->map = load_map(filename);
	if (!g->map)
		return (0);
	if (!validate_map(g->map, info))
	{
		free_map(g->map);
		return (0);
	}
	if (!init_game(g, info))
	{
		free_map(g->map);
		return (0);
	}
	return (1);
}

static void	on_close(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	cleanup_game(g);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_map_info	info;
	t_game		g;

	ft_bzero(&g, sizeof(g));
	if (argc != 2)
	{
		ft_putstr_fd("Error\nUsage: ", 2);
		ft_putstr_fd(argv[0], 2);
		ft_putstr_fd(" <map_file.ber>\n", 2);
		return (1);
	}
	if (!check_extension(argv[1]))
		return (1);
	if (!init_and_validate(&g, &info, argv[1]))
		return (1);
	draw_map(&g);
	mlx_key_hook(g.mlx, handle_key, &g);
	mlx_close_hook(g.mlx, on_close, &g);
	mlx_loop(g.mlx);
	cleanup_game(&g);
	return (0);
}
