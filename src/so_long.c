/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:02:12 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/11 15:36:41 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc == 2)
	{
		game = (t_game){0};
		parse_map(&game, argv[1]);
		initialize_and_validate(&game);
		game.mlx = mlx_init(game.width * TILE, game.height * TILE,
				"Hellou!", false);
		if (game.mlx == NULL)
			cleanup_and_exit(&game, ERRGEN, 0);
		load_textures(&game);
		mlx_key_hook(game.mlx, (void *) key_hook, &game);
		mlx_loop(game.mlx);
		cleanup_and_exit(&game, NULL, 1);
	}
	return (1);
}
