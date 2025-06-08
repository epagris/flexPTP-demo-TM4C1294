target_sources(${CMAKE_PROJECT_NAME} 
    PUBLIC
    
    locator.c
    locator.h

    lwiplib.c
    lwiplib.h

    uartstdio.c
    uartstdio.h
)

# set(LWIP_ROOT ${CMAKE_CURRENT_LIST_DIR}/third_party/lwip-1.4.1)

# target_include_directories(${CMAKE_PROJECT_NAME}
#     PUBLIC
#     ${LWIP_ROOT}/src/include
#     ${LWIP_ROOT}/ports/tiva-tm4c129/include
#     ${LWIP_ROOT}/src/include/ipv4
# )