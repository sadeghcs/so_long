/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadegh <sadegh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 11:57:23 by snasiri           #+#    #+#             */
/*   Updated: 2025/08/25 13:32:30 by sadegh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include "get_next_line/get_next_line.h"

# define TILE_SIZE 64
# define MAX_SCREEN_WIDTH 1920
# define MAX_SCREEN_HEIGHT 1080

// ====== Structs ======
typedef struct s_map_info
{
	int	player_x;
	int	player_y;
	int	collectible_count;
	int	exit_count;
}	t_map_info;

typedef struct s_game
{
	mlx_t			*mlx;
	char			**map;
	mlx_texture_t	*texture_wall;
	mlx_texture_t	*texture_floor;
	mlx_texture_t	*texture_player;
	mlx_texture_t	*texture_exit;
	mlx_texture_t	*texture_exit_open;
	mlx_texture_t	*texture_collect;
	mlx_image_t		*img_wall;
	mlx_image_t		*img_floor;
	mlx_image_t		*img_player;
	mlx_image_t		*img_exit;
	mlx_image_t		*img_exit_open;
	mlx_image_t		*img_collect;
	int				collected;
	int				total_collectibles;
	int				moves;
	int				rows;
	int				cols;
	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;
	int				player_on_exit;
}	t_game;

typedef struct s_validation_data
{
	int	i;
	int	j;
	int	rows;
	int	width;
}	t_validation_data;

// ====== Map Functions ======
char	**load_map(const char *filename);
int		validate_map(char **map, t_map_info *info);
void	free_map(char **map);

// ====== Map Utils Functions ======
char	**read_map_lines(int fd, int *rows);
int		check_map_solvable(char **map, t_map_info *info);
void	init_validation_data(int *counts, t_map_info *info);
//int		check_remaining_items(char **copy, int rows);

// ====== Map Dimensions Functions ======
//int		check_map_dimensions(char **map, int rows, int *width);

// ====== Map Characters Functions ======
int		validate_map_characters(char **map, int rows, int width,
			t_map_info *info);

// ====== Game Functions ======
int		init_game(t_game *g, t_map_info *info);
int		close_window(t_game *g);

// ====== Game Utils Functions ======
void	put_img_instanced(t_game *g, mlx_image_t *img, int x, int y);
void	draw_map(t_game *g);
void	handle_key(mlx_key_data_t keydata, void *param);
int		load_game_images(t_game *g);
int		handle_movement_keys(mlx_key_data_t keydata, int *nx, int *ny);
void	update_player_position(t_game *g, int nx, int ny);
void	handle_collectible(t_game *g, int nx, int ny);
void	handle_exit(t_game *g, int nx, int ny);

// ====== Utility Functions ======
void	error_exit(const char *message, t_game *g);
void	cleanup_game(t_game *g);

#endif
