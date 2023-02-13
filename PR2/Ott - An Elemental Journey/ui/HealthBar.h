#pragma once
#include "UIElement.h"
#include <list>

enum HEALTHCHANGE {
	FULL_EMPTY_CONTAINER, ///< Rellena un contenedor de vida. Solo hay que usarlo cuando el contenedor ha sido previamente vaciado, NO DEBILITADO.
	UNFULL_FULL_CONTAINER, ///< Vac�a un contenedor de vida que previamente estaba lleno, NO DEBILITADO.
	WEAKEN_CONTAINER, ///< Debilita un contenedor de vida PREVIAMENTE LLENO.
	UNWEAKEN_CONTAINER, ///< Quita la debilidad al contenedor PREVIAMENTE D�BIL.
	UNFULL_WEAKEN_CONTAINER, ///< Vac�a un contenedor de vida PREVIAMENTE D�BIL.
	FULL_ALL_CONTAINERS ///< Rellena todos los contenedores simult�neamente, estuviesen o no d�biles (�til si se va a otorgar un contenedor m�s).
};

const int INITIAL_CONTAINERS = 5;
const int CONTAINER_OFFSET = 10;

class HealthBar : public UIElement {
private:
	enum HEALTHSTATE { NORMAL, WEAK, EMPTY };

	struct healthContainer {
		SDL_Rect destRect;
		HEALTHSTATE state;
	};
	struct healthList {
		list<healthContainer> healthContainerList;
		list<healthContainer>::iterator firstEmptyContainer;
		list<healthContainer>::iterator firstWeakContainer;
		list<healthContainer>::iterator lastNormalContainer;
	};

	healthList containers;
	int weakenedContainers;

public:
	HealthBar(const Vector2D& position, Texture* texture, const Scale& scale = Scale(1.0f, 1.0f)) : UIElement(position, texture, scale) {
		initializeContainers();
	}

	void render() const override;

	void initializeContainers();

	void changeHealth(HEALTHCHANGE change);

	void addContainer();

	void changeSize();

    Vector2D lastHeartPosition() const;
};

