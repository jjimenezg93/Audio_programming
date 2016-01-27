#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#pragma warning(disable: 4100)
#pragma warning(disable: 4710)
#pragma warning(disable: 4820)
#pragma warning(disable: 4996)

#include "../include/u-gine.h"
#include "../include/audiobuffer.h"
#include "../include/audioengine.h"
#include "../include/audiosource.h"
#include "../include/audiostream.h"
#include "../include/listener.h"

int main(int argc, char* argv[]) {
	Screen::Instance().Open(800, 600, false);

	AudioEngine::Instance().Init();

	//SIMPLE OGG
	//AudioBuffer * buffer = new AudioBuffer(String("data/mutant.ogg"));
	//AudioSource * source = new AudioSource(buffer);

	//OGG STREAMING
	AudioSource * source = new AudioSource(String("data/mutant.ogg"));
	source->SetLooping(true);
	AudioStream * stream = new AudioStream(String("data/mutant.ogg"), source);

	double xSource = 0, ySource = 0;
	double wSource = 10, hSource = 10;

	float pitch = 1;
	
	double keyDelay = 0;

	source->Play();

	while (Screen::Instance().IsOpened() && !Screen::Instance().KeyPressed(GLFW_KEY_ESC)) {
		Renderer::Instance().Clear();

		if (Screen::Instance().KeyPressed(GLFW_KEY_SPACE) && keyDelay >= 0.5) {
			if (source->IsPlaying())
				source->Pause();
			else
				source->Play();

			keyDelay = 0;
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_ENTER) && keyDelay >= 0.5) {
			if (source->IsPlaying())
				source->Stop();
			else
				source->Play();

			keyDelay = 0;
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_UP)) {
			pitch += 5;
		} else if (Screen::Instance().KeyPressed(GLFW_KEY_DOWN)) {
			pitch -= 5;
		}

		if (Screen::Instance().KeyPressed(GLFW_KEY_LEFT)) {
			xSource -= 5;
		} else if (Screen::Instance().KeyPressed(GLFW_KEY_RIGHT)) {
			 xSource += 5;
		}

		source->SetPitch(pitch);
		source->SetPosition(xSource, ySource, 0);
		Listener::Instance().SetPosition(xSource, ySource, 0);

		stream->UpdateAll();

		Renderer::Instance().SetColor(255, 255, 255, 255);
		Renderer::Instance().DrawRect(xSource, ySource, wSource, hSource);
		keyDelay += 0.1;

		Screen::Instance().Refresh();
	}

	//delete buffer;
	delete source;
	delete stream;

	AudioEngine::Instance().Finish();

	return 0;
}