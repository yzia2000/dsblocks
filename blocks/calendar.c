#include <time.h>

#include "../util.h"
#include "calendar.h"

#define ICON                    COL1 "" COL0

void
calendaru(char *str, int sigval)
{
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        strftime(str, BLOCKLENGTH, "%d/%m/%Y %I:%M %p", &tm);
}
