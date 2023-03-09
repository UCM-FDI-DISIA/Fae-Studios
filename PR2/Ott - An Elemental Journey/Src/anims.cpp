#include "anims.h"
// enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY };

// Declaración de variables de animaciones
// { tiempo entre frames, nº de frames, fila, columna inicial }
// enum Animations { IDLE, WALK, RUN, JUMP_UP, PEAK, FALL, LAND, VANISH, DIE, ATTACK };

// OTT
std::vector<anims::animDescription> anims::ott_anims{ 
	{300, 2, 0, 0}, { 200,4,2,0 },  // IDLE, WALK
	{ 100,8,3,0 }, { 300,1,5,2 }, // RUN, JUMP_UP
	{ 300,2,5,3 }, { 300,1,5,5 }, // PEAK, FALL
	{ 75,2,5,6 }, { 75,4,6,0 }, // LAND, VANISH
	{ 200 ,8,7,0 }, { 100,5,8,3 } }; // DIE, ATTACK
// ENEMIGO MELEE
std::vector<anims::animDescription> anims::melee_anims{ {300,4,0,0}, {150,9,0,12}, {150,4,0,8}, {450,1,0,7}, {150,3,0,4} };
// ENEMIGO A RANGO
std::vector<anims::animDescription> anims::range_anims{ {150,3,0,0}, {150,12,0,10}, {150,3,0,7}, {250,4,0,3} };
// ENEMIGO SLIME
std::vector<anims::animDescription> anims::slime_anims{ {300,4,0,0}, {150,4,0,17}, {200,7,0,10}, {150,6,0,4} };
// vector con todas las animaciones definidas. se accede a él por un enum llamado Entities
std::vector<std::vector<anims::animDescription>> anims::animations{ ott_anims, melee_anims, range_anims, slime_anims };