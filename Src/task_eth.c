#include "task_eth.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdint.h>
#include <stdbool.h>
#include "utils/uartstdio.h"

// common includes
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"

#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"

#include "utils/lwiplib.h"
#include "utils/locator.h"

#include "Drivers/pinout.h"
#include "Drivers/eth_client_lwip.h"

#include "utils.h"

extern uint32_t g_ui32SysClock;


// ----- TASK PROPERTIES -----
static TaskHandle_t sTH; // task handle
static uint8_t sPrio = 5; // priority
static uint16_t sStkSize = 256; // stack size
void task_eth(void * pParam); // task routine function
// ---------------------------

typedef union {
	uint32_t qword;
	uint8_t bytes[4];
} IPAddrUnion;

static struct {
	IPAddrUnion ipAddr; // ip-address
	bool isConnected; // are we connected to a network?
} sState;

void setup();

// register task
void reg_task_eth() {
	BaseType_t result = xTaskCreate(task_eth, "eth", sStkSize, NULL, sPrio, &sTH);
	if (result != pdPASS) { // error handling
    	MSG("Failed to create task! (errcode: %d)\n", result);
	}

	setup(); // setup
}

// initialize Ethernet
void setup_in_tcpip_thread(void * pArg) {
    uint8_t pui8MAC[6];

    LocatorInit();
    lwIPLocalMACGet(pui8MAC);
    LocatorMACAddrSet(pui8MAC);

    LocatorAppTitleSet("FlexPTP-demo");
}

// Ethernet event handling (DHCP connection successful, disconnected from the network etc.)
void eth_client_event_handler(uint32_t ui32Event, void *pvData, uint32_t ui32Param) {
	return;
}

void setup() {
	MSG("Setting up eth_task...\r\n");

	// fetch MAC-address
	uint32_t pUser[2];
	uint8_t pMAC[6];

	ROM_FlashUserGet(&pUser[0], &pUser[1]); // let's assume MAC address is fused in the chip

	// transfer to MAC array
    pMAC[0] = ((pUser[0] >>  0) & 0xff);
    pMAC[1] = ((pUser[0] >>  8) & 0xff);
    pMAC[2] = ((pUser[0] >> 16) & 0xff);
    pMAC[3] = ((pUser[1] >>  0) & 0xff);
    pMAC[4] = ((pUser[1] >>  8) & 0xff);
    pMAC[5] = ((pUser[1] >> 16) & 0xff);

    // print MAC array to the user
    MSG("MAC-address: %02x:%02x:%02x:%02x:%02x:%02x\r\n", pMAC[0], pMAC[1], pMAC[2], pMAC[3], pMAC[4], pMAC[5]);

    MSG("Setup done!\r\n");

    // set Ethernet interrupt priority low
    ROM_IntPrioritySet(INT_EMAC0, 0xE0);

    // Ethernet client (lwIP) initialization
    EthClientInit(g_ui32SysClock, eth_client_event_handler);

    // further inicialization of various services is done in the context of the tcpip's thread
    tcpip_callback(setup_in_tcpip_thread, 0);

    // store state
    sState.ipAddr.qword = 0;
    sState.isConnected = false;
}

#define PRINT_IP(ip) MSG("IP-address: %d.%d.%d.%d\r\n", (ip & 0xFF), ((ip >> 8) & 0xFF), ((ip >> 16) & 0xFF), ((ip >> 24) & 0xFF));
#define IP_ADDR_VALID(ip) (ip != 0 && ip != ~0)

void task_eth(void * pParam) {
	uint32_t currentIP = 0; // current IP address

	// FŐCIKLUS
	while (1) {
		vTaskDelay(pdMS_TO_TICKS(500)); // delay between pollings

		currentIP = lwIPLocalIPAddrGet(); // query IP address

		// hif we were not up before but now we have received an IP address
		if (sState.isConnected == false && IP_ADDR_VALID(currentIP)) {
			sState.isConnected = true;

			// print IP address
			MSG("Connected! ");
			PRINT_IP(currentIP);

		} else if (sState.isConnected == true && !IP_ADDR_VALID(currentIP)) { // if we have disconnected from the network

		    MSG("Disconnected!\n");

			sState.isConnected = false;

		} else { // we are connected
			// Todo ...
		}
	}
}
