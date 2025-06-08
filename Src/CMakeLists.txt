target_sources(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    
    main.c
    
    flexptp_options.h
    lwipopts.h

    cli.c
    cli.h
    cmds.c
    cmds.h
    osc.c
    osc.h
    task_eth.c
    task_eth.h
    uart_comm.c
    uart_comm.h
    utils.c
    utils.h

    syscall.c
    sysmem.c
)

target_include_directories(
    ${CMAKE_PROJECT_NAME}
    PUBLIC
    .
)

add_subdirectory(utils)
