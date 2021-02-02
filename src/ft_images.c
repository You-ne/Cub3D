/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_images.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotillar <yotillar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 07:51:11 by yotillar          #+#    #+#             */
/*   Updated: 2021/02/01 23:33:58 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Cub3D.h"

void	ft_pixel_put(t_img *img, int x, int y, int color)

{
	char	red;
	char	green;
	char	blue;

	red = (char)(color & 255);
	green = (char)((color >> 8) & 255);
	blue = (char)((color >> 16) & 255);

/*	printf("Line Size = %d\n", img->s_line);
	printf("Tryng to put a pixel in x = %d, y = %d, with color %d, Index = %d\n", x, y, color, (x*4)+(y*(img->s_line)*4));*/

/*	red = 215;
	blue = 15;
	green = 100;*/

	char	*dst;                                                               /*pad compris l'utilite */

	dst = (char *)img->img + ((y * img->s_line) + (x * 4));
	*(int*)dst = color;
//	*(dst) = red;
//	*(dst + 1) = green;
//	*(dst + 2) = blue;


//	if (img->img != NULL)
//	{
//		img->img[((x * 4) + (y * img->s_line))] = (int)red;
//		img->img[((x * 4 + 1) + (y * img->s_line))] = (int)green;
//		img->img[((x * 4 + 2) + (y * img->s_line))] = (int)blue;
//	}
}

double find_size_sp(char chr)
{
	if (chr == '2')
		return (SP2_SIZE);
	if (chr == '3')
		return (SP3_SIZE);
	if (chr == '4')
		return (SP4_SIZE);
	if (chr == '5')
		return (SP5_SIZE);
}

t_img find_sprite(t_game game, char chr)
{
	t_img *tex;

	tex = &game.SP;
	while (tex->chr != chr)
	{
	//printf("\nnext=%p;tex.chr='%c';chr=%c\n", tex->next, tex->chr, chr);
//		if (tex.next == NULL)
//			return (NULL);
		tex = tex->next;
	}
	return (*tex);
}

void	ft_texture_put(t_img *img, int x, int y, char *texture)
{
	//printf("%d ; ", (int)*(texture + 3));
	if (LINUX != 1 || (LINUX == 1 && (*texture != 0 || *(texture + 1) != 0 ||
	*(texture + 2) != 0)))
	{
		img->img[((x * (img->bpp / 8)) + (y * img->s_line))] = *texture;
		img->img[((x * (img->bpp / 8) + 1) + (y * img->s_line))] = *(texture + 1);
		img->img[((x * (img->bpp / 8) + 2) + (y * img->s_line))] = *(texture + 2);
		img->img[((x * (img->bpp / 8) + 3) + (y * img->s_line))] = *(texture + 3);
	}
}

void	ft_drawcol_sp(t_coor *heightncol, t_game game, t_img *img, int x)
{
	int y;
	int count;
	int i;
	t_img tex;
	double size;

	y = 0;
	count = 0;
	size = find_size_sp(((int)heightncol->dist) + '0');
	//printf("\n\n!!!%c;%f!!!\n\n", ((int)heightncol->dist) + '0', heightncol->dist);
	tex = find_sprite(game, ((int)heightncol->dist) + '0');
	if (heightncol->y > game.res[1])
	{
		count = (heightncol->y - game.res[1]) * size;
		heightncol->y = (int)round(game.res[1] * size);
	}
	while((double)y <= ((game.res[1] / 2) + ((heightncol->y * (1 / size)) / 2)))
	{
		//printf("%i;\n\n", (int)(round(((tex.height * count) / heightncol.y))));
		if (y >= ((game.res[1] / 2) + ((heightncol->y * (1 / size)) / 2)) - heightncol->y)
		{
			i = (int)round(((double)tex.height / heightncol->y) * (double)count);
			i = i * tex.s_line;
			i = i + ((int)(round(heightncol->x)) * (tex.bpp / 8));
			ft_texture_put(img, x, y, &tex.img[i]);
			count++;
		}
		y++;
	}
	//printf("!!next=%p; heightncol.dist=%f\n", heightncol->next, heightncol->dist);
	if (heightncol->next != 0x0)
	{
		//printf("SPRIIITE!!\n");
		ft_drawcol_sp(heightncol->next, game, img, x);
	}
	free(heightncol);  //// NE FONCTIONNE PAS, GROSSE FUITE DE MEMOIRE !!!
}


void	ft_drawcol(t_coor *heightncol, t_img tex, t_game game, t_img *img)
{
	int y;
	int count;
	int i;

	y = 0;
	count = 0;
	//printf("\n\n!!!!!!\n\n", (int)(round(heightncol.dist)));
	if (heightncol->y > game.res[1])
	{
		count = (heightncol->y - game.res[1]) / 2;
		heightncol->y = game.res[1];
	}
	while(y < (game.res[1] / 2 + (heightncol->y / 2)))
	{
		if(y > (game.res[1] / 2 - (heightncol->y / 2)))
		{
			//printf("%i;\n\n", (int)(round(((tex.height * count) / heightncol.y))));
			i = (int)(((double)tex.height / heightncol->y) * (double)count);
			i = i * tex.s_line;
			i = i + ((int)(round(heightncol->x)) * (tex.bpp / 8));
			//printf(" %i + %i |", ((int)(round(heightncol.dist))), (int)(round(((tex.height * count) / heightncol.y))));
			ft_texture_put(img, heightncol->dist, y, &tex.img[i]);
			count++;
		}
		else
			ft_pixel_put(img, heightncol->dist, y, game.Ce);
		y++;
	}
	while(y < game.res[1])
	{
		ft_pixel_put(img, heightncol->dist, y++, game.Fl);
		//y++;
	}
	//printf("\n\n\nnext=%p; heightncol.dist=%f\n", heightncol.next, heightncol.dist);
	if (heightncol->next != 0x0)
	{
		//printf("SPRIIITE!!\n");
		ft_drawcol_sp(heightncol->next, game, img, heightncol->dist);
	}
}

