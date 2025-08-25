/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:39 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 13:19:42 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	*process_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

static char	**resize_map(char **map, int *capacity, int rows)
{
	char	**new_map;
	int		i;

	*capacity *= 2;
	new_map = malloc(sizeof(char *) * *capacity);
	if (!new_map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free_map(map);
		return (NULL);
	}
	i = 0;
	while (i < rows)
	{
		new_map[i] = map[i];
		i++;
	}
	free(map);
	return (new_map);
}

static char	**process_single_line(char **map, char *line, int *rows,
	int *capacity)
{
	if (*rows >= *capacity)
	{
		map = resize_map(map, capacity, *rows);
		if (!map)
		{
			free(line);
			return (NULL);
		}
	}
	map[*rows] = ft_strdup(line);
	if (!map[*rows])
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		free(line);
		free_map(map);
		return (NULL);
	}
	(*rows)++;
	return (map);
}

char	**read_map_lines(int fd, int *rows)
{
	char	**map;
	char	*line;
	int		capacity;

	*rows = 0;
	capacity = 10;
	map = malloc(sizeof(char *) * capacity);
	if (!map)
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (NULL);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = process_line(line);
		map = process_single_line(map, line, rows, &capacity);
		if (!map)
			return (NULL);
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

void	init_validation_data(int *counts, t_map_info *info)
{
	counts[0] = 0;
	counts[1] = 0;
	counts[2] = 0;
	info->player_x = -1;
	info->player_y = -1;
}
