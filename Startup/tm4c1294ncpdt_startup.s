
  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb

.global  g_pfnVectors
.global  Default_Handler

/* start address for the initialization values of the .data section. 
defined in linker script */
.word  _sidata
/* start address for the .data section. defined in linker script */  
.word  _sdata
/* end address for the .data section. defined in linker script */
.word  _edata
/* start address for the .bss section. defined in linker script */
.word  _sbss
/* end address for the .bss section. defined in linker script */
.word  _ebss
/* stack used for SystemInit_ExtMemCtl; always internal RAM used */

/**
 * @brief  This is the code that gets called when the processor first
 *          starts execution following a reset event. Only the absolutely
 *          necessary set is performed, after which the application
 *          supplied main() routine is called. 
 * @param  None
 * @retval : None
*/

  .section  .text.Reset_Handler
  .weak  Reset_Handler
  .type  Reset_Handler, %function
Reset_Handler:  
  ldr   sp, =_estack     /* set stack pointer */

/* Copy the data segment initializers from flash to SRAM */  
  ldr r0, =_sdata
  ldr r1, =_edata
  ldr r2, =_sidata
  movs r3, #0
  b LoopCopyDataInit

CopyDataInit:
  ldr r4, [r2, r3]
  str r4, [r0, r3]
  adds r3, r3, #4

LoopCopyDataInit:
  adds r4, r0, r3
  cmp r4, r1
  bcc CopyDataInit
  
/* Zero fill the bss segment. */
  ldr r2, =_sbss
  ldr r4, =_ebss
  movs r3, #0
  b LoopFillZerobss

FillZerobss:
  str  r3, [r2]
  adds r2, r2, #4

LoopFillZerobss:
  cmp r2, r4
  bcc FillZerobss

/* Call the clock system initialization function.*/
  bl  SystemInit   
/* Call static constructors */
    bl __libc_init_array
/* Call the application's entry point.*/
  bl  main
  bx  lr    
.size  Reset_Handler, .-Reset_Handler

/**
 * @brief  This is the code that gets called when the processor receives an 
 *         unexpected interrupt.  This simply enters an infinite loop, preserving
 *         the system state for examination by a debugger.
 * @param  None     
 * @retval None       
*/
    .section  .text.IntDefaultHandler,"ax",%progbits
IntDefaultHandler:
Infinite_Loop:
  b  Infinite_Loop
  .size  IntDefaultHandler, .-IntDefaultHandler
/******************************************************************************
*
* The minimal vector table for a Cortex M3. Note that the proper constructs
* must be placed on this to ensure that it ends up at physical address
* 0x0000.0000.
* 
*******************************************************************************/
   .section  .isr_vector,"a",%progbits
  .type  g_pfnVectors, %object
    
    
g_pfnVectors:
    .word _estack
    .word Reset_Handler                          /* The reset handler       */ 
    .word NmiSR                                  /* The NMI handler         */ 
    .word FaultISR                               /* The hard fault handler  */ 
    .word IntDefaultHandler                      /* The MPU fault handler   */ 
    .word IntDefaultHandler                      /* The bus fault handler   */ 
    .word IntDefaultHandler                      /* The usage fault handler */ 
    .word 0                                      /* Reserved                */ 
    .word 0                                      /* Reserved                */ 
    .word 0                                      /* Reserved                */ 
    .word 0                                      /* Reserved                */ 
	  .word SVC_Handler                      	     /* SVCall handler          */ 
    .word IntDefaultHandler                      /* Debug monitor handler   */  
    .word 0                                      /* Reserved                */ 
	  .word PendSV_Handler                         /* The PendSV handler      */ 
	  .word OS_Tick_Handler                        /* The SysTick handler     */ 

    /* External */
    .word IntDefaultHandler                      /* GPIO Port A                            */
    .word IntDefaultHandler                      /* GPIO Port B                            */
    .word IntDefaultHandler                      /* GPIO Port C                            */
    .word IntDefaultHandler                      /* GPIO Port D                            */
    .word IntDefaultHandler                      /* GPIO Port E                            */
	  .word UARTStdioIntHandler                    /* UART0 Rx and Tx                        */
    .word IntDefaultHandler                      /* UART1 Rx and Tx                        */
    .word IntDefaultHandler                      /* SSI0 Rx and Tx                         */
    .word IntDefaultHandler                      /* I2C0 Master and Slave                  */
    .word IntDefaultHandler                      /* PWM Fault                              */
    .word IntDefaultHandler                      /* PWM Generator 0                        */
    .word IntDefaultHandler                      /* PWM Generator 1                        */
    .word IntDefaultHandler                      /* PWM Generator 2                        */
    .word IntDefaultHandler                      /* Quadrature Encoder 0                   */
    .word IntDefaultHandler                      /* ADC Sequence 0                         */
    .word IntDefaultHandler                      /* ADC Sequence 1                         */
    .word IntDefaultHandler                      /* ADC Sequence 2                         */
    .word IntDefaultHandler                      /* ADC Sequence 3                         */
    .word IntDefaultHandler                      /* Watchdog timer                         */
    .word IntDefaultHandler                      /* Timer 0 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 0 subtimer B                     */
    .word IntDefaultHandler                      /* Timer 1 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 1 subtimer B                     */
    .word IntDefaultHandler                      /* Timer 2 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 2 subtimer B                     */
    .word IntDefaultHandler                      /* Analog Comparator 0                    */
    .word IntDefaultHandler                      /* Analog Comparator 1                    */
    .word IntDefaultHandler                      /* Analog Comparator 2                    */
    .word IntDefaultHandler                      /* System Control (PLL, OSC, BO)          */
    .word IntDefaultHandler                      /* FLASH Control                          */
    .word IntDefaultHandler                      /* GPIO Port F                            */
    .word IntDefaultHandler                      /* GPIO Port G                            */
    .word IntDefaultHandler                      /* GPIO Port H                            */
    .word IntDefaultHandler                      /* UART2 Rx and Tx                        */
    .word IntDefaultHandler                      /* SSI1 Rx and Tx                         */
    .word IntDefaultHandler                      /* Timer 3 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 3 subtimer B                     */
    .word IntDefaultHandler                      /* I2C1 Master and Slave                  */
    .word IntDefaultHandler                      /* CAN0                                   */
    .word IntDefaultHandler                      /* CAN1                                   */
	  .word lwIPEthernetIntHandler                 /* Ethernet                               */
    .word IntDefaultHandler                      /* Hibernate                              */
    .word IntDefaultHandler                      /* USB0                                   */
    .word IntDefaultHandler                      /* PWM Generator 3                        */
    .word IntDefaultHandler                      /* uDMA Software Transfer                 */
    .word IntDefaultHandler                      /* uDMA Error                             */
    .word IntDefaultHandler                      /* ADC1 Sequence 0                        */
    .word IntDefaultHandler                      /* ADC1 Sequence 1                        */
    .word IntDefaultHandler                      /* ADC1 Sequence 2                        */
    .word IntDefaultHandler                      /* ADC1 Sequence 3                        */
    .word IntDefaultHandler                      /* External Bus Interface 0               */
    .word IntDefaultHandler                      /* GPIO Port J                            */
    .word IntDefaultHandler                      /* GPIO Port K                            */
    .word IntDefaultHandler                      /* GPIO Port L                            */
    .word IntDefaultHandler                      /* SSI2 Rx and Tx                         */
    .word IntDefaultHandler                      /* SSI3 Rx and Tx                         */
    .word IntDefaultHandler                      /* UART3 Rx and Tx                        */
    .word IntDefaultHandler                      /* UART4 Rx and Tx                        */
    .word IntDefaultHandler                      /* UART5 Rx and Tx                        */
    .word IntDefaultHandler                      /* UART6 Rx and Tx                        */
    .word IntDefaultHandler                      /* UART7 Rx and Tx                        */
    .word IntDefaultHandler                      /* I2C2 Master and Slave                  */
    .word IntDefaultHandler                      /* I2C3 Master and Slave                  */
    .word IntDefaultHandler                      /* Timer 4 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 4 subtimer B                     */
    .word IntDefaultHandler                      /* Timer 5 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 5 subtimer B                     */
    .word IntDefaultHandler                      /* FPU                                    */
    .word 0                                      /* Reserved                               */
    .word 0                                      /* Reserved                               */
    .word IntDefaultHandler                      /* I2C4 Master and Slave                  */
    .word IntDefaultHandler                      /* I2C5 Master and Slave                  */
    .word IntDefaultHandler                      /* GPIO Port M                            */
    .word IntDefaultHandler                      /* GPIO Port N                            */
    .word 0                                      /* Reserved                               */
    .word IntDefaultHandler                      /* Tamper                                 */
    .word IntDefaultHandler                      /* GPIO Port P (Summary or P0)            */
    .word IntDefaultHandler                      /* GPIO Port P1                           */
    .word IntDefaultHandler                      /* GPIO Port P2                           */
    .word IntDefaultHandler                      /* GPIO Port P3                           */
    .word IntDefaultHandler                      /* GPIO Port P4                           */
    .word IntDefaultHandler                      /* GPIO Port P5                           */
    .word IntDefaultHandler                      /* GPIO Port P6                           */
    .word IntDefaultHandler                      /* GPIO Port P7                           */
    .word IntDefaultHandler                      /* GPIO Port Q (Summary or Q0)            */
    .word IntDefaultHandler                      /* GPIO Port Q1                           */
    .word IntDefaultHandler                      /* GPIO Port Q2                           */
    .word IntDefaultHandler                      /* GPIO Port Q3                           */
    .word IntDefaultHandler                      /* GPIO Port Q4                           */
    .word IntDefaultHandler                      /* GPIO Port Q5                           */
    .word IntDefaultHandler                      /* GPIO Port Q6                           */
    .word IntDefaultHandler                      /* GPIO Port Q7                           */
    .word IntDefaultHandler                      /* GPIO Port R                            */
    .word IntDefaultHandler                      /* GPIO Port S                            */
    .word IntDefaultHandler                      /* SHA/MD5 0                              */
    .word IntDefaultHandler                      /* AES 0                                  */
    .word IntDefaultHandler                      /* DES3DES 0                              */
    .word IntDefaultHandler                      /* LCD Controller 0                       */
    .word IntDefaultHandler                      /* Timer 6 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 6 subtimer B                     */
    .word IntDefaultHandler                      /* Timer 7 subtimer A                     */
    .word IntDefaultHandler                      /* Timer 7 subtimer B                     */
    .word IntDefaultHandler                      /* I2C6 Master and Slave                  */
    .word IntDefaultHandler                      /* I2C7 Master and Slave                  */
    .word IntDefaultHandler                      /* HIM Scan Matrix Keyboard 0             */
    .word IntDefaultHandler                      /* One Wire 0                             */
    .word IntDefaultHandler                      /* HIM PS/2 0                             */
    .word IntDefaultHandler                      /* HIM LED Sequencer 0                    */
    .word IntDefaultHandler                      /* HIM Consumer IR 0                      */
    .word IntDefaultHandler                      /* I2C8 Master and Slave                  */
    .word IntDefaultHandler                      /* I2C9 Master and Slave                  */
    .word IntDefaultHandler                      /* GPIO Port T                            */
    .word IntDefaultHandler                      /* Fan 1                                  */
    .word 0                                      /* Reserved                               */
                         
                         

  .size  g_pfnVectors, .-g_pfnVectors