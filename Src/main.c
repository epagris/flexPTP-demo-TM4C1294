/* (C) András Wiesner, 2020 */

// FreeRTOS includes
#include "FreeRTOS.h"
#include "cli.h"
#include "cmds.h"
#include "cmsis_os2.h"
#include "flexptp/event.h"
#include "flexptp/logging.h"
#include "flexptp/ptp_profile_presets.h"
#include "flexptp/settings_interface.h"
#include "task.h"

// oscillator init function
#include "osc.h"

#include "utils.h"

// UART communication
#include "uart_comm.h"
#include "Drivers/pinout.h"

// task management
#include "task_eth.h"
#include <stdlib.h>

#define FLEXPTP_INITIAL_PROFILE ("gPTP")

// global initialization
void init()
{
    OSC_init(); // initializing oscillator
    UART_init(); // UART initialization (115200bps)
}

int main(void)
{
    init(); // initialization

    // configuring Ethernet pins
    PinoutSet(true, false);

    // --------

    MSG("\033[2J\033[H"); // clear console

    MSG(ANSI_COLOR_BGREEN "Hi!" ANSI_COLOR_BYELLOW " This is a flexPTP demo for the Texas Instruments TI Tiva C ConnectedLaunchpad (TM4C1294).\n\n"
        "The application is built on FreeRTOS, flexPTP is compiled against lwip and uses the supplied example lwip Network Stack Driver. "
        "The TM4C1294 PTP hardware module driver is also picked from the bundled ones. This flexPTP instance features a full CLI control interface, the help can be listed by typing '?' once the flexPTP has loaded. "
        "The initial PTP preset that loads upon flexPTP initialization is the 'gPTP' (802.1AS) profile. It's a nowadays common profile, but we encourage "
        "you to also try out the 'default' (plain IEEE 1588) profile and fiddle around with other options as well. The application will try to acquire an IP-address with DHCP. "
        "Once the IP-address is secured, you might start the flexPTP module by typing 'flexptp'. 'Have a great time! :)'\n\n" ANSI_COLOR_RESET);

    reg_task_eth(); // register eth task
    
    cli_init(); // initialize CLI

    cmd_init(); // initialize CLI commands

    // ---------

    vTaskStartScheduler();
}

uint8_t ucHeap[configTOTAL_HEAP_SIZE];

// *****************************************************************************

void flexptp_user_event_cb(PtpUserEventCode uev) {
    switch (uev) {
        case PTP_UEV_INIT_DONE:
            ptp_load_profile(ptp_profile_preset_get(FLEXPTP_INITIAL_PROFILE));
            ptp_log_enable(PTP_LOG_DEF, true);
            ptp_log_enable(PTP_LOG_BMCA, true);
            break;
        default:
            break;
    }
}

// *****************************************************************************
void vApplicationStackOverflowHook(xTaskHandle pxTask, char * pcTaskName)
{

    MSG("Stack overflow in task: %s\r\n", pcTaskName);

    while (1)
    {
    }
}

// runtime statistics...
volatile unsigned long g_vulRunTimeStatsCountValue;

void __error__(char *pcFilename, uint32_t ui32Line)
{
    MSG("%s:%d\r\n", pcFilename, ui32Line);
}
