/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snasiri <snasiri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:39 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/22 15:14:58 by snasiri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

char	**load_map(const char *filename)
{
	int		fd;
	char	**map;
	int		rows;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nCould not open map file\n", 2);
		return (NULL);
	}
	map = read_map_lines(fd, &rows);
	close(fd);
	if (map)
		map[rows] = NULL;
	return (map);
}
