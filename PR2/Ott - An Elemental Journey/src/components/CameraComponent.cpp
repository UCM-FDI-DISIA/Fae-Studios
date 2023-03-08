#include "CameraComponent.h"

float lerp(float a, float b, float t)
{
	return a + t * (b - a);
}
void CameraComponent::initComponent()
{
	playerTrnf_ = mngr_->getPlayer()->getComponent<Transform>();
	tr_ = ent_->getComponent<Transform>();
}

void CameraComponent::update()
{
	SDL_Rect ottRect = playerTrnf_->getRect(); // conseguir la posici�n de Ott
	// mover camera.x
	// Comprobamos si la c�mara est� suficientemente cerca del jugador. En caso de que lo est�, la posici�n se settea a la 
	// posici�n del jugador. En caso contrario, se hace una interpolaci�n lineal para acercarse "lentalmente". Esto solo se aprecia cuando
	// la c�mara viaja grandes distancias (entre l�mparas, por ejemplo). 
	camera.x = lerp(camera.x, ((ottRect.x + ottRect.w / 2) - mngr_->getWinW() / 2), 0.03);

	// mover camera.y
	// Setteamos un deadzone donde la c�mara no tiene porqu� moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
	// zona, la c�mara se mueve. Tambi�n se mover� si est� por debajo del m�nimo admitido (CAM_OFFSET_HEIGHT * camera.h)
	// Siempre se calcula la posici�n con interpolaci�n lineal

	// RETOCAR ESTAS COSAS
	if (ottRect.y > camera.y + camera.h - CAM_DEAD_ZONE || ottRect.y < camera.y + CAM_DEAD_ZONE) {
		camera.y = lerp(camera.y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * mngr_->getWinH(), 0.01);
	}

	// Limites de la camara dependiendo del tama�o de la sala (mapa)
	if (camera.x < 0)
	{
		camera.x = 0;
	}
	if (camera.x > LEVEL_WIDTH - tr_->getW())
	{
		camera.x = LEVEL_WIDTH - tr_->getW();
	}
	if (camera.y > LEVEL_HEIGHT - tr_->getH())
	{
		cout << "fix Y pos" << endl;
		camera.y = LEVEL_HEIGHT - tr_->getH();
	}
	camera = { camera.x,camera.y,mngr_->getWinW(), mngr_->getWinH() };
}
CameraComponent::~CameraComponent()
{
}