/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 07:51:11 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/27 04:11:11 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)
{
	char	red;
	char	green;
	char	blue;
	char	*dst;

	red = (char)(color & 255);
	green = (char)((color >> 8) & 255);
	blue = (char)((color >> 16) & 255);
	dst = (char *)img->img + ((y * img->s_line) + (x * 4));
	*(int*)dst = color;
}


void	ft_texture_put_sp(t_img *img, t_coor xy, char *texture, int i)
{
	int x;
	int y;

	x = (int)xy.x;
	y = (int)xy.y;
	if (LINUX != 1 || (LINUX == 1 && (texture[i] == 0 && 
	texture[i + 1] == 0 && texture[i + 2] == 0 )))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = 0;
	}
	else if (LINUX != 1 || (LINUX == 1 && (texture[i] != texture[0] && 
	texture[i + 1] != texture[1] && texture[i + 2] != texture[0])))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = texture[i];
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = texture[i + 1];
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = texture[i + 2];
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = texture[i + 3];
	}
}

void	ft_texture_put(t_img *img, int x, int y, char *texture)
{
	//printf("%d ; ", (int)*(texture + 3));
	if (LINUX != 1 || (LINUX == 1 && *texture == 0 && 
	*(texture + 1) == 0 && *(texture + 2) == 0 ))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = 0;
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = 0;
	}
	else if (LINUX != 1 || (LINUX == 1 && (*(texture) != 0 && 
	*(texture + 1) != 255 && *(texture + 2) != 0)))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = *texture;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = *(texture + 1);
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = *(texture + 2);
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = *(texture + 3);
	}
//	printf("R=%i, V=%i, B=%i\n", *(texture), *(texture + 1), *(texture + 2));
}

void	end_screen(t_game *game, t_img *tex, t_img *img)
{
	int x;
	int y;
	int i;
	int count;
	float mid;
	int j;

	x = 0;
	while (x < game->res[0])
	{
		y = 0;
		j = ((int)(((float)tex->width / game->res[0])* (float)x));
		while (y < game->res[1])
		{
			i = (int)(((float)tex->height / game->res[1]) * (float)y);
			i = i * tex->s_line;
			i = i + (j * 4);
			ft_texture_put(img, x, y, &tex->img[i]);
			y++;
		}
		x++;
	}
}
