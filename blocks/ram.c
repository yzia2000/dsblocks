/* See LICENSE file for copyright and license details. */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../util.h"

#define HTOP                     (char *[]){ "/usr/bin/htop", NULL }

	void 
ramu(char *str, int sigval)
{
	uintmax_t total, free, buffers, cached;

	if (pscanf("/proc/meminfo",
				"MemTotal: %ju kB\n"
				"MemFree: %ju kB\n"
				"MemAvailable: %ju kB\n"
				"Buffers: %ju kB\n"
				"Cached: %ju kB\n",
				&total, &free, &buffers, &buffers, &cached) != 5) {
		return;
	}

	if (total == 0) {
		return;
	}

	snprintf(str, BLOCKLENGTH, "RAM: %d%%", (int)(100 * ((total - free) - (buffers + cached))
			/ total));
}
