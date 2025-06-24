target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

get_property(include_dirs TARGET ${CMAKE_PROJECT_NAME} PROPERTY INCLUDE_DIRECTORIES)
# foreach(dir ${include_dirs})
#   message(STATUS "dir='${dir}'")
# endforeach()

set(EMBFMT_CPU_PARAMS ${cpu_PARAMS})
add_subdirectory(embfmt)
target_link_libraries(${CMAKE_PROJECT_NAME} embfmt)

# add_subdirectory(blocking_io)

set(LWIP_DIR ${CMAKE_CURRENT_LIST_DIR}/lwip)
set(LWIP_PORT_DIR ${CMAKE_CURRENT_LIST_DIR}/lwip_port/tiva-tm4c129)
#set(LWIP_CONTRIB_DIR ${LWIP_DIR}/contrib)
set(LWIP_INCLUDE_DIRS
    ${LWIP_DIR}/src/include
    ${LWIP_DIR}/contrib
    ${LWIP_PORT_DIR}/include
    ${LWIP_PORT_DIR}
    ${include_dirs}
)
message(${LWIP_PORT_DIR})
set(LWIP_COMPILER_FLAGS ${cpu_PARAMS})
include(${LWIP_DIR}/src/Filelists.cmake)
#include(${LWIP_DIR}/contrib/Filelists.cmake)

target_include_directories(
    ${CMAKE_PROJECT_NAME} 
    PUBLIC
    
    ${LWIP_DIR}/src/include
    ${LWIP_PORT_DIR}
    ${LWIP_PORT_DIR}/include
)

target_sources(lwipcore PUBLIC 
    ${LWIP_PORT_DIR}/perf.c
    ${LWIP_PORT_DIR}/sys_arch.c
    ${LWIP_PORT_DIR}/netif/tiva-tm4c129.c
)
target_compile_definitions(lwipcore PUBLIC ${symbols_c_SYMB})
target_link_libraries(${CMAKE_PROJECT_NAME} lwipcore)

set(FLEXPTP_HWPORT "TM4C1294_LWIP")
set(FLEXPTP_NSD "LWIP")
set(FLEXPTP_SERVO "PID")
set(FLEXPTP_INCLUDES ${include_dirs} ${LWIP_DIR}/src/include ${LWIP_PORT_DIR}/include)
set(FLEXPTP_CPU_PARAMS ${cpu_PARAMS})
set(FLEXPTP_COMPILE_DEFS ${symbols_c_SYMB})
add_subdirectory(flexptp)
target_link_libraries(${CMAKE_PROJECT_NAME} flexptp)
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${FLEXPTP_INCLUDE_EXPORT})

