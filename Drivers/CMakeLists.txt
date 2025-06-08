# Tivaware library

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/tivaware
    ${CMAKE_CURRENT_LIST_DIR}/tivaware/inc
    ${CMAKE_CURRENT_LIST_DIR}/Inc
)

set(TIVAWARE_SRC
    tivaware/driverlib/timer.c
    tivaware/driverlib/sysexc.c
    tivaware/driverlib/uart.c
    tivaware/driverlib/eeprom.c
    tivaware/driverlib/sw_crc.c
    tivaware/driverlib/sysctl.c
    tivaware/driverlib/gpio.c
    tivaware/driverlib/usb.c
    tivaware/driverlib/epi.c
    tivaware/driverlib/emac.c
    tivaware/driverlib/i2c.c
    tivaware/driverlib/aes.c
    tivaware/driverlib/interrupt.c
    tivaware/driverlib/systick.c
    tivaware/driverlib/des.c
    tivaware/driverlib/can.c
    tivaware/driverlib/ssi.c
    tivaware/driverlib/qei.c
    tivaware/driverlib/shamd5.c
    tivaware/driverlib/adc.c
    tivaware/driverlib/lcd.c
    tivaware/driverlib/udma.c
    tivaware/driverlib/comp.c
    tivaware/driverlib/hibernate.c
    tivaware/driverlib/pwm.c
    tivaware/driverlib/cpu.c
    tivaware/driverlib/flash.c
    tivaware/driverlib/fpu.c
    tivaware/driverlib/crc.c
    tivaware/driverlib/mpu.c
    tivaware/driverlib/watchdog.c
    #tivaware/driverlib/onewire.c
)

add_library(tivaware STATIC ${TIVAWARE_SRC})
target_include_directories(tivaware PRIVATE ${CMAKE_CURRENT_LIST_DIR}/tivaware)
target_compile_options(tivaware PRIVATE
    ${cpu_PARAMS}
    -Wall
    -Wextra
    #-Wpedantic
    -Wno-unused-parameter
    
    $<$<COMPILE_LANGUAGE:ASM>:-x assembler-with-cpp -MMD -MP>
    $<$<CONFIG:Debug>:-O0 -g3 -ggdb>
    $<$<CONFIG:Release>:-Og -g0> 
)

target_compile_definitions(tivaware PRIVATE ${symbols_c_SYMB})
target_link_libraries(${CMAKE_PROJECT_NAME} tivaware)

target_sources(${CMAKE_PROJECT_NAME} 
    PUBLIC 
    
    eth_client_lwip.c
    pinout.c
)

add_subdirectory(CMSIS)