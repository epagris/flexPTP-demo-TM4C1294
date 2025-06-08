/* (C) András Wiesner, 2020 */

#ifndef SRC_UTILS_H_
#define SRC_UTILS_H_

#include <stdbool.h>

#include <stdint.h>

#include "driverlib/sysctl.h"

#include "utils/uartstdio.h"

#include "term_colors.h"

#define EnableWaitPeripheral(x) { if(!SysCtlPeripheralReady(x)) { SysCtlPeripheralEnable(x); \
	while (!SysCtlPeripheralReady(x)) {}; }}

#ifndef htonl
#define htonl(a)                    \
        ((((a) >> 24) & 0x000000ff) |   \
         (((a) >>  8) & 0x0000ff00) |   \
         (((a) <<  8) & 0x00ff0000) |   \
         (((a) << 24) & 0xff000000))
#endif

#ifndef ntohl
#define ntohl(a)    htonl((a))
#endif

#ifndef htons
#define htons(a)                \
        ((((a) >> 8) & 0x00ff) |    \
         (((a) << 8) & 0xff00))
#endif

#ifndef ntohs
#define ntohs(a)    htons((a))
#endif

void MSG(const char *pcString, ...);
void MSGchar(char c);
void MSGraw(const char * str);

#define CLILOG(en, ...) { if (en) MSG(__VA_ARGS__); }

#define LIMIT(x,l) (x < -l ? -l : (x > l ? l : x))

#define MAX(x,y) ((x > y) ? (x) : (y))
#define MIN(x,y) ((x < y) ? (x) : (y))

#endif /* SRC_UTILS_H_ */
