#include "anims.h"
// enum EnemyAnims { IDLE_ENEMY, DIE_ENEMY, ATTACK_ENEMY, PREPARE_ATTACK_ENEMY, WALK_ENEMY };

// Declaraci�n de variables de animaciones
// { tiempo entre frames, n� de frames, fila, columna inicial }
// enum Animations { IDLE, WALK, RUN, JUMP_UP, PEAK, FALL, LAND, VANISH, DIE, ATTACK };

// enum EarthAnims { ADVANCE, BACK }

// OTT
std::vector<anims::animDescription> anims::ott_anims{
	{300, 2, 0, 0}, { 200,4,2,0 },  // IDLE, WALK
	{ 100,8,3,0 }, { 300,1,5,2 }, // RUN, JUMP_UP
	{ 300,2,5,3 }, { 300,1,5,5 }, // PEAK, FALL
	{ 75,2,5,6 }, { 75,4,6,0 }, // LAND, VANISH
	{ 200 ,8,7,0 }, { 100,5,8,3 } }; // DIE, ATTACK
// ENEMIGO MELEE
std::vector<anims::animDescription> anims::melee_anims{ {150,4,0,0}, {150,9,0,12}, {200,4,0,8}, {450,1,0,7}, {100,3,0,4} };
// ENEMIGO A RANGO
std::vector<anims::animDescription> anims::range_anims{ {150,3,0,0}, {150,12,0,10}, {150,3,0,7}, {250,4,0,3} };
// ENEMIGO SLIME
std::vector<anims::animDescription> anims::slime_anims{ {300,4,0,0}, {150,4,0,17}, {1000,1,0,10}, {150,6,0,4}, {300,4,0,0}, {200,7,0,10} };
// WATER BOSS
std::vector<anims::animDescription> anims::waterBoss_anims{ {300,6,0,0}, {300,6,0,0}, {300,6,0,0}, {300,6,0,0}, {300,6,0,0}, {300,6,0,0} };
// ATAQUE TIERRA
std::vector<anims::animDescription> anims::earth_attack{ {100,10,0,0}, {100,10,0,9} };
//MINI BOSS TIERRA
std::vector<anims::animDescription> anims::earthBossPresent_anims{ {100, 8, 0, 0} };
std::vector<anims::animDescription> anims::earthBoss_anims{ {100, 1,0,0} };
std::vector<anims::animDescription> anims::warning_anims{ {50, 27,1,0} };
std::vector<anims::animDescription> anims::pause_anims{ {10000, 1,0,0} };
//ATAQUE AGUA
std::vector<anims::animDescription> anims::water_attack{ {100,10,0,0}, {100,10,1,9} };
// vector con todas las animaciones definidas. se accede a �l por un enum llamado Entities
std::vector<std::vector<anims::animDescription>> anims::animations{ott_anims, melee_anims, range_anims, slime_anims, earth_attack, earthBossPresent_anims,earthBoss_anims, warning_anims,pause_anims, water_attack, , waterBoss_anims };


// int izqPixels, totalHorPixels, upPixels, totalVertPixels, width, height;

// OTT
anims::offsetPhysics anims::ott_collider{ 7, 32, 4, 32, 16, 28};
// ENEMIGO MELEE
anims::offsetPhysics anims::melee_collider{ 25, 65, 5, 32, 16, 27};
// ENEMIGO A RANGO
anims::offsetPhysics anims::range_collider{ 6, 32, 10, 32, 22, 22 };
// ENEMIGO SLIME
anims::offsetPhysics anims::slime_collider{ 49, 120, 7, 60, 23, 51 };
// vector con todas las animaciones definidas. se accede a �l por un enum llamado Entities
std::vector<anims::offsetPhysics> anims::colliders{ ott_collider, melee_collider, range_collider, slime_collider };
