#include "colliders.h"

// OTT
colliders::offsetPhysics colliders::ott_collider{ 7, 32, 4, 32, 16, 28 };
// ENEMIGO MELEE
colliders::offsetPhysics colliders::melee_collider{ 25, 65, 5, 32, 16, 27 };
// ENEMIGO A RANGO
colliders::offsetPhysics colliders::range_collider{ 6, 32, 10, 32, 22, 22 };
// ENEMIGO SLIME
colliders::offsetPhysics colliders::slime_collider{ 49, 120, 7, 60, 23, 51 };

colliders::offsetPhysics colliders::waterBoss_collider{60, 180, 60, 180, 80, 80 };
// vector con todas las animaciones definidas. se accede a él por un enum llamado Entities
std::vector<colliders::offsetPhysics> colliders::collider{ ott_collider, melee_collider, range_collider, slime_collider,waterBoss_collider };