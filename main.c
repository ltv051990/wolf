/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlutsyk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:58:34 by tlutsyk           #+#    #+#             */
/*   Updated: 2018/05/14 19:58:36 by tlutsyk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void    calc_ray_pos_and_direct(t_al *uk)//first call;
{
    //calculate ray position and direction
    uk->ray->cameraX = 2 * uk->ray->x / (double)WIDTH - 1; //x-coordinate in camera space
    uk->ray->rayDirX = uk->ray->dirX + uk->ray->planeX * uk->ray->cameraX;
    uk->ray->rayDirY = uk->ray->dirY + uk->ray->planeY * uk->ray->cameraX;
    //which box of the map we're in
    uk->ray->mapX = (int)uk->ray->posX;
    uk->ray->mapY = (int)uk->ray->posY;

    //length of ray from one x or y-side to next x or y-side
    uk->ray->deltaDistX = sqrt(1 + (uk->ray->rayDirY * uk->ray->rayDirY) / (uk->ray->rayDirX * uk->ray->rayDirX));
    uk->ray->deltaDistY = sqrt(1 + (uk->ray->rayDirX * uk->ray->rayDirX) / (uk->ray->rayDirY * uk->ray->rayDirY));
    uk->ray->hit = 0; //was there a wall hit?
}

void  calc_step_and_init_sideDist(t_al *uk)
{
    //calculate step and initial sideDist
     if (uk->ray->rayDirX < 0)
      {
        uk->ray->stepX = -1;
        uk->ray->sideDistX = (uk->ray->posX - uk->ray->mapX) * uk->ray->deltaDistX;
      }
      else
      {
        uk->ray->stepX = 1;
        uk->ray->sideDistX = (uk->ray->mapX + 1.0 - uk->ray->posX) * uk->ray->deltaDistX;
      }
      if (uk->ray->rayDirY < 0)
      {
        uk->ray->stepY = -1;
        uk->ray->sideDistY = (uk->ray->posY - uk->ray->mapY) * uk->ray->deltaDistY;
      }
      else
      {
        uk->ray->stepY = 1;
        uk->ray->sideDistY = (uk->ray->mapY + 1.0 - uk->ray->posY) * uk->ray->deltaDistY;
      }
}

void    calc_dda(t_al *uk) {
     while (uk->ray->hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (uk->ray->sideDistX < uk->ray->sideDistY)
        {
          uk->ray->sideDistX += uk->ray->deltaDistX;
          uk->ray->mapX += uk->ray->stepX;
          uk->ray->side = 0;
        }
        else
        {
          uk->ray->sideDistY += uk->ray->deltaDistY;
          uk->ray->mapY += uk->ray->stepY;
          uk->ray->side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[uk->ray->mapX][uk->ray->mapY] > 0)
            uk->ray->hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if (uk->ray->side == 0)
        uk->ray->perpWallDist = (uk->ray->mapX - uk->ray->posX + (1 - uk->ray->stepX) / 2) / uk->ray->rayDirX;
      else
        uk->ray->perpWallDist = (uk->ray->mapY - uk->ray->posY + (1 - uk->ray->stepY) / 2) / uk->ray->rayDirY;
    //Calculate height of line to draw on screen
    uk->ray->lineHeight = (int)(HEIGHT / uk->ray->perpWallDist);
    //calculate lowest and highest pixel to fill in current stripe
    uk->ray->drawStart = -uk->ray->lineHeight / 2 + HEIGHT / 2;
      if(uk->ray->drawStart < 0)
        uk->ray->drawStart = 0;
      uk->ray->drawEnd = (int)(uk->ray->lineHeight / 2 + HEIGHT / 2);
      if(uk->ray->drawEnd >= HEIGHT)
        uk->ray->drawEnd = HEIGHT - 1;
}

void ft_init_sdl(t_al *uk)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        exit(1);
    // create the window and renderer
    // note that the renderer is accelerated
    uk->sdl->win = SDL_CreateWindow("WOLF3D", 100, 100, WIDTH, HEIGHT, 0);
    uk->sdl->renderer = SDL_CreateRenderer(uk->sdl->win, -1, SDL_RENDERER_ACCELERATED);
    uk->sdl->sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
}

void    ft_redraw_text(t_al *uk) {
	// load our image
	uk->sdl->img = IMG_LoadTexture(uk->sdl->renderer, uk->sdl->img_path);
	SDL_QueryTexture(uk->sdl->img, NULL, NULL, &uk->sdl->w, &uk->sdl->h); // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	uk->sdl->texr.x = 0;
	uk->sdl->texr.y = 0;
	uk->sdl->texr.w = WIDTH;
	uk->sdl->texr.h = HEIGHT; 

	uk->sdl->texmenu.x = WIDTH / 4;
	uk->sdl->texmenu.y = HEIGHT - 25;
	uk->sdl->texmenu.w = WIDTH / 2;
	uk->sdl->texmenu.h = 20; 
}

void    init_struct(t_al *uk) {
	uk->sdl = ft_memalloc(sizeof(t_sdl));
	uk->ray = ft_memalloc(sizeof(t_player));
	uk->pl = ft_memalloc(sizeof(t_raycast));
	uk->ad = ft_memalloc(sizeof(t_add));
	uk->sdl->tmp = 1;
	uk->sdl->img_path = "23.png";
	uk->ray->posY = 12;
	uk->ray->posX = 22;
	uk->ray->dirX = -1;
	uk->ray->dirY = 0;
	uk->ray->dirX = -1;
	uk->ray->planeX = 0;
	uk->ray->planeY = 0.66;
	uk->pl->time = 0;
	uk->pl->oldTime = 0;
}

void    present_picture(t_al *uk)
{
	 uk->sdl->img = SDL_CreateTextureFromSurface(uk->sdl->renderer, uk->sdl->sur);
	// clear the screen
	SDL_RenderClear(uk->sdl->renderer);
	// copy the texture to the rendering context
	SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img, NULL, &uk->sdl->texr);
	SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img_menu, NULL, &uk->sdl->texmenu);
	// flip the backbuffer
	// this means that everything that we prepared behind the screens is actually shown
	SDL_RenderPresent(uk->sdl->renderer);
	}

void full_exit(t_al *uk)
{
	SDL_DestroyTexture(uk->sdl->img);
	SDL_DestroyRenderer(uk->sdl->renderer);
	SDL_DestroyWindow(uk->sdl->win);
	exit(1);
}

void    key_left(t_al *uk)
{
    //both camera direction and camera plane must be rotated
    double oldDirX = uk->ray->dirX;
    uk->ray->dirX = uk->ray->dirX * cos(uk->pl->rotSpeed) - uk->ray->dirY * sin(uk->pl->rotSpeed);
    uk->ray->dirY = oldDirX * sin(uk->pl->rotSpeed) + uk->ray->dirY * cos(uk->pl->rotSpeed);
    double oldPlaneX = uk->ray->planeX;
    uk->ray->planeX = uk->ray->planeX * cos(uk->pl->rotSpeed) - uk->ray->planeY * sin(uk->pl->rotSpeed);
    uk->ray->planeY = oldPlaneX * sin(uk->pl->rotSpeed) + uk->ray->planeY * cos(uk->pl->rotSpeed);    
}

void    key_right(t_al *uk)
{
      double oldDirX = uk->ray->dirX;
      uk->ray->dirX = uk->ray->dirX * cos(-uk->pl->rotSpeed) - uk->ray->dirY * sin(-uk->pl->rotSpeed);
      uk->ray->dirY = oldDirX * sin(-uk->pl->rotSpeed) + uk->ray->dirY * cos(-uk->pl->rotSpeed);
      double oldPlaneX = uk->ray->planeX;
      uk->ray->planeX = uk->ray->planeX * cos(-uk->pl->rotSpeed) - uk->ray->planeY * sin(-uk->pl->rotSpeed);
      uk->ray->planeY = oldPlaneX * sin(-uk->pl->rotSpeed) + uk->ray->planeY * cos(-uk->pl->rotSpeed);  
}

void    key_up(t_al *uk)
{
    //move forward if no wall in front of you
    if(worldMap[(int)(uk->ray->posX + uk->ray->dirX * uk->pl->moveSpeed)][(int)(uk->ray->posY)] == false)
        uk->ray->posX += uk->ray->dirX * uk->pl->moveSpeed;
    if(worldMap[(int)(uk->ray->posX)][(int)(uk->ray->posY + uk->ray->dirY * uk->pl->moveSpeed)] == false)
        uk->ray->posY += uk->ray->dirY * uk->pl->moveSpeed;
}

void    key_down(t_al *uk)
{
    //move backwards if no wall behind you
    if(worldMap[(int)(uk->ray->posX - uk->ray->dirX * uk->pl->moveSpeed)][(int)(uk->ray->posY)] == false)
        uk->ray->posX -= uk->ray->dirX * uk->pl->moveSpeed;
    if(worldMap[(int)(uk->ray->posX)][(int)(uk->ray->posY - uk->ray->dirY * uk->pl->moveSpeed)] == false)
        uk->ray->posY -= uk->ray->dirY * uk->pl->moveSpeed;
}

void fill_line(t_al *uk)
{
    int y = -1;
    uk->ad->pixels = (uint32_t *)uk->sdl->sur->pixels;

    while(++y < HEIGHT) {
        if (y < uk->ray->drawStart)
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = (uint32_t)0xCCECFF;
        else if (y >= uk->ray->drawStart && y <= uk->ray->drawEnd)
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = uk->ad->colorRGB;
        else
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = (uint32_t)0x997676;
    }
}

void fill_line_text(t_al *uk)
{
    int y = -1;
    uk->ad->pixels = (uint32_t *)uk->sdl->sur->pixels;
    uk->ad->pixels2 = (uint32_t *)uk->sdl->sur2->pixels;

    while(++y < HEIGHT)
    {
        if (y < uk->ray->drawStart)
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = (uint32_t)0xCCECFF;
        else if (y >= uk->ray->drawStart && y < uk->ray->drawEnd)
        {
            uk->ad->d = (y * 256 - HEIGHT * 128 + uk->ray->lineHeight * 128);
            uk->ray->texY = (uint32_t)(((uk->ad->d * texHeight) / uk->ray->lineHeight) / 256);
            uk->ad->colorRGB = (unsigned int)uk->ad->pixels2[(texWidth * uk->ray->texY + uk->ray->texX)];
            if (uk->ray->side == 1)
                uk->ad->colorRGB = (uk->ad->colorRGB >> 1) & 8355711;
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = uk->ad->colorRGB;
        }
        else
            uk->ad->pixels[uk->ray->x + y * uk->sdl->sur->w] = (uint32_t)0x997676;
    }
}

void    ft_trans_img_to_int_array(t_al *uk, const char *text_name)
{
    SDL_PixelFormat a;

    a.BitsPerPixel = 32;
    a.BytesPerPixel = 4;
    a.palette = NULL;
    a.Rmask = 0;
    a.Gmask = 0;
    a.Bmask = 0;
    a.Amask = 0;
    uk->sdl->sur3 = IMG_Load(text_name);
    uk->sdl->sur2 = SDL_ConvertSurface(uk->sdl->sur3, &a, 0);
    SDL_FreeSurface(uk->sdl->sur3);
}

void    load_textures(t_al *uk)
{
    uk->sdl->menu = IMG_Load("textures/4.png");;
    SDL_QueryTexture(uk->sdl->img_menu, NULL, NULL, &uk->sdl->w2, &uk->sdl->h2); // get the width and height of the texture
    uk->sdl->img_menu = SDL_CreateTextureFromSurface(uk->sdl->renderer, uk->sdl->menu);
    
    //!!!!!!!!!!!!! malloc _ all structures
    ft_trans_img_to_int_array(uk, "textures/14.png");
}

int main (void) {
    t_al *uk;

    uk = ft_memalloc(sizeof(t_al));
    init_struct(uk);

    ft_init_sdl(uk);
 
    load_textures(uk);

    ft_redraw_text(uk);
    SDL_RenderClear(uk->sdl->renderer);
    // copy the texture to the rendering context
    SDL_RenderCopy(uk->sdl->renderer, uk->sdl->img, NULL, &uk->sdl->texr);
    // flip the backbuffer
    // this means that everything that we prepared behind the screens is actually shown
    SDL_RenderPresent(uk->sdl->renderer);
    SDL_Delay(3000);
    // main loop
    int done = 1;
    while (done) {
        uk->ray->x = -1;
        while (++uk->ray->x < WIDTH)
        {
            calc_ray_pos_and_direct(uk);
            calc_step_and_init_sideDist(uk);
            calc_dda(uk);
            //choose_texturs color
            if (worldMap[uk->ray->mapX][uk->ray->mapY] == 1)
            {
                uk->ray->texNum = worldMap[uk->ray->mapX][uk->ray->mapY] - 1;
                if (uk->ray->side == 0)
                    uk->ray->wallX = uk->ray->posY + uk->ray->perpWallDist * uk->ray->rayDirY;
                else
                    uk->ray->wallX = uk->ray->posX + uk->ray->perpWallDist * uk->ray->rayDirX;
                uk->ray->wallX -= floor((uk->ray->wallX));
                //x coordinate on the texture
                uk->ray->texX = (int)(uk->ray->wallX * (double)texWidth);
                if(uk->ray->side == 0 && uk->ray->rayDirX > 0)
                    uk->ray->texX = texWidth - uk->ray->texX - 1;
                if(uk->ray->side == 1 && uk->ray->rayDirY < 0)
                    uk->ray->texX = texWidth - uk->ray->texX - 1;
                fill_line_text(uk);
            }
             //choose wall color
            else
            {
                switch(worldMap[uk->ray->mapX][uk->ray->mapY])
                {
                    // case 1:  colorRGB = 0x990880;
                    //     break; //green
                    case 2:  uk->ad->colorRGB = 0x990000;
                        break; //green
                    case 3:  uk->ad->colorRGB = 0x5DAE8D;
                        break; //blue
                    case 4:  uk->ad->colorRGB = 0xBF4600;
                        break; //white
                    default: uk->ad->colorRGB = 0xBC93E5;
                        break; //yellow
                }
                fill_line(uk);
            }
        }
        present_picture(uk);
        uk->pl->oldTime = uk->pl->time;
        uk->pl->time = SDL_GetTicks();
        uk->pl->frameTime = (uk->pl->time - uk->pl->oldTime) / 1000.0;        
        uk->pl->moveSpeed = uk->pl->frameTime * 3.0; //the constant value is in squares/second
        uk->pl->rotSpeed = uk->pl->frameTime * 2.0;

        uk->sdl->keykey = SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&uk->sdl->event);

        if (uk->sdl->event.type == SDL_QUIT)
            full_exit(uk);
        if (uk->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            full_exit(uk);
        if (uk->sdl->keykey[SDL_SCANCODE_UP])
            key_up(uk);
        if (uk->sdl->keykey[SDL_SCANCODE_DOWN])
            key_down(uk);
        if (uk->sdl->keykey[SDL_SCANCODE_RIGHT])
            key_right(uk);
        if (uk->sdl->keykey[SDL_SCANCODE_LEFT])
            key_left(uk);
    }
    full_exit(uk);
    return 0;
}
