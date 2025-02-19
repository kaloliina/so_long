/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_validate.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:00:59 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/19 13:24:49 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static bool	fill(char **tab, int player_x, int player_y,
t_map_validation *validation)
{
	if (tab[player_y][player_x] == '1')
		return (false);
	if (tab[player_y][player_x] == 'C')
		validation->collectable_reached++;
	if (tab[player_y][player_x] == 'E')
		validation->exit_reached++;
	tab[player_y][player_x] = '1';
	fill(tab, player_x + 1, player_y, validation);
	fill(tab, player_x - 1, player_y, validation);
	fill(tab, player_x, player_y + 1, validation);
	fill(tab, player_x, player_y - 1, validation);
	return (true);
}

static void	flood_fill(t_game *game, t_map_validation *validation)
{
	int		y;
	char	**tab;

	y = 0;
	tab = malloc(sizeof(char *) * (game->height + 1));
	if (tab == NULL)
		cleanup_and_exit(game, ERRGEN, 0);
	while (y < game->height)
	{
		tab[y] = ft_strdup(game->map[y]);
		if (tab[y] == NULL)
		{
			free_floodmap(tab);
			cleanup_and_exit(game, ERRGEN, 0);
		}
		y++;
	}
	tab[y] = NULL;
	fill(tab, game->player.x, game->player.y, validation);
	free_floodmap(tab);
}

static void	validation_check(t_game *game, t_map_validation *validation
, int validation_complete)
{
	if (validation->collectable_count < 1)
		cleanup_and_exit(game, ERRC, 0);
	if (validation->exit_count != 1)
		cleanup_and_exit(game, ERRE, 0);
	if (validation->player_count != 1)
		cleanup_and_exit(game, ERRP, 0);
	if (validation->is_rectangular == false)
		cleanup_and_exit(game, ERRREC, 0);
	if (validation->is_enclosed == false)
		cleanup_and_exit(game, ERRENC, 0);
	if (validation->has_invalid_chars == true)
		cleanup_and_exit(game, ERRCHARS, 0);
	if (validation_complete == 0)
		return ;
	if (validation->collectable_count != validation->collectable_reached)
		cleanup_and_exit(game, ERRCUNR, 0);
	if (validation->exit_count != validation->exit_reached)
		cleanup_and_exit(game, ERREUNR, 0);
}

static void	update_validation(t_game *game, t_map_validation *validation)
{
	char	current;

	current = game->map[game->height][game->width];
	if (current == 'C')
		validation->collectable_count++;
	if (current == 'E')
		validation->exit_count++;
	if (current == 'P')
		validation->player_count++;
	if (current != '1' && current != '0' && current != 'C'
		&& current != 'E' && current != 'P')
		validation->has_invalid_chars = true;
	if (game->height != 0 && (ft_strlen(game->map[game->height])
			!= (ft_strlen(game->map[game->height - 1]))))
	{
		validation->is_rectangular = false;
		return ;
	}
	if ((game->map[0][game->width] != '1')
	|| (game->map[game->height + 1] == NULL && current != '1'))
		validation->is_enclosed = false;
	if (game->map[game->height][0] != '1'
	|| (game->map[game->height][game->width + 1] == '\0' && current != '1'))
		validation->is_enclosed = false;
}

void	initialize_and_validate(t_game *game)
{
	t_map_validation	validation;

	validation = (t_map_validation){true, true, false, 0, 0, 0, 0, 0};
	game->player = (t_player){0};
	while (game->map[game->height] != NULL)
	{
		game->width = 0;
		while (game->map[game->height][game->width] != '\0')
		{
			if (game->map[game->height][game->width] == 'C')
				game->collectables++;
			if (game->map[game->height][game->width] == 'P')
			{
				game->player.y = game->height;
				game->player.x = game->width;
			}
			update_validation(game, &validation);
			game->width++;
		}
		game->height++;
	}
	validation_check(game, &validation, 0);
	flood_fill(game, &validation);
	validation_check(game, &validation, 1);
}
