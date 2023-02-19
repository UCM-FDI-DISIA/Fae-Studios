#include "HealthBar.h"
#include <iostream>

void HealthBar::render(const SDL_Rect& Camera) const {
    for (auto it = containers.healthContainerList.begin(); it != containers.healthContainerList.end(); ++it) {
        if ((*it).state == NORMAL) { texture->renderFrame(it->destRect, 0, 1);
    }
        else if((*it).state == EMPTY) texture->renderFrame(it->destRect, 0, 4);
        else if((*it).state == WEAK) texture->renderFrame(it->destRect, 0, 12);
    }
}

void HealthBar::initializeContainers() {
    for (int i = 0; i < INITIAL_CONTAINERS; ++i) {
        SDL_Rect tmp = getRect();
        tmp.x = tmp.x + ((CONTAINER_OFFSET + tmp.w) * i);
        healthContainer h{ tmp, NORMAL };
        containers.healthContainerList.push_back(h); //Se añaden los corazones a la lista de corazones
    }
    containers.lastNormalContainer = containers.healthContainerList.end();
    --containers.lastNormalContainer; //El último corazón es el último de la lista
    containers.firstEmptyContainer = containers.healthContainerList.end();
    containers.firstWeakContainer = containers.healthContainerList.end();
    weakenedContainers = 0;
}

void HealthBar::reposition() {
    SDL_Rect tmp = getRect();
    for (auto it = containers.healthContainerList.begin(); it != containers.healthContainerList.end(); ++it) {
        it->destRect.y = tmp.y;
    }
}

void HealthBar::changeHealth(HEALTHCHANGE change) {
    switch (change) {
        case FULL_EMPTY_CONTAINER: 
            if(containers.firstEmptyContainer != containers.healthContainerList.end()) {
                containers.firstEmptyContainer->state == NORMAL;
                ++containers.firstEmptyContainer;
                ++containers.lastNormalContainer;
            }
            break;
        case UNFULL_FULL_CONTAINER: 
            if (containers.lastNormalContainer != containers.healthContainerList.begin()) {
                --containers.firstEmptyContainer;
                --containers.lastNormalContainer;
                containers.firstEmptyContainer->state = EMPTY;
            }
            else containers.lastNormalContainer->state = EMPTY;
            break;
        case WEAKEN_CONTAINER: 
            containers.firstWeakContainer = containers.lastNormalContainer;
            if(containers.healthContainerList.begin() != containers.lastNormalContainer)--containers.lastNormalContainer;
            containers.firstWeakContainer->state = WEAK;
            weakenedContainers++;
            break;
        case UNWEAKEN_CONTAINER: 
            containers.firstWeakContainer->state = NORMAL;
            ++containers.lastNormalContainer;
            ++containers.firstWeakContainer;
            weakenedContainers--;
            if (weakenedContainers == 0) containers.firstWeakContainer = containers.healthContainerList.end();
            break;
        case UNFULL_WEAKENED_CONTAINER:
            --containers.firstEmptyContainer;
            containers.firstEmptyContainer->state = EMPTY;
            weakenedContainers--;
            if (weakenedContainers == 0) containers.firstWeakContainer = containers.healthContainerList.end();
            break;
        case FULL_ALL_CONTAINERS:
            for (auto e : containers.healthContainerList) { e.state = NORMAL; }
            containers.lastNormalContainer = containers.healthContainerList.end();
            --containers.lastNormalContainer;
            containers.firstEmptyContainer = containers.healthContainerList.end();
            containers.firstWeakContainer = containers.healthContainerList.end();
            weakenedContainers = 0;
            break;
    }
}

void HealthBar::addContainer() {
    SDL_Rect tmp = getRect();
    tmp.x = tmp.x + ((tmp.w + CONTAINER_OFFSET) * containers.healthContainerList.size() - 1);
    healthContainer h{ tmp, NORMAL };
    containers.healthContainerList.push_front(h); //Se añaden los corazones a la lista de corazones
    containers.lastNormalContainer = containers.healthContainerList.end();
    --containers.lastNormalContainer;
    containers.firstEmptyContainer = containers.healthContainerList.end();
    containers.firstWeakContainer = containers.healthContainerList.end();
}

Vector2D HealthBar::lastHeartPosition() const {
    auto it = containers.healthContainerList.end();
    --it;
    return Vector2D(it->destRect.x, it->destRect.y);
}