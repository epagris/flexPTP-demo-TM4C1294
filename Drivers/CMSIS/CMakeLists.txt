# target_sources(${CMAKE_PROJECT_NAME} 
#     PUBLIC
# )

target_include_directories(${CMAKE_PROJECT_NAME}
    PUBLIC
    Core/Include
    RTOS_V2    
)

target_sources(${CMAKE_PROJECT_NAME}
    PUBLIC
    RTOS_V2/cmsis_os2.c
)