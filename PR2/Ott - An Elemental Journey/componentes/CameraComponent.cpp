#include "CameraComponent.h"

CameraComponent::CameraComponent()
{

}
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
	int x = tr_->getPos().getX();
	int y = tr_->getPos().getY();
	// mover camera.x
	// Comprobamos si la c�mara est� suficientemente cerca del jugador. En caso de que lo est�, la posici�n se settea a la 
	// posici�n del jugador. En caso contrario, se hace una interpolaci�n lineal para acercarse "lentalmente". Esto solo se aprecia cuando
	// la c�mara viaja grandes distancias (entre l�mparas, por ejemplo). 
	x = lerp(x, (int)((ottRect.x + ottRect.w / 2) - mngr_->getWinW() / 2), 0.2);

	// mover camera.y
	// Setteamos un deadzone donde la c�mara no tiene porqu� moverse (CAM_DEAD_ZONE). En caso de que el personaje salga de esta
	// zona, la c�mara se mueve. Tambi�n se mover� si est� por debajo del m�nimo admitido (CAM_OFFSET_HEIGHT * camera.h)
	// Siempre se calcula la posici�n con interpolaci�n lineal

	// RETOCAR ESTAS COSAS
	if (ottRect.y < y + tr_->getH() - CAM_DEAD_ZONE || ottRect.y > y + CAM_OFFSET_HEIGHT * tr_->getH()) {
		y = lerp(y, (ottRect.y + ottRect.h / 2) - CAM_OFFSET_HEIGHT * mngr_->getWinH() / 2, 0.2);
	}
	
	camera = { x,y,mngr_->getWinW(), mngr_->getWinH() };
	
	// Limites de la camara dependiendo del tama�o de la sala (mapa)
	if (x < 0)
	{
		x = 0;
	}
	if (y < 0)
	{
		y = 0;
	}
	if (x > LEVEL_WIDTH - tr_->getW())
	{
		x = LEVEL_WIDTH - tr_->getW();
	}
	if (y > LEVEL_HEIGHT - tr_->getH())
	{
		y = LEVEL_HEIGHT - tr_->getH();
	}
}
CameraComponent::~CameraComponent()
{
}