/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:58:43 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/05/14 19:58:46 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H
# include "libft/libft.h"
# include "SDL.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include <SDL.h>
# include <stdio.h>
# include <stdbool.h>
# include <SDL_image.h>
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# define mapWidth 24
# define mapHeight 24
# define WIDTH 1280
# define HEIGHT 800
# define texWidth 64
# define texHeight 64

// int         done = 1;
// int         colorRGB;

// double posX = 22, posY = 12;  //x and y start position
// double dirX = -1, dirY = 0; //initial direction vector
// double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

// double time = 0; //time of current frame
// double oldTime = 0; //time of previous frame
// double frameTime; //frameTime is the time this frame has taken, in seconds
// double moveSpeed;
// double rotSpeed;

// double cameraX;
// double rayDirX;
// double rayDirY;

// int mapX;
// int mapY;
// //length of ray from current position to next x or y-side
// double sideDistX;
// double sideDistY;
// //length of ray from one x or y-side to next x or y-side
// double deltaDistX;
// double deltaDistY;
// double perpWallDist;

// //what direction to step in x or y-direction (either +1 or -1)
// int stepX;
// int stepY;

// int hit; //was there a wall hit?
// int side; //was a NS or a EW wall hit?

// int lineHeight; //Calculate height of line to draw on screen

// //calculate lowest and highest pixel to fill in current stripe
// int drawStart;
// int drawEnd;
// int x;

// SDL_Surface     *sur; // use to draw world map
// SDL_Surface     *sur2;
// SDL_Surface     *sur3;
// SDL_Surface     *menu; // use draw down side bar
// SDL_Texture     *img_menu; //use to draw down side bar

// double wallX; //where exactly the wall was hit
// int texX; //x colorRGB   ordinate on the texture
// uint32_t *pixels;
// int texNum;

// int texY;
// int d;

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

typedef  struct 	s_add
{
	int				d;
	int				x;
	int				done;
	int				colorRGB;
	uint32_t *pixels;
	uint32_t *pixels2;
}					t_add;

typedef struct		s_raycast
{
	int texNum;
	int texY;
	double wallX; //where exactly the wall was hit
	int texX; //x colorRGB   ordinate on the texture

	double posX, posY;  //x and y start position
	double dirX, dirY; //initial direction vector
	double planeX, planeY; //the 2d raycaster version of camera plane

	double cameraX;
	double rayDirX;
	double rayDirY;

	int mapX;
	int mapY;
	//length of ray from current position to next x or y-side
	double sideDistX;
	double sideDistY;
	//length of ray from one x or y-side to next x or y-side
	double deltaDistX;
	double deltaDistY;
	double perpWallDist;

	//what direction to step in x or y-direction (either +1 or -1)
	int stepX;
	int stepY;

	int hit; //was there a wall hit?
	int side; //was a NS or a EW wall hit?

	int lineHeight; //Calculate height of line to draw on screen

	//calculate lowest and highest pixel to fill in current stripe
	int drawStart;
	int drawEnd;
	int x;
}					t_raycast;

typedef struct		s_player
{
	double			time; //time of current frame
	double			oldTime; //time of previous frame
	double			frameTime; //frameTime is the time this frame has taken, in seconds
	double			moveSpeed;
	double			rotSpeed;
}					t_player;

typedef struct		s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Texture		*img;
	SDL_Texture		*fillscreen;
	SDL_Rect		texr;
	SDL_Rect		texmenu;
	SDL_Event		event;
	SDL_Surface		*sur; // use to draw world map
	SDL_Surface		*sur2;
	SDL_Surface		*sur3;
	SDL_Surface		*menu; // use draw down side bar
	SDL_Texture		*img_menu; //use to draw down side bar

	int				w, h; // texture width & height
	int				w2,h2;
	int				tmp;
	char			*img_path;
	const Uint8		*keykey;
	}					t_sdl;

typedef struct		s_al
{
	t_sdl			*sdl;
	t_player		*pl;
	t_raycast		*ray;
	t_add			*ad;
}					t_al;

#endif
