#ifndef SPEL_AI_H_INCLUDED
#define SPEL_AI_H_INCLUDED



void Zombie_UseBrain(Scene* scene, GameObject* zombie, int index);
SDL_Rect* FindPlayer(Scene* scene, GameObject* zombie, int range);


#endif // SPEL_AI_H_INCLUDED
