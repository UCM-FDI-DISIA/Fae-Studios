#include "anims.h"

std::vector<anims::animDescription> anims::ott_anims{ {300, 2, 0, 0}, { 200,4,2,0 }, { 100,8,3,0 }, { 100,4,5,0 }, { 100,1,5,0 }, { 100,1,5,0 }, { 100,2,5,0 }, { 150,4,6,0 }, { 200,8,7,0 }, { 100,5,8,3 } };
std::vector<anims::animDescription> anims::melee_anims{ {300,3,0,0}, {150,4,0,3}, {150,1,0,7}, {150,4,0,8}, {150,9,0,12} };
std::vector<anims::animDescription> anims::range_anims{ {300,4,0,0}, {150,7,0,4}, {150,4,0,12} };
std::vector<anims::animDescription> anims::slime_anims{ {300,2,0,0}, {150,4,0,2}, {150,3,0,6}, {150,12,0,9} };
std::vector<std::vector<anims::animDescription>> anims::animations{ ott_anims, melee_anims, range_anims, slime_anims };