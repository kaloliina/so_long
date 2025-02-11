/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_and_exits.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khiidenh <khiidenh@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 16:03:18 by khiidenh          #+#    #+#             */
/*   Updated: 2025/02/10 11:46:31 by khiidenh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
//this printf text prints anyways if you exit, remove
void	cleanup_and_exit(t_game *game, char *str, bool success)
{
	int	y;

	y = 0;
	if (game->map != NULL)
	{
		while (game->map[y] != NULL)
		{
			free (game->map[y]);
			y++;
		}
		free (game->map);
	}
	if (game->mlx != NULL)
		mlx_terminate(game->mlx);
	if (success == true)
	{
		printf("Wohoo! You did it!\n");
		exit (0);
	}
	if (success == false)
	{
		ft_putstr_fd(str, 2);
		exit (1);
	}
}
