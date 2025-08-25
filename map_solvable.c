/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_solvable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snasiri <snasiri@student.42.fr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:39 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/22 18:20:00 by snasiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, t_validation_data *data)
{
	t_validation_data	next;

	if (data->j < 0 || data->i < 0 || data->i >= data->rows
		|| data->j >= data->width)
		return ;
	if (map[data->i][data->j] == '1' || map[data->i][data->j] == 'V')
		return ;
	map[data->i][data->j] = 'V';
	next = *data;
	next.j = data->j + 1;
	flood_fill(map, &next);
	next.j = data->j - 1;
	flood_fill(map, &next);
	next.j = data->j;
	next.i = data->i + 1;
	flood_fill(map, &next);
	next.i = data->i - 1;
	flood_fill(map, &next);
}

static char	**copy_map(char **map, int rows)
{
	char	**copy;
	int		i;

	copy = malloc((rows + 1) * sizeof(char *));
	if (!copy)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			ft_putstr_fd("Error\nMemory allocation failed\n", 2);
			free_map(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static int	count_remaining_items(char **copy, int rows)
{
	int	i;
	int	j;
	int	c_left;
	int	e_left;

	c_left = 0;
	e_left = 0;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (copy[i][j])
		{
			if (copy[i][j] == 'C')
				c_left++;
			else if (copy[i][j] == 'E')
				e_left++;
			j++;
		}
		free(copy[i]);
		i++;
	}
	free(copy);
	return (c_left == 0 && e_left == 0);
}

int	check_map_solvable(char **map, t_map_info *info)
{
	char				**copy;
	int					rows;
	t_validation_data	data;

	rows = 0;
	while (map[rows])
		rows++;
	if (info->player_x < 0 || info->player_y < 0)
		return (0);
	copy = copy_map(map, rows);
	if (!copy)
		return (0);
	data.i = info->player_y;
	data.j = info->player_x;
	data.rows = rows;
	data.width = ft_strlen(map[0]);
	flood_fill(copy, &data);
	return (count_remaining_items(copy, rows));
}
