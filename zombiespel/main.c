#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>//windows
//#include <SDL2/SDL.h>//mac
#include "spel_gfx.h"
#include "spel_structs.h"
#include "spel_gameobject.h"
#include <math.h>
#include "spel_actions.h"



int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Event e;
    Scene level;
    GameObject* player;

    PlayerMovement moving = {false, false, false, false};
    int mouseX, mouseY;

    playerStats stats = {100, 20, 1};

    level.objectCount = 0;

    printf("Starting graphics engine..\n");

    graphics_start(); // kalla en gång

    /*
     *Skapar två objekt och lägger in dem i objektarrayen.
     */

    player = addObjectToScene(&level, createObject("Player 1",100, 100, 128, 128, TXT_PLAYER));
    addObjectToScene(&level, createObject("ZOMBIE",128, 128, 128, 128, TXT_ZOMBIE));
    addObjectToScene(&level, createObject("ZOMBIE",240, 240, 128, 128, TXT_ZOMBIE));

    // ----------rotation

    // Game loop
    while(!quit)
    {

        // ******** INPUTS ***********
        while(SDL_PollEvent(&e) != 0)
        {
            if(e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if( e.type == SDL_KEYDOWN )
            {
                switch( e.key.keysym.sym )
                {

                    case SDLK_w:
                        moving.up = true;
                        break;
                    case SDLK_s:
                        moving.down = true;
                        break;
                    case SDLK_d:
                        moving.right = true;
                        break;
                    case SDLK_a:
                        moving.left = true;
                        break;
                }
            }
            else if( e.type == SDL_KEYUP )
            {
                switch( e.key.keysym.sym )
                {
                    case SDLK_w:
                        moving.up = false;
                        break;
                    case SDLK_s:
                        moving.down = false;
                        break;
                    case SDLK_d:
                        moving.right = false;
                        break;
                    case SDLK_a:
                        moving.left = false;
                        break;
                    case SDLK_r:
                        //
                        if(stats.klass == 1){
                            stats.ammo = 20;
                        }else printf("Fork u\n");
                        break;
                    case SDLK_e:
                        //USE
                        break;
                    case SDLK_f:
                        //special item
                        break;
                }
            }
            else if(e.type == SDL_MOUSEMOTION){
                    mouseX = e.motion.x - (SCREEN_WIDTH/2);
                    mouseY = (e.motion.y - (SCREEN_HEIGHT/2))*(-1);
                    player->rotation = 90 - (atan2(mouseY,mouseX)*180/M_PI);

            }
            else if(e.type == SDL_MOUSEBUTTONDOWN){
                if(e.button.button == SDL_BUTTON_LEFT){
                    //Vänsterklick
                    stats.ammo = stats.ammo - 1;
                    if(stats.ammo >= 0){
                        printf("Ammo count %d\n", stats.ammo);
                    }else{printf("Reload\n");}


                }
                if(e.button.button == SDL_BUTTON_RIGHT){
                    //högerklick

                }
            }

        }



        // ************ INPUTS END **********

        if(moving.up)
            player->rect.y -= 3;
        else if(moving.down)
            player->rect.y += 3;
        if(moving.left)
            player->rect.x -= 3;
        else if(moving.right)
            player->rect.x += 3;


        //player->rotation = 90 - (atan2(mouseY,mouseX)*180/M_PI);

        graphics_render(level, player); // Skickar med en "Scene" och ett relativt objekt (objekt ritas ut relativt till det objektet)
    }

    graphics_stop();

    return 0;
}


