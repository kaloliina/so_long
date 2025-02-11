/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:46:14 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/11 17:16:49 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

//needs to have a correct exit, and get rid of the size_t
//also slightly too long but maybe i could use the map here or find another way
static void	place_images(t_game *game)
{
	int		asset_index;
	size_t	x;
	size_t	y;

	y = 0;
	while (game->height > y)
	{
		x = 0;
		while (game->width > x)
		{
			asset_index = -1;
			if (game->map[y][x] == '1')
				asset_index = 1;
			else if (game->map[y][x] == 'E')
				asset_index = 2;
			else if (game->map[y][x] == 'C')
				asset_index = 5;
			if (mlx_image_to_window(game->mlx, game->images[BASE],
					x * TILE, y * TILE) < 0
				|| (asset_index != -1 && mlx_image_to_window(game->mlx,
						game->images[asset_index], x * TILE, y * TILE) < 0))
				exit(1);
			x++;
		}
		y++;
	}
}

// const char *ASSET_PATHS[] = {
//     "assets/base.png",
//     "assets/wall.png",
//     "assets/exit.png",
//     "assets/player_left.png",
//     "assets/player_right.png",
// 	"assets/collectable.png",
// };

//not sure if you can have global variable here.. see if you can add that to load textures,
//also correct exit and not just exit(1)
//also remember to delete textureif something fails!
void	load_textures(t_game *game)
{
	int				i;
	mlx_texture_t	*texture;
	const char *ASSET_PATHS[] = {
		"assets/base.png",
		"assets/wall.png",
		"assets/exit.png",
		"assets/player_left.png",
		"assets/player_right.png",
		"assets/collectable.png",
	};

	i = 0;
	while (i < ASSET_COUNT)
	{
		if ((texture = mlx_load_png(ASSET_PATHS[i])) == NULL)
			exit(1);
		if ((game->images[i] = mlx_texture_to_image(game->mlx, texture))
			== NULL)
			exit(1);
		mlx_delete_texture(texture);
		if ((mlx_resize_image(game->images[i], TILE, TILE)) == false)
			exit(1);
		i++;
	}
	place_images(game);
	if (mlx_image_to_window(game->mlx, game->images[PLAYER_LEFT]
			, game->player.x * TILE, game->player.y * TILE) < 0
		|| mlx_image_to_window(game->mlx, game->images[PLAYER_RIGHT]
			, game->player.x * TILE, game->player.y * TILE) < 0)
		exit (1);
	game->images[PLAYER_LEFT]->instances[0].enabled = false;
}
