/*
 * This software is licensed under the terms of the MIT-License
 * See COPYING for further information.
 * ---
 * Copyright (C) 2011, Lukas Weber <laochailan@web.de>
 */

#include <stdlib.h>
#include <SDL_mixer.h>

#include "resource.h"
#include "sfx.h"

char* audio_mixer_sound_path(const char *prefix, const char *name);
bool audio_mixer_check_sound_path(const char *path, bool isbgm);

char* sound_path(const char *name) {
	return audio_mixer_sound_path(SFX_PATH_PREFIX, name);
}

bool check_sound_path(const char *path) {
	return strstartswith(path, SFX_PATH_PREFIX) && audio_mixer_check_sound_path(path, false);
}

void* load_sound_begin(const char *path, unsigned int flags) {
	Mix_Chunk *sound = Mix_LoadWAV(path);

	if(!sound) {
		log_warn("Mix_LoadWAV() failed: %s", Mix_GetError());
		return NULL;
	}

	Sound *snd = calloc(1, sizeof(Sound));
	snd->impl = sound;

	return snd;
}

void* load_sound_end(void *opaque, const char *path, unsigned int flags) {
	return opaque;
}

void unload_sound(void *vsnd) {
	Sound *snd = vsnd;
	Mix_FreeChunk((Mix_Chunk*)snd->impl);
	free(snd);
}
