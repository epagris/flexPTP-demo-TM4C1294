#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "embfmt/embformat.h"
#include "utils/uartstdio.h"

#define MAX_LINE_LENGTH (1023)

static char linebuf[MAX_LINE_LENGTH + 1];

void MSG(const char *pcString, ...) {
    va_list vaArgP;
    va_start(vaArgP, pcString);
    vembfmt(linebuf, MAX_LINE_LENGTH, pcString, vaArgP);
    va_end(vaArgP);

    UARTwrite(linebuf, strlen(linebuf));
}

void MSGchar(char c) {
    UARTwrite(&c, 1);
}

void MSGraw(const char * str) {
    UARTwrite(str, strlen(str));
}

