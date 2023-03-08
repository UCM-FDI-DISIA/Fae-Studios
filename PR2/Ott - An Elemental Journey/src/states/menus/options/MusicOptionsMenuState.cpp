#include "../../../utils/checkML.h"
#include "MusicOptionsMenuState.h"
#include "../../GameStateMachine.h"
#include "../../../sdlutils/SDLUtils.h"
#include "../../../components/Transform.h"
#include "../../../components/Image.h"
#include "../../../components/Text.h"
#include "../../../components/Button.h"
#include "../../../components/Slider.h"

MusicOptionsMenuState::MusicOptionsMenuState() : MenuState() {
	SDL_Color transparente{ 255,255,255,1 };
	SDL_Color darkYellow{ 194,147,42 };
	SDL_Color yellow{ 255,217,102 };
	SDL_Color blanco{ 255,255,255 };
	Vector2D textPos;
	Vector2D needlePos;
	Vector2D maxNeedlePos;
	{
		auto background = mngr_->addEntity(ecs::_grp_UI);
		background->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), sdlutils().width(), sdlutils().height());
		background->addComponent<Image>(&sdlutils().images().at("playbackground"));
	}
	{
		{
			auto returnBack = mngr_->addEntity(ecs::_grp_UI);
			returnBack->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 7), Vector2D(0, 0), 50, 50);
			returnBack->addComponent<FramedImage>(&sdlutils().images().at("button"), 1, 3);
			returnBack->addComponent<Text>("Volver", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			returnBack->addComponent<Button>(back);
			returnBack->getComponent<Transform>()->setWidth(returnBack->getComponent<FramedImage>()->getFrameWidth());
			returnBack->getComponent<Transform>()->setHeight(returnBack->getComponent<FramedImage>()->getFrameHeight());
			returnBack->getComponent<Transform>()->setPosition(returnBack->getComponent<Transform>()->getPosition() - Vector2D(returnBack->getComponent<FramedImage>()->getFrameWidth() / 2, returnBack->getComponent<FramedImage>()->getFrameHeight() / 2));
		}
	}
	{
		{
			auto generalVolumeSlider = mngr_->addEntity(ecs::_grp_UI);
			generalVolumeSlider->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 2 * sdlutils().height() / 9), Vector2D(0, 0), 50, 50);
			generalVolumeSlider->addComponent<FramedImage>(&sdlutils().images().at("slider"), 3, 1);
			generalVolumeSlider->getComponent<Transform>()->setWidth(generalVolumeSlider->getComponent<FramedImage>()->getFrameWidth());
			generalVolumeSlider->getComponent<Transform>()->setHeight(generalVolumeSlider->getComponent<FramedImage>()->getFrameHeight());
			generalVolumeSlider->getComponent<Transform>()->setPosition(generalVolumeSlider->getComponent<Transform>()->getPosition() - Vector2D(generalVolumeSlider->getComponent<FramedImage>()->getFrameWidth() / 2, generalVolumeSlider->getComponent<FramedImage>()->getFrameHeight() / 2));
			generalVolumeSlider->addComponent<Text>("Volumen general", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			generalVolumeSlider->addComponent<SliderPercentage>("100%", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			generalVolumeSlider->addComponent<Slider>(100.0f, 0.0f, 100.0f, generalVolume);

			auto generalVolumeSliderNeedle = mngr_->addEntity(ecs::_grp_UI);
			generalVolumeSliderNeedle->addComponent<Transform>(Vector2D(0,0), Vector2D(0,0), 50, 50);
			generalVolumeSliderNeedle->addComponent<FramedImage>(&sdlutils().images().at("needle"), 1, 3);
			generalVolumeSliderNeedle->getComponent<Transform>()->setWidth(generalVolumeSliderNeedle->getComponent<FramedImage>()->getFrameWidth() / 2.5f);
			generalVolumeSliderNeedle->getComponent<Transform>()->setHeight(generalVolumeSliderNeedle->getComponent<FramedImage>()->getFrameHeight() / 2.5f);
			generalVolumeSliderNeedle->addComponent<SliderNeedle>();

			generalVolumeSlider->getComponent<Slider>()->setNeedle(generalVolumeSliderNeedle);
		}
		{
			auto musicVolumeSlider = mngr_->addEntity(ecs::_grp_UI);
			musicVolumeSlider->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 4 * sdlutils().height() / 9), Vector2D(0, 0), 50, 50);
			musicVolumeSlider->addComponent<FramedImage>(&sdlutils().images().at("slider"), 3, 1);
			musicVolumeSlider->getComponent<Transform>()->setWidth(musicVolumeSlider->getComponent<FramedImage>()->getFrameWidth());
			musicVolumeSlider->getComponent<Transform>()->setHeight(musicVolumeSlider->getComponent<FramedImage>()->getFrameHeight());
			musicVolumeSlider->getComponent<Transform>()->setPosition(musicVolumeSlider->getComponent<Transform>()->getPosition() - Vector2D(musicVolumeSlider->getComponent<FramedImage>()->getFrameWidth() / 2, musicVolumeSlider->getComponent<FramedImage>()->getFrameHeight() / 2));
			musicVolumeSlider->addComponent<Text>("Música", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			musicVolumeSlider->addComponent<SliderPercentage>("100%", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			musicVolumeSlider->addComponent<Slider>(100.0f, 0.0f, 100.0f, musicVolume);

			auto musicVolumeSliderNeedle = mngr_->addEntity(ecs::_grp_UI);
			musicVolumeSliderNeedle->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 50, 50);
			musicVolumeSliderNeedle->addComponent<FramedImage>(&sdlutils().images().at("needle"), 1, 3);
			musicVolumeSliderNeedle->getComponent<Transform>()->setWidth(musicVolumeSliderNeedle->getComponent<FramedImage>()->getFrameWidth() / 2.5f);
			musicVolumeSliderNeedle->getComponent<Transform>()->setHeight(musicVolumeSliderNeedle->getComponent<FramedImage>()->getFrameHeight() / 2.5f);
			musicVolumeSliderNeedle->addComponent<SliderNeedle>();

			musicVolumeSlider->getComponent<Slider>()->setNeedle(musicVolumeSliderNeedle);
		}
		{
			auto soundVolumeSlider = mngr_->addEntity(ecs::_grp_UI);
			soundVolumeSlider->addComponent<Transform>(Vector2D(sdlutils().width() / 2, 6 * sdlutils().height() / 9), Vector2D(0, 0), 50, 50);
			soundVolumeSlider->addComponent<FramedImage>(&sdlutils().images().at("slider"), 3, 1);
			soundVolumeSlider->getComponent<Transform>()->setWidth(soundVolumeSlider->getComponent<FramedImage>()->getFrameWidth());
			soundVolumeSlider->getComponent<Transform>()->setHeight(soundVolumeSlider->getComponent<FramedImage>()->getFrameHeight());
			soundVolumeSlider->getComponent<Transform>()->setPosition(soundVolumeSlider->getComponent<Transform>()->getPosition() - Vector2D(soundVolumeSlider->getComponent<FramedImage>()->getFrameWidth() / 2, soundVolumeSlider->getComponent<FramedImage>()->getFrameHeight() / 2));
			soundVolumeSlider->addComponent<Text>("Sonido", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			soundVolumeSlider->addComponent<SliderPercentage>("100%", sdlutils().fonts().at("vcr_osd48"), blanco, transparente);
			soundVolumeSlider->addComponent<Slider>(100.0f, 0.0f, 100.0f, soundsVolume);

			auto soundVolumeSliderNeedle = mngr_->addEntity(ecs::_grp_UI);
			soundVolumeSliderNeedle->addComponent<Transform>(Vector2D(0, 0), Vector2D(0, 0), 50, 50);
			soundVolumeSliderNeedle->addComponent<FramedImage>(&sdlutils().images().at("needle"), 1, 3);
			soundVolumeSliderNeedle->getComponent<Transform>()->setWidth(soundVolumeSliderNeedle->getComponent<FramedImage>()->getFrameWidth() / 2.5f);
			soundVolumeSliderNeedle->getComponent<Transform>()->setHeight(soundVolumeSliderNeedle->getComponent<FramedImage>()->getFrameHeight() / 2.5f);
			soundVolumeSliderNeedle->addComponent<SliderNeedle>();

			soundVolumeSlider->getComponent<Slider>()->setNeedle(soundVolumeSliderNeedle);
		}
	}
}

void MusicOptionsMenuState::back() {
	GameStateMachine::instance()->popState();
}

void MusicOptionsMenuState::generalVolume(int value) {
	//app->changeVolume(0, value);
}
void MusicOptionsMenuState::musicVolume(int value) {
	//app->changeVolume(1, value);
}
void MusicOptionsMenuState::soundsVolume(int value) {
	//app->changeVolume(2, value);
}