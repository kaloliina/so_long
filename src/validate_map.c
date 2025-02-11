/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:00:59 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/10 19:04:48 by khiidenh         ###   ########.fr       */
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

void	free_floodmap(char **tab)
{
	int	y;

	y = 0;
	if (tab != NULL)
	{
		while (tab[y] != NULL)
		{
			free (tab[y]);
			y++;
		}
		free (tab);
	}
}

void	flood_fill(t_game *game, t_map_validation *validation)
{
	int		y;
	char	**tab;

	y = 0;
	tab = malloc(sizeof(char *) * (game->height + 1));
	if (tab == NULL)
		cleanup_and_exit(game, ERRGEN, 0);
	while (y < (int)game->height)
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

void	validation_check(t_game *game, t_map_validation *validation)
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
	if (validation->collectable_count != validation->collectable_reached)
		cleanup_and_exit(game, ERRCUNR, 0);
	if (validation->exit_count != validation->exit_reached)
		cleanup_and_exit(game, ERREUNR, 0);
}
//this one could be made slightly clearer
void	update_validation(t_game *game, t_map_validation *validation)
{
	if (game->map[game->height][game->width] == 'C')
		validation->collectable_count++;
	if (game->map[game->height][game->width] == 'E')
		validation->exit_count++;
	if (game->map[game->height][game->width] == 'P')
		validation->player_count++;
	if ((game->map[0][game->width] != '1') || (game->map[game->height + 1] == NULL && game->map[game->height][game->width] != '1'))
		validation->is_enclosed = false;
	if (game->height != 0 && (ft_strlen(game->map[game->height]) != (ft_strlen(game->map[game->height - 1]))))
		validation->is_rectangular = false;
	if (game->map[game->height][0] != '1' || (game->map[game->height][game->width + 1] == '\0' && game->map[game->height][game->width] != '1'))
		validation->is_enclosed = false;
}
//remember to remove the debug text from this one.
void	initialize_and_validate(t_game *game)
{
	t_map_validation	validation;

	validation = (t_map_validation){true, true, 0, 0, 0, 0, 0};
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
	printf("Collectable count: %d\n", game->collectables);
	printf("Map size: Y: %zu X: %zu\n", game->height, game->width);
	printf("NEW PATH: Player pos: Y: %zu X: %zu\n", game->player.y, game->player.x);
	flood_fill(game, &validation);
	validation_check(game, &validation);
}

void	parse_map(t_game *game, char *str)
{
	int		len;
	int		fd;
	int		bytes_read;
	char	buffer[1000];

	len = ft_strlen(str) - 1;
	if (len < 4 || str[len] != 'r' || str[len - 1] != 'e'
		|| str[len - 2] != 'b' || str[len - 3] != '.')
		cleanup_and_exit(game, ERRBER, 0);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		cleanup_and_exit(game, ERRFILE, 0);
	bytes_read = read(fd, buffer, 1000);
	if (bytes_read == -1)
	{
		close (fd);
		cleanup_and_exit(game, ERRFILE, 0);
	}
	buffer[bytes_read] = '\0';
	if (close (fd) == -1)
		cleanup_and_exit(game, ERRFILE, 0);
	game->map = ft_split(buffer, '\n');
	if (game->map == NULL || game->map[0] == NULL)
		cleanup_and_exit(game, ERREMPTY, 0);
}
