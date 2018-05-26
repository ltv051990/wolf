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

int         done = 1;
uint32_t    colorRGB;
unsigned int         *array;

double posX = 22, posY = 12;  //x and y start position
double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

double time = 0; //time of current frame
double oldTime = 0; //time of previous frame
double frameTime; //frameTime is the time this frame has taken, in seconds
double moveSpeed;
double rotSpeed;

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

SDL_Surface     *sur;
SDL_Surface     *menu;
SDL_Texture     *img_menu;

uint32_t *pixels;

void    calc_ray_pos_and_direct()//first call;
{
    //calculate ray position and direction
    cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
    rayDirX = dirX + planeX * cameraX;
    rayDirY = dirY + planeY * cameraX;
    //which box of the map we're in
    mapX = (int)posX;
    mapY = (int)posY;
    //length of ray from one x or y-side to next x or y-side
    deltaDistX = fabs(1 / rayDirX);
    deltaDistY = fabs(1 / rayDirY);
    hit = 0; //was there a wall hit?
}

void  calc_step_and_init_sideDist()
{
    //calculate step and initial sideDist
    if (rayDirX < 0)
    {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
    }
    else
    {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
    }
    if (rayDirY < 0)
    {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
    }
    else
    {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
    }
}

void    calc_dda() {
    while (hit == 0)
    {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
            sideDistX += deltaDistX;
            mapX += stepX;
            side = 0;
        }
        else
        {
            sideDistY += deltaDistY;
            mapY += stepY;
            side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
    }
    //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (side == 0)
        perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
    else
        perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY; 
    //Calculate height of line to draw on screen
    lineHeight = (int)(HEIGHT / perpWallDist);
    //calculate lowest and highest pixel to fill in current stripe
    drawStart = -lineHeight / 2 + HEIGHT / 2;
    if(drawStart < 0)
        drawStart = 0;
    drawEnd = lineHeight / 2 + HEIGHT / 2;
    if(drawEnd >= HEIGHT)
        drawEnd = HEIGHT - 1;
}

void fill_line(int x)
{
    int y = -1;
    pixels = (uint32_t *)sur->pixels;

    while(++y < HEIGHT) {
        if (y < drawStart)
            pixels[x + y * sur->w] = (uint32_t)0xCCECFF;
        else if (y >= drawStart && y <= drawEnd)
            pixels[x + y * sur->w] = colorRGB;
        else
            pixels[x + y * sur->w] = (uint32_t)0x997676;
    }
}

void ft_init_sdl(t_sdl *uk)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(1);
    // create the window and renderer
    // note that the renderer is accelerated
    uk->win = SDL_CreateWindow("WOLF3D", 100, 100, WIDTH, HEIGHT, 0);
    uk->renderer = SDL_CreateRenderer(uk->win, -1, SDL_RENDERER_ACCELERATED);
    sur = SDL_CreateRGBSurface(0, WIDTH, HEIGHT, 32, 0, 0, 0, 0);
}

void    ft_redraw_text(t_sdl *uk) {
    // load our image
    uk->img = IMG_LoadTexture(uk->renderer, uk->img_path);
    SDL_QueryTexture(uk->img, NULL, NULL, &uk->w, &uk->h); // get the width and height of the texture
    // put the location where we want the texture to be drawn into a rectangle
    // I'm also scaling the texture 2x simply by setting the width and height
    uk->texr.x = 0;
    uk->texr.y = 0;
    uk->texr.w = WIDTH;
    uk->texr.h = HEIGHT; 

    uk->texmenu.x = WIDTH / 4;
    uk->texmenu.y = HEIGHT - 25;
    uk->texmenu.w = WIDTH / 2;
    uk->texmenu.h = 20; 
}

void    init_struct(t_sdl *uk) {
    uk->tmp = 1;
    uk->img_path = "23.png";
}

void    present_picture(t_sdl *uk)
{
     uk->img = SDL_CreateTextureFromSurface(uk->renderer, sur);
    // clear the screen
    SDL_RenderClear(uk->renderer);
    // copy the texture to the rendering context
    SDL_RenderCopy(uk->renderer, uk->img, NULL, &uk->texr);
    SDL_RenderCopy(uk->renderer, img_menu, NULL, &uk->texmenu);
    // flip the backbuffer
    // this means that everything that we prepared behind the screens is actually shown
    SDL_RenderPresent(uk->renderer);
}

void full_exit(t_sdl *uk)
{
    SDL_DestroyTexture(uk->img);
    SDL_DestroyRenderer(uk->renderer);
    SDL_DestroyWindow(uk->win);
    exit(1);
}

void    key_left()
{
    // double old_x = posY;
    // double old_y = posY;

    //both camera direction and camera plane must be rotated
    double oldDirX = dirX;
    dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
    dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
    double oldPlaneX = planeX;
    planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
    planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);    
}

void    key_right()
{
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);  
}

void    key_up()
{
    //move forward if no wall in front of you
    if(worldMap[(int)(posX + dirX * moveSpeed)][(int)(posY)] == false)
        posX += dirX * moveSpeed;
    if(worldMap[(int)(posX)][(int)(posY + dirY * moveSpeed)] == false)
        posY += dirY * moveSpeed;
}

void    key_down()
{
    //move backwards if no wall behind you
    if(worldMap[(int)(posX - dirX * moveSpeed)][(int)(posY)] == false)
        posX -= dirX * moveSpeed;
    if(worldMap[(int)(posX)][(int)(posY - dirY * moveSpeed)] == false)
        posY -= dirY * moveSpeed;
}

int main (void) {
    t_sdl *uk;

    uk = ft_memalloc(sizeof(t_sdl));

    init_struct(uk);
    ft_init_sdl(uk);
   menu = IMG_Load("4.png");;
   SDL_QueryTexture(img_menu, NULL, NULL, &uk->w2, &uk->h2); // get the width and height of the texture

   img_menu = SDL_CreateTextureFromSurface(uk->renderer, menu);

    ft_redraw_text(uk);
    SDL_RenderClear(uk->renderer);
    // copy the texture to the rendering context
    SDL_RenderCopy(uk->renderer, uk->img, NULL, &uk->texr);
    // flip the backbuffer
    // this means that everything that we prepared behind the screens is actually shown
    SDL_RenderPresent(uk->renderer);
    SDL_Delay(3000);
    // main loop
    while (done) {
        x = -1;
        while (++x < WIDTH)
        {
            calc_ray_pos_and_direct();
            calc_step_and_init_sideDist();
            calc_dda();
             //choose wall color
            switch(worldMap[mapX][mapY])
            {
                case 1:  colorRGB = 0xCCAC00;
                    break; //red
                case 2:  colorRGB = 0x990000;
                    break; //green
                case 3:  colorRGB = 0x5DAE8D;
                    break; //blue
                case 4:  colorRGB = 0xBF4600;
                    break; //white
                default: colorRGB = 0xBC93E5;
                    break; //yellow
              }
                fill_line(x);
        }
        present_picture(uk);
        oldTime = time;
        time = SDL_GetTicks();
        frameTime = (time - oldTime) / 1000.0;        
        moveSpeed = frameTime * 3.0; //the constant value is in squares/second
        rotSpeed = frameTime * 2.0;

        uk->keykey = SDL_GetKeyboardState(NULL);
        SDL_PollEvent(&uk->event);

        if (uk->event.type == SDL_QUIT)
            full_exit(uk);
        if (uk->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
            full_exit(uk);
        if (uk->keykey[SDL_SCANCODE_UP])
            key_up();
        if (uk->keykey[SDL_SCANCODE_DOWN])
            key_down();
        if (uk->keykey[SDL_SCANCODE_RIGHT])
            key_right();
        if (uk->keykey[SDL_SCANCODE_LEFT])
            key_left();
    }
    full_exit(uk);
    return 0;
}
