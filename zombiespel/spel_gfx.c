
#ifdef _WIN32
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#elif __APPLE__
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

#elif __linux
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#endif

#include <stdbool.h>
#include "spel_structs.h"
#include "spel_gameobject.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 800


SDL_Texture* loadTexture(char* path);
void graphics_start();
void graphics_render();
void graphics_stop();
void loadSprites();

SDL_Renderer* gRenderer;
SDL_Texture* gTexture;
SDL_Window* window = NULL;
TTF_Font* gFont = NULL;
Sprite sprites[100];
int spritesCount = 0;

void SetFont(int size)
{
    gFont = TTF_OpenFont("fonts/verdana.ttf", size);
    if(gFont == NULL)
    {
        printf("could not load font\n");
    }
}

//Sets a gameobjects text options (a text displayed on the object).
GameObject* SetText(GameObject* object, char* text, bool draw, SDL_Color textColor, int padding)
{
    strcpy(object->text, text);
    object->drawText = draw;
    object->textColor = textColor;
    object->textPadding = padding;

    SDL_Surface* srf;
    srf = TTF_RenderText_Solid(gFont, text, textColor);
    object->textTexture = SDL_CreateTextureFromSurface(gRenderer, srf);

    return object;
}

//Creates a new texture from text with a string.
GameObject* ChangeTextStr(GameObject* object, char* text)
{
    strcpy(object->text, text);

    SDL_Surface* srf;
    srf = TTF_RenderText_Solid(gFont, text, object->textColor);
    if(object->textTexture==NULL)
    {
        SDL_DestroyTexture(object->textTexture);
    }
    object->textTexture = SDL_CreateTextureFromSurface(gRenderer, srf);

    return object;
}

//Creates a new texture from text with one value.
GameObject* ChangeTextInt(GameObject* object, char* text, int value)
{
    char str[15];

    sprintf(str, "%s%d", text, value);
    strcpy(object->text, str);
    SDL_Surface* srf;
    srf = TTF_RenderText_Solid(gFont, str, object->textColor);
    object->textTexture = SDL_CreateTextureFromSurface(gRenderer, srf);
    printf("New text is:%s\n",object->text);

    return object;
}

//Creates a new texture from text with two values.
GameObject* ChangeTextInt2(GameObject* object, char* text, int value, int value2)
{
    char str[15];

    sprintf(str, "%s%d || %d", text, value,value2);
    strcpy(object->text, str);
    SDL_Surface* srf;
    srf = TTF_RenderText_Solid(gFont, str, object->textColor);
    object->textTexture = SDL_CreateTextureFromSurface(gRenderer, srf);
    printf("New text is:%s\n",object->text);

    return object;
}



void loadSprites() //Loads all the textures and adds them to an array.
{
    sprites[0].id = TXT_PLAYER;
    sprites[0].texture = loadTexture("textures/man3_anim.png");

    sprites[1].id = TXT_WALL;
    sprites[1].texture = loadTexture("textures/wall.png");

    sprites[2].id = TXT_ZOMBIE;
    sprites[2].texture = loadTexture("textures/zombie1.png");

    sprites[3].id = TXT_BULLET;
    sprites[3].texture = loadTexture("textures/bullet.png");

    sprites[4].id = TXT_BUTTON;
    sprites[4].texture = loadTexture("textures/button.png");

    sprites[5].id = TXT_MENU_BACKGROUND;
    sprites[5].texture = loadTexture("textures/Bloody_wall1.png");

    sprites[6].id = TXT_PLAYGROUND;
    sprites[6].texture = loadTexture("textures/playground.png");

    sprites[7].id = TXT_MEDKIT;
    sprites[7].texture = loadTexture("textures/medkit.png");

    sprites[8].id = TXT_GUN;
    sprites[8].texture = loadTexture("textures/vapen1.png");

    sprites[9].id = TXT_VOID;
    sprites[9].texture = loadTexture("textures/void.png");

    sprites[10].id = TXT_ZOMBIE_FAT;
    sprites[10].texture = loadTexture("textures/zombie3.png");

    sprites[11].id = TXT_CAR1;
    sprites[11].texture = loadTexture("textures/bil1.png");

    sprites[12].id =TXT_CAR2;
    sprites[12].texture = loadTexture("textures/bil2.png");

    sprites[13].id =TXT_CAR22;
    sprites[13].texture = loadTexture("textures/bil22.png");

    sprites[14].id =TXT_CAR3;
    sprites[14].texture = loadTexture("textures/bil3.png");

    sprites[15].id =TXT_CAR4;
    sprites[15].texture = loadTexture("textures/bil4.png");

    sprites[16].id =TXT_CAR42;
    sprites[16].texture = loadTexture("textures/bil42.png");

    sprites[17].id = TXT_BLOOD_SPLATTER;
    sprites[17].texture = loadTexture("textures/blood_splatter.png");

    sprites[18].id = TXT_BOMB;
    sprites[18].texture = loadTexture("textures/bomb.png");

    sprites[19].id = TXT_EXPLOSION;
    sprites[19].texture = loadTexture("textures/explosion.png");

    sprites[20].id = TXT_ARMOR;
    sprites[20].texture = loadTexture("textures/armor.png");

    sprites[21].id = TXT_MAXARMOR;
    sprites[21].texture = loadTexture("textures/maxarmor.png");

    sprites[22].id = TXT_ZBULLET;
    sprites[22].texture = loadTexture("textures/bullet_zombie.png");

    sprites[23].id = TXT_PLAYER_SCOUT;
    sprites[23].texture = loadTexture("textures/man4.png");

    sprites[24].id = TXT_PLAYER_TANK;
    sprites[24].texture = loadTexture("textures/man1.png");

    sprites[25].id = TXT_PLAYER_ENGINEER;
    sprites[25].texture = loadTexture("textures/man3_anim.png");

    sprites[26].id = TXT_ZBULLET;
    sprites[26].texture = loadTexture("textures/bullet_zombie.png");

    sprites[27].id = TXT_SHOTGUN;
    sprites[27].texture = loadTexture("textures/vapen2.png");

    sprites[28].id = TXT_REVOLVER;
    sprites[28].texture = loadTexture("textures/vapen3.png");

    sprites[29].id = TXT_MACHINEGUN;
    sprites[29].texture = loadTexture("textures/vapen1.png");

    sprites[30].id = TXT_PLAYER_SOLDIER;
    sprites[30].texture = loadTexture("textures/man2.png");

    sprites[31].id = TXT_PLAYER_SOLDIER_LOBBY;
    sprites[31].texture = loadTexture("textures/guy2.png");

    sprites[32].id = TXT_PLAYER_ENGINEER_LOBBY;
    sprites[32].texture = loadTexture("textures/guy3.png");

    sprites[33].id = TXT_PLAYER_TANK_LOBBY;
    sprites[33].texture = loadTexture("textures/guy1.png");

    sprites[34].id = TXT_PLAYER_SCOUT_LOBBY;
    sprites[34].texture = loadTexture("textures/guy4.png");


    spritesCount = 35;
}

//Used to load a texture to the program.
SDL_Texture* loadTexture(char* path)
{
    SDL_Texture* newTexture = NULL;

    SDL_Surface* loadedSurface = IMG_Load(path);
    if(loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL_image Error:%s\n", path, IMG_GetError());
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if(newTexture == NULL)
        {
            printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
        }

        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}

//Initializes SDL graphics.
void graphics_start() //
{

    TTF_Init();
    SetFont(24);
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Could not initialize SDL! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        window = SDL_CreateWindow("Outbreak Zombol City v0.8", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
            {
                printf("Could not create renderer! SDL_Error: %s\n", SDL_GetError());
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }

                //Loads all sprites in to the game.
                loadSprites();

            }
        }
    }

    printf("Graphics initialized successfully!\n");
}

//Calculates the animation frame.
void CalcAnimation(GameObject* object)
{
    if(object->state == ANIM_MOVING)
    {
        if(object->anim.animationTimer > 0)
        {
            object->anim.animationTimer -= 1;
        }
        if (object->anim.animationTimer == 0)
        {
            if(object->anim.currentCycle < object->anim.movingFrames)
            {
                object->anim.currentCycle++;
            }
            else if(object->anim.currentCycle == object->anim.movingFrames)
            {
                object->anim.currentCycle = 1;
            }
            object->anim.animationTimer = object->anim.animationSpeed;
        }
    }
    else
    {
        object->anim.currentCycle = 0;
    }
}


//Renders the passed scene to the screen.
void graphics_render(Scene level, GameObject* relative)
{
    SDL_RenderClear(gRenderer);
    SDL_Rect newRect;
    SDL_Rect srcRect;

    for(int i = 0; i < level.objectLimit; i++) // Loops through all objects which are not void.
    {
        if(level.objects[i].objectType == OBJECT_EMPTY)
            continue;
        for(int j = 0; j < spritesCount; j++) //Get the texture associated with the objects texture ID.
        {
            if(sprites[j].id == level.objects[i].id)
            {
                newRect = level.objects[i].rect;
                srcRect = level.objects[i].rect;

                if(level.objects[i].anim.animated)
                {
                    srcRect.x = level.objects[i].anim.currentCycle * level.objects[i].anim.movingOffset;
                    srcRect.y = 0;
                    srcRect.w = 128;
                    srcRect.h = 128;
                }

                //Calculates the relative position to the player which the camera is following.
                if(level.objects[i].objectType != OBJECT_BUTTON && level.objects[i].objectType != OBJECT_BACKGROUND && level.objects[i].objectType != OBJECT_UI)
                {
                    newRect.x = newRect.x - relative->rect.x + SCREEN_WIDTH/2 - relative->rect.w/2;
                    newRect.y = newRect.y - relative->rect.y + SCREEN_HEIGHT/2 - relative->rect.h/2;
                }

                //Colors the texture.
                SDL_SetTextureColorMod( sprites[j].texture, level.objects[i].drawColor.r, level.objects[i].drawColor.g, level.objects[i].drawColor.b);

                if(level.objects[i].anim.animated)
                {
                    SDL_RenderCopyEx(gRenderer, sprites[j].texture, &srcRect, &newRect, level.objects[i].rotation, level.objects[i].center, level.objects[i].flip);
                }
                else
                {
                    SDL_RenderCopyEx(gRenderer, sprites[j].texture, NULL, &newRect, level.objects[i].rotation, level.objects[i].center, level.objects[i].flip);
                }

                if(level.objects[i].drawText) //Prints out text on top of the object with padding.
                {
                    TTF_SizeText(gFont, level.objects[i].text, &newRect.w, &newRect.h);
                    newRect.x += level.objects[i].rect.w/2 -(newRect.w/2);
                    newRect.y += level.objects[i].rect.h/2 -(newRect.h/2);
                    if(level.objects[i].objectType == OBJECT_NPC || level.objects[i].objectType == OBJECT_ITEM)
                        newRect.y -= 40;
                    SDL_RenderCopy(gRenderer, level.objects[i].textTexture, NULL, &newRect);
                }
                
                break;
            }
        }
    }

    //Presents the result to the screen.
    SDL_RenderPresent(gRenderer);
}

void graphics_stop()
{
    for(int i = 0; i < spritesCount; i++) //Releases all the loaded textures.
    {
        SDL_DestroyTexture(sprites[i].texture);
    }

    printf("Textures was destroyed successfully!\n");

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(window);

    printf("Window and renderer was destroyed successfully!\n");

    SDL_Quit();
}

