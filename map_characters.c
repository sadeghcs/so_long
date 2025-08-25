/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_characters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 18:15:00 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 13:31:31 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check_wall_boundary(t_validation_data *data, char c)
{
	if ((data->i == 0 || data->i == data->rows - 1 || data->j == 0
			|| data->j == data->width - 1) && c != '1')
	{
		ft_putstr_fd("Error\nMap is not surrounded by walls\n", 2);
		return (0);
	}
	return (1);
}

static int	process_map_character(char c, int *counts,
		t_map_info *info, t_validation_data *data)
{
	if (c == 'P')
	{
		counts[0]++;
		info->player_x = data->j;
		info->player_y = data->i;
	}
	else if (c == 'C')
		counts[1]++;
	else if (c == 'E')
		counts[2]++;
	else if (c != '0' && c != '1')
	{
		ft_putstr_fd("Error\nInvalid character in map\n", 2);
		return (0);
	}
	return (1);
}

static int	validate_character_counts(int *counts)
{
	if (counts[0] != 1)
	{
		ft_putstr_fd("Error\nMap must contain exactly one player\n", 2);
		return (0);
	}
	if (counts[1] < 1)
	{
		ft_putstr_fd("Error\nMap must contain at least one collectible\n", 2);
		return (0);
	}
	if (counts[2] != 1)
	{
		ft_putstr_fd("Error\nMap must contain exactly one exit\n", 2);
		return (0);
	}
	return (1);
}

static int	scan_map_for_characters(char **map, t_validation_data *data,
	int *counts, t_map_info *info)
{
	int					i;
	int					j;

	i = 0;
	while (i < data->rows)
	{
		j = 0;
		while (j < data->width)
		{
			data->i = i;
			data->j = j;
			if (!check_wall_boundary(data, map[i][j]))
				return (0);
			if (!process_map_character(map[i][j], counts, info, data))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map_characters(char **map, int rows, int width, t_map_info *info)
{
	int					counts[3];
	t_validation_data	data;

	init_validation_data(counts, info);
	data.rows = rows;
	data.width = width;
	if (!scan_map_for_characters(map, &data, counts, info))
		return (0);
	if (!validate_character_counts(counts))
		return (0);
	info->collectible_count = counts[1];
	info->exit_count = counts[2];
	return (1);
}
