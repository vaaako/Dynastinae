#include "../../include/types/audio.hpp"
#include "../../include/utils/string.hpp"

#include <SDL2/SDL.h>

Audio::Audio(const std::string& path, const bool ismusic) : path(path), ismusic(ismusic) {
	// Init
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) != 0) {
		SDL_Log("Failed to load audio \"%s\" \n~> %s", path.c_str(), SDL_GetError());
		Mix_CloseAudio();
		SDL_Quit();
		return;
	}

	// INFO -- Apparently LoadWAV doens't necessarily need to be a .wav is just the name
	//       - I will do a little more tests, then remove this checks if this is true
	const std::string extension = String::file_extension(path);
	if(extension == "wav") {
		// this->sound = Mix_LoadWAV(path.c_str());

	} else if(extension == "ogg" || extension == "flac" || extension == "mp3") {
		// this->music = Mix_LoadMUS(path.c_str());

	} else {
		SDL_Log("Failed to load audio \"%s\" \n~> Supported extensions are: WAV, OGG, FLAC and MP3", path.c_str());
		Mix_CloseAudio();
		SDL_Quit();
		return;
	}


	if(ismusic) {
		this->music = Mix_LoadMUS(path.c_str());
	} else {
		this->sound = Mix_LoadWAV(path.c_str());
	}
}

// loops -> -1 to repeat forever
void Audio::play(const short loops) const {
	if(this->sound != nullptr) {
		Mix_PlayChannel(-1, this->sound, (loops > 0) ? loops - 1 : loops);
	} else {
		Mix_PlayMusic(this->music, loops);
	}

	// Wait until play all file
	// while(Mix_Playing(-1) != 0) {
	// 	this->isplaying = true;
	// }
	// this->isplaying = false;
}
