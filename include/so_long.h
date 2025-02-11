/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 12:48:44 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/11 17:18:50 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/includes/libft.h"
# include "../include/get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
//# define WIDTH 256
//# define HEIGHT 256
# define TILE 100
# define ERRFILE "Warning: Map file does not exist!"
# define ERREMPTY "Warning: Map file is empty!"
# define ERRNAME "Warning: Map file has a wrong naming convention!"
# define ERRC "Warning: No collectables found on the map!"
# define ERRE "Warning: Invalid amount of exits on the map!"
# define ERRP "Warning: Invalid amount of players on the map!"
# define ERRREC "Warning: Map is not rectangular!"
# define ERRENC "Warning: Map is not enclosed with walls!"
# define ERRCUNR "Warning: Player cannot reach all collectables!"
# define ERREUNR "Warning: Player cannot reach the exit!"
# define ERRGEN "Warning: Operation failed."
# define ERRBER "Warning: File needs to end in .ber extension."

#define ASSET_COUNT 6

enum assets
{
 BASE,
 WALL,
 EXIT,
 PLAYER_LEFT,
 PLAYER_RIGHT,
 COLLECTABLE,
};

typedef	struct s_player
{
	size_t x;
	size_t y;
	int collected;
	int movements;
} t_player;

typedef struct s_game
{
	mlx_t	*mlx;
	int collectables;
	char	**map;
	size_t width;
	size_t height;
	t_player player;
	mlx_image_t *images[6];
} t_game;

typedef struct s_map_validation
{
	bool is_rectangular;
	bool is_enclosed;
	int collectable_count;
	int collectable_reached;
	int exit_count;
	int exit_reached;
	int player_count;
} t_map_validation;

void parse_map(t_game *game, char *str);

void initialize_and_validate(t_game *game);
void load_textures(t_game *game);
void key_hook(mlx_key_data_t keydata, t_game *game);
void cleanup_and_exit(t_game *game, char *str, bool success);
#endif
