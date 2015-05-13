#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <SDL.h>

#elif __APPLE__
#include <SDL2/SDL.h>

#elif __linux
#endif


#include <math.h>
#include "spel_structs.h"
#include "spel_gameobject.h"
#include "spel_AI.h"

#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0

void Zombie_UseBrain(Scene* scene, GameObject* zombie)
{
    int dx, dy;

    if(zombie->ai.atkTimer > 0)
    {
        zombie->ai.atkTimer--;
    }

    if(zombie->ai.target == NULL || zombie->ai.targetIsAlive)
    {
        zombie->ai.target = FindPlayer(scene, zombie,zombie->ai.detectRange);
    }
    if(zombie->ai.target == NULL)
            return;

    dx = zombie->rect.x - zombie->ai.target->x;
    dy = zombie->rect.y - zombie->ai.target->y;
    zombie->rotation = 270 + (atan2(dy,dx)*180/M_PI);

    dx = 0;
    dy = 0;

    dy -= sin((zombie->rotation + 90) * M_PI / 180.0f) * zombie->ai.speed; //Objektets y hastighet
    dx -= cos((zombie->rotation + 90) * M_PI / 180.0f) * zombie->ai.speed; //objektets x hastighet

    if(GetDistance(*zombie->ai.target,zombie->rect) > zombie->ai.attackRange)
    {
        MoveObject(zombie, scene, dx,dy);
    }
    if(zombie->ai.ai == AI_SPITTER && GetDistance(*zombie->ai.target,zombie->rect) < zombie->ai.attackRange)
    {
        Zombie_Shoot(zombie, scene);
    }
}

int Zombie_Shoot(GameObject* zombie, Scene* scene)
{
    if(zombie->ai.fireCount > 0){
        zombie->ai.fireCount--;
    }

    int newObject;
    if(zombie->ai.fireCount == 0){
        printf("fatass is firing!\n");
        newObject = createObject(scene, OBJECT_ZBULLET, "Spit", zombie->rect.x + (zombie->rect.w/2),zombie->rect.y + (zombie->rect.h/2), 20, 20, TXT_ZBULLET, false);
        SetBulletStats(&scene->objects[newObject], zombie->ai.bulletSpeed, zombie->rotation, zombie->ai.damage);
        zombie->ai.fireCount = zombie->ai.fireRate;
    }

    return EXIT_SUCCESS;

}

SDL_Rect* FindPlayer(Scene* scene, GameObject* zombie, int range)
{
    for(int i = 0; i < scene->objectLimit ; i++)
    {
        int distance = 10;

        if(scene->objects[i].objectType == OBJECT_PLAYER && scene->objects[i].p_stats.alive)
        {
            distance = (int)(sqrt(pow(zombie->rect.x - scene->objects[i].rect.x, 2) + pow(zombie->rect.y - scene->objects[i].rect.y, 2)));

            if(distance < range)
            {
                zombie->ai.targetIsAlive = &scene->objects[i].p_stats.alive;
                return &scene->objects[i].rect;
            }
        }
    }

    return NULL;
}

int GetDistance(SDL_Rect obj1, SDL_Rect obj2)
{
    return (int)(sqrt(pow((obj1.x + (obj1.w/2)) - (obj2.x + (obj2.w/2)), 2) + pow((obj1.y + (obj1.h/2)) - (obj2.y + (obj2.h/2)), 2)));
}
