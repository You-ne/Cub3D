/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 01:52:24 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/28 17:18:15 by yotillar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

int		verify_char(t_game *game, int y, int x, char *sp_set)
{
	if (in_str(game->map[y][x], sp_set) && (!game->map[y + 1] ||
	!game->map[y][x + 1]))
		return (0);
	if (in_str(game->map[y][x], sp_set) && (game->map[y][x + 1] == ' ' ||
	game->map[y][x - 1] == ' ' || game->map[y + 1][x] == ' ' ||
	game->map[y - 1][x] == ' '))
		return (0);
	return (1);
}

void	verify_map(t_game *game, char *sp_set)
{
	int		i;
	int		j;

	i = 0;
	while (game->map[i] != NULL)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (!verify_char(game, i, j, sp_set))
				ft_error("Erreur: Map ouverte !\n", game);
			j++;
		}
		i++;
	}
}

void	find_secret_door(t_game *game)
{
	int		x;
	int		y;

	y = 0;
	while (game->map[y] != NULL)
	{
		x = 0;
		while (game->map[y][x] != 0)
		{
			if (game->map[y][x] == '*')
			{
				game->secret.x = x;
				game->secret.y = y;
				game->secret.dist = 1;
				return ;
			}
			x++;
		}
		y++;
	}
}

char	*count_sprites(t_game *game, int time, char *sp_set)
{
	int		i;
	char	*tmp;
	t_img	*sp;

	if (time == 0)
		sp = game->SP;
	else
		sp = game->SA;
	while (sp != NULL)
	{
		if (!(in_str(sp->chr, sp_set)))
		{
			tmp = ft_ctostr(1, sp->chr);
			sp_set = ft_strmcat(sp_set, tmp);
			free(tmp);
		}
		sp = sp->next;
	}
	return (sp_set);
}