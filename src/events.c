/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 18:38:04 by amanchon          #+#    #+#             */
/*   Updated: 2021/02/27 03:44:32 by antoine          ###   ########.fr       */
//Colors
#/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	change_enemy_pv(t_game *game, t_enemy *enemy, int pv)
{
	if (enemy->pv > 1)
	{
		enemy->pv = enemy->pv + pv;
		if (enemy->pv < 1)
		{
			enemy->tdeath = clock();
			change_map(game, enemy->x, enemy->y, find_death_chr(enemy->chr));
				if (enemy->chr == 'H')
					game->victory = clock();
		}
	}
}

void	weapon_fire(t_game *game, t_coor *tir)
{
	t_coor	*tir2;
	t_enemy	*enemy;

	tir2 = tir;
	if (tir->next != NULL)
	{
		while (tir->next->next != NULL)
				tir = tir->next;
		if ((int)game->res[1] / 2 > (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist)) / 2))) ||
		game->res[1] / 2 < (game->tilt + (int)(game->res[1] / 2)) +
		((tir->next->y * (1 / sp_size((char)((int)tir->next->dist))) / 2)) -
		tir->next->y || is_alive_or_dead((char)((int)tir->next->dist) == -1))
		{
			free_ray(tir->next);
			tir->next = NULL;
			weapon_fire(game, tir2);
			return ;
		}
		if (is_alive_or_dead((char)((int)tir->next->dist)) != 1)
			return ;
		enemy = find_enemy(game, tir->next->coor_sp / 1000,
		tir->next->coor_sp % 1000, (char)((int)tir->next->dist));
		change_enemy_pv(game, enemy, game->player.damage);
	}
}


void	teleportation(t_player *player, float x, float y)
{
	player->pos.x = x;
	player->pos.y = y;
}

void	change_map(t_game *game, int x, int y, char chr)
{
	game->map[y][x] = chr;
}

void	change_pv(t_player *player, float pv)
{
	player->pv = player->pv + pv;
	printf("PV = %f, DMG = %f\n\n", player->pv, pv);
	if (player->pv > 100)
		player->pv = 100;
}

