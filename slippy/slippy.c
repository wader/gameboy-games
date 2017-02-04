/* 
 * Slippy GameBoy version (compile with GBDK)
 * Copyright (c)2000 Mattias Wadman <mattias.wadman@gmail.com>
 *
 * Slippy version history in time order:
 * 	Original version for ZShell/PhatOS by Martin Hock
 *	TI83/TI82/TI?? version by Andrew Von Dollen <warn@geocities.com>, Jason Burke
 *	JavaScript version by Mattias Wadman
 *	GameBoy version Mattias Wadman
 *
 * Images generated with PPM by Ville Helin <vhelin@cc.hut.fi>
 * http://www.hut.fi/~vhelin/ppm.html
 * 
 * Last modified: 010101 22:11
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#include <gb.h>

#define GAME_MAX_X	16
#define	GAME_MAX_Y	9
#define GAME_LEVELS	25

#define SCREEN_OFFSET_X	2
#define SCREEN_OFFSET_Y	3

#define IMAGE_BLOCK	0
#define IMAGE_EMPTY	1
#define IMAGE_MOVEABLE	2
#define IMAGE_SOLID	3
#define IMAGE_SCORE	4
#define IMAGE_PLAYER	5

#define MOVE_DOWN	0
#define MOVE_UP		1
#define MOVE_LEFT	2
#define MOVE_RIGHT	3

// Include level data
#include "levels.h"

// Macro to move sprites with absolute positions in the game area
#define _MOVE_SPRITE(n,x,y) move_sprite(n,(x+SCREEN_OFFSET_X)*8+8,(y+SCREEN_OFFSET_Y)*8+16)
// Macro to hide sprites
#define _HIDE_SPRITE(n) move_sprite(n,0,0)

unsigned char images_game[] =
{
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xff, 0xff, 0x81, 0x81, 0x83, 0x83, 0x83, 0x83,
0x83, 0x83, 0x83, 0x83, 0xbf, 0xbf, 0xff, 0xff,
0x7e, 0x7e, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81,
0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0x7e, 0x7e,
0x18, 0x18, 0x24, 0x24, 0x42, 0x42, 0x81, 0x81,
0x81, 0x81, 0x42, 0x42, 0x24, 0x24, 0x18, 0x18,
0x00, 0x00, 0x18, 0x18, 0x34, 0x34, 0x3c, 0x3c,
0x5a, 0x5a, 0x5a, 0x5a, 0x24, 0x24, 0x00, 0x00
};

unsigned char images_logo[] =
{
0x18, 0x18, 0x3e, 0x3e, 0x74, 0x74, 0xe2, 0xe2,
0x71, 0x71, 0x7a, 0x7a, 0xe7, 0xe7, 0x00, 0x00,
0x1f, 0x1f, 0x3c, 0x3c, 0x3f, 0x3f, 0x3f, 0x3f,
0x3f, 0x3f, 0x01, 0x01, 0x7f, 0x7f, 0x00, 0x00,
0xcf, 0xcf, 0x0f, 0x0f, 0xde, 0xde, 0xde, 0xde,
0xdc, 0xdc, 0xbd, 0xbd, 0xbd, 0xbd, 0x00, 0x00,
0x70, 0x70, 0x00, 0x00, 0xf3, 0xf3, 0xf7, 0xf7,
0xef, 0xef, 0xef, 0xef, 0xef, 0xef, 0x1e, 0x1e,
0x00, 0x00, 0x00, 0x00, 0xf9, 0xf9, 0x9b, 0x9b,
0x3f, 0x3f, 0xf7, 0xf7, 0xf7, 0xf7, 0x0f, 0x0f,
0x00, 0x00, 0x00, 0x00, 0xfd, 0xfd, 0xcf, 0xcf,
0x9f, 0x9f, 0xfb, 0xfb, 0xf8, 0xf8, 0x03, 0x03,
0x00, 0x00, 0x00, 0x00, 0xee, 0xee, 0xee, 0xee,
0xdc, 0xdc, 0xfc, 0xfc, 0x3c, 0x3c, 0xf8, 0xf8,
0x18, 0x18, 0x7c, 0x7c, 0x2e, 0x2e, 0x47, 0x47,
0x8e, 0x8e, 0x5e, 0x5e, 0xe7, 0xe7, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xaa, 0x00,
0xea, 0x00, 0xaa, 0x00, 0xae, 0x00, 0xaa, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00,
0x15, 0x00, 0x75, 0x00, 0x45, 0x00, 0x77, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x77, 0x00,
0x55, 0x00, 0x55, 0x00, 0x55, 0x00, 0x77, 0x00
};

unsigned char images_game_tiles[] = 
	{IMAGE_BLOCK,IMAGE_EMPTY,IMAGE_MOVEABLE,IMAGE_SOLID,IMAGE_SCORE,IMAGE_PLAYER};
unsigned char images_logo_tiles[] = 
	{6,7,8,9,10,11,12,13,14,15,16};

char game_current_level[GAME_MAX_Y][GAME_MAX_X];
BYTE game_level;
UBYTE game_scores;
UBYTE game_player_x;
UBYTE game_player_y;

char Game_Get_Pos(UBYTE x,UBYTE y)
{
	return game_current_level[y][x];
}

void Game_Set_Pos(UBYTE x,UBYTE y,UBYTE v)
{
	game_current_level[y][x] = v;
}

void Game_Set_Image(UBYTE x,UBYTE y,UBYTE img)
{
	set_bkg_tiles(x+SCREEN_OFFSET_X,y+SCREEN_OFFSET_Y,1,1,&images_game_tiles[img]);
}

void Game_Set_Current_Level(UBYTE level)
{
	char translation[6] = {' ','x','b','s','m','p'};
	UBYTE y,x,d;
	for(y=0;y < GAME_MAX_Y;y++)
		for(x=0;x < GAME_MAX_X/2;x++)
		{
			d = game_level_data[level][y][x];
			game_current_level[y][x*2] = translation[d>>4];
			game_current_level[y][(x*2)+1] = translation[d&0x0f];
		}
}

void Game_Scroll_Sprite(UBYTE sprite,UBYTE move,UBYTE n)
{
	UBYTE i,x=0,y=0;

	while(n-- > 0)
	{
		for(i=0;i < 8;i++)
		{
			scroll_sprite(sprite,
				(move == MOVE_RIGHT ? 1 : (move == MOVE_LEFT ? -1 : 0)),
				(move == MOVE_UP ? -1 : (move == MOVE_DOWN ? 1 : 0))
				);
			wait_vbl_done();
		}
	}
}


void Game_Setup_Level()
{
	UBYTE img,temp,x,y;
	game_scores = 0;
	for(y=0;y < GAME_MAX_Y;y++)
	{
		for(x=0;x < GAME_MAX_X;x++)
		{
			switch(Game_Get_Pos(x,y))
			{
				case 's':
					img = IMAGE_SOLID;
					break;
				case 'p':
					game_player_x = x;
					game_player_y = y;
					_MOVE_SPRITE(0,game_player_x,game_player_y);
					Game_Set_Pos(game_player_x,game_player_y,' '); // mark my start position with empty space (so that Game_Move does not need to care about 'p')
					img = IMAGE_EMPTY; // Make empty in background (player is a sprite)
					break;
				case 'm':
					img = IMAGE_MOVEABLE;
					break;
				case 'b':
					img = IMAGE_BLOCK;
					break;
				case 'x':
					img = IMAGE_SCORE;
					game_scores++;
					break;
				default:
					img = IMAGE_EMPTY;
					break;
			}
			Game_Set_Image(x,y,img);
		}
	}
}

void Game_Move(UBYTE move,UBYTE push)
{
	BYTE x = game_player_x;
	BYTE y = game_player_y;
	UBYTE pos,warp;
	
	if(move == MOVE_UP)
		y--;
	else if(move == MOVE_DOWN)
		y++;
	else if(move == MOVE_LEFT)
		x--;
	else if(move == MOVE_RIGHT)
		x++;
	
	warp = TRUE;
	if(x > GAME_MAX_X-1)
		x = 0;
	else if(x < 0)
		x = GAME_MAX_X-1;
	else if(y > GAME_MAX_Y-1)
		y = 0;
	else if(y < 0)
		y = GAME_MAX_Y-1;
	else
		warp = FALSE; // no warp
	
	pos = Game_Get_Pos(x,y);
	if((pos == ' ' ||  pos == 'x') && !push)
	{
		if(warp) // if warp, do not scroll player sprite
		{
			_MOVE_SPRITE(0,x,y);
			delay(120); // make joypad() happy
		}
		else
			Game_Scroll_Sprite(0,move,1);
		
		if(pos == 'x')
		{
			game_scores--;
			Game_Set_Pos(x,y,' ');
			Game_Set_Image(x,y,IMAGE_EMPTY);
			if(game_scores == 0)
			{
				game_level++;
				if(game_level > GAME_LEVELS-1)
					game_level = GAME_LEVELS-1;
				Game_Set_Current_Level(game_level);
				Game_Setup_Level();
				return;
			}
		}
			
		game_player_x = x;
		game_player_y = y;
		return;
	} 
	else if(pos == 'm' && push)
	{
		BYTE move_x = x;
		BYTE move_y = y;
		BYTE move_last_x = 0;
		BYTE move_last_y = 0;
		
		_MOVE_SPRITE(1,x,y); // show dummy
		wait_vbl_done();
		
		for(;;)
		{
			move_last_x = move_x;
			move_last_y = move_y;
				
			if(move == MOVE_UP)
				move_y--;
			else if(move == MOVE_DOWN)
				move_y++;
			else if(move == MOVE_LEFT)
				move_x--;
			else if(move == MOVE_RIGHT)
				move_x++;
				
			if(move_x > GAME_MAX_X-1 || move_x < 0 || move_y > GAME_MAX_Y-1 || move_y < 0) // hit end of game area
			{
				_HIDE_SPRITE(1); // hide dummy
				Game_Set_Pos(x,y,' '); // mark the original block position with empty space
				Game_Set_Image(x,y,IMAGE_EMPTY); // make it look like one (empty)
				return;
			}
			pos = Game_Get_Pos(move_x,move_y);
			if(pos == 'm' || pos == 's') // hit moveable or solid
			{
				_HIDE_SPRITE(1); // hide dummy
				Game_Set_Pos(x,y,' '); // mark the original block position with empty space
				Game_Set_Pos(move_last_x,move_last_y,'m'); // mask the new position as moveable
				Game_Set_Image(move_last_x,move_last_y,IMAGE_MOVEABLE); // make it look like one (moveable)
				return;
			}
			else if(pos == 'b') // hit block
			{
				_HIDE_SPRITE(1); // hide dummy
				Game_Set_Pos(x,y,' '); // mark the original block position with empty space
				Game_Set_Pos(move_x,move_y,' '); // mark the current moveable block as empty space
				Game_Set_Image(x,y,IMAGE_EMPTY); // hide moveable block (FIXME: only if no scrolling)
				Game_Set_Image(move_x,move_y,IMAGE_EMPTY); // make it look like one (empty)
				return;
			}
			else if(pos == 'x') // hit score (run over)
			{
				Game_Set_Pos(move_x,move_y,' '); // remove it
				Game_Set_Image(move_x,move_y,IMAGE_EMPTY); // make it look like one (empty)
				// continue to move
			}
			
			Game_Set_Image(x,y,IMAGE_EMPTY); // hide moveable block (FIXME: only one time)
			Game_Scroll_Sprite(1,move,1); // smoothly move our dummy		
		}
	}
}

void main()
{
	UBYTE j,k;

	disable_interrupts();
	DISPLAY_OFF;
	
	BGP_REG = OBP0_REG = 0xe4;
	SPRITES_8x8;
	
	game_level = 0;
	game_scores = 0;
	
	set_bkg_data(0,6,images_game);
	set_bkg_data(6,16,images_logo);

	for(j=0;j < 32;j++)
		for(k=0;k < 32;k++)
			set_bkg_tiles(j,k,1,1,&images_game_tiles[IMAGE_EMPTY]);
	
	set_bkg_tiles(6,13,8,1,&images_logo_tiles[0]);
	set_bkg_tiles(17,17,3,1,&images_logo_tiles[8]);

	set_sprite_data(0,6,images_game);
	set_sprite_tile(0,IMAGE_PLAYER); // Player
	set_sprite_tile(1,IMAGE_MOVEABLE); // Dummy sprite for scrolling moveable block
	set_sprite_prop(0,0);
	set_sprite_prop(1,0);
	_HIDE_SPRITE(0); // Outside screen
	_HIDE_SPRITE(1); // Outside screen
	
	Game_Set_Current_Level(0);
	Game_Setup_Level();
	
	SHOW_BKG;
	HIDE_WIN;
	SHOW_SPRITES;

	DISPLAY_ON;
	enable_interrupts();
	
	for(;;)
	{
		j = joypad();
		if(j & J_START)
		{
			Game_Set_Current_Level(game_level);
			Game_Setup_Level();
		}
		else if(j & J_SELECT) // cheat: hold down SELECT and press LEFT or RIGHT
		{
			if(j & J_LEFT || j & J_RIGHT)
			{
				game_level = (j & J_LEFT ? --game_level : (j & J_RIGHT ? ++game_level : game_level));
				if(game_level < 0)
					game_level = 0;
				if(game_level > GAME_LEVELS-1)
					game_level = GAME_LEVELS-1;
				Game_Set_Current_Level(game_level);
				Game_Setup_Level();
				delay(120); // make joypad() happy
			}
		}
		else
		{	
			if(j & J_UP)
				Game_Move(MOVE_UP,j&J_B);
			else if(j & J_DOWN)
				Game_Move(MOVE_DOWN,j&J_B);
			else if(j & J_LEFT)
				Game_Move(MOVE_LEFT,j&J_B);
			else if(j & J_RIGHT)
				Game_Move(MOVE_RIGHT,j&J_B);
		}
	}
}

