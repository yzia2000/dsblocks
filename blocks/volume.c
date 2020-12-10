#include <stdio.h>
#include <alsa/asoundlib.h>
#include "../util.h"
#include "volume.h"

#define PAVUCONTROL                     (char *[]){ "/usr/bin/pavucontrol", NULL }
#define DEVNAME                         "default"
#define MIXNAME                         "Master"

	void
volumeu(char *str, int sigval)
{
	snd_mixer_t *mixer = NULL;
	snd_mixer_selem_id_t *mixid = NULL;
	snd_mixer_elem_t *elem = NULL;
	long min = 0, max = 0, volume = -1;
	int err;

	if ((err = snd_mixer_open(&mixer, 0))) {
		return;
	}
	if ((err = snd_mixer_attach(mixer, DEVNAME))) {
		goto cleanup;
	}
	if ((err = snd_mixer_selem_register(mixer, NULL, NULL))) {
		goto cleanup;
	}
	if ((err = snd_mixer_load(mixer))) {
		goto cleanup;
	}

	snd_mixer_selem_id_alloca(&mixid);
	snd_mixer_selem_id_set_name(mixid, MIXNAME);
	snd_mixer_selem_id_set_index(mixid, 0);

	elem = snd_mixer_find_selem(mixer, mixid);
	if (!elem) {
		goto cleanup;
	}

	if ((err = snd_mixer_selem_get_playback_volume_range(elem, &min, &max))) {
		goto cleanup;
	}
	if ((err = snd_mixer_selem_get_playback_volume(elem, SND_MIXER_SCHN_MONO, &volume))) {
	}

cleanup:
	snd_mixer_free(mixer);
	snd_mixer_detach(mixer, DEVNAME);
	snd_mixer_close(mixer);

	snprintf(str, BLOCKLENGTH, "VOL: %.0f%%", (volume-min)*100./(max-min));
}

	void
volumec(int button)
{
	switch(button) {
		case 1:
			cspawn(PAVUCONTROL);
			break;
	}
}
