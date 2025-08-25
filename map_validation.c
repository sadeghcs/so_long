/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snasiri <snasiri@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:39 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/22 18:00:00 by snasiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	is_map_empty(char **map)
{
	int	i;
	int	j;

	if (!map)
		return (1);
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] && (map[i][j] == ' ' || map[i][j] == '\t'
				|| map[i][j] == '\n'))
			j++;
		if (map[i][j] != '\0')
			return (0);
		i++;
	}
	return (1);
}

static int	check_map_dimensions(char **map, int rows, int *width)
{
	int	i;
	int	len;

	if (rows <= 0)
	{
		ft_putstr_fd("Error\nMap is empty or invalid\n", 2);
		return (0);
	}
	*width = -1;
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		if (*width == -1)
			*width = len;
		else if (len != *width)
		{
			ft_putstr_fd("Error\nMap is not rectangular\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	check_window_size_ok(int rows, int cols)
{
	int	w;
	int	h;

	w = cols * TILE_SIZE;
	h = rows * TILE_SIZE;
	if (w > MAX_SCREEN_WIDTH || h > MAX_SCREEN_HEIGHT)
	{
		ft_putstr_fd("Error\nMap size exceeds screen dimensions\n", 2);
		return (0);
	}
	return (1);
}

int	validate_map(char **map, t_map_info *info)
{
	int	rows;
	int	width;

	if (is_map_empty(map))
	{
		ft_putstr_fd("Error\nMap is empty\n", 2);
		return (0);
	}
	rows = 0;
	while (map[rows])
		rows++;
	if (!check_map_dimensions(map, rows, &width))
		return (0);
	if (!check_window_size_ok(rows, width))
		return (0);
	if (!validate_map_characters(map, rows, width, info))
		return (0);
	if (!check_map_solvable(map, info))
	{
		ft_putstr_fd("Error\nNo valid path to collect and reach exit\n", 2);
		return (0);
	}
	return (1);
}
