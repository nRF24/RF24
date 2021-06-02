# try to get the CPU model using a Linux bash command
execute_process(COMMAND cat /proc/cpuinfo
    OUTPUT_VARIABLE CPU_MODEL
    )

# If above command is not executed on an actual SOC board (& compatible OS), then
# there won't be a "Hardware" field to describe the CPU model
string(FIND ${CPU_MODEL} "Hardware" cpu_info_has_hw_field)
if(${cpu_info_has_hw_field} GREATER 0) # Hardware field does exist
    string(SUBSTRING ${CPU_MODEL} ${cpu_info_has_hw_field} -1 CPU_MODEL)
    string(REGEX MATCH "[ ]+([A-Za-z0-9_])+" SOC ${CPU_MODEL})
    string(STRIP ${SOC} SOC)
else() # Hardware field does not exist
    set(SOC "UNKNOWN") # use this string as a sentinel
endif()

# detect machine hardware name
execute_process(COMMAND uname -m
    OUTPUT_VARIABLE CPU_TYPE)
string(STRIP "${CPU_TYPE}" CPU_TYPE)
message(STATUS "detected CPU type: ${CPU_TYPE}")

# add compiler flags to optomize builds with arm-linux-gnueabihf-g* compilers
if("${CMAKE_C_COMPILER}" STREQUAL "/usr/bin/arm-linux-gnueabihf-gcc" AND
    "${CMAKE_CXX_COMPILER}" STREQUAL "/usr/bin/arm-linux-gnueabihf-g++")
    if("${SOC}" STREQUAL "BCM2835")
        add_compile_options(-marm -march=armv6zk -mtune=arm1176jzf-s -mfpu=vfp -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "BCM2836")
        add_compile_options(-march=armv7-a -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "AM33XX")
        add_compile_options(-march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "A10")
        add_compile_options(-march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "A13")
        add_compile_options(-march=armv7-a -mtune=cortex-a8 -mfpu=neon -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "A20")
        add_compile_options(-march=armv7-a -mtune=cortex-a7 -mfpu=neon-vfpv4 -mfloat-abi=hard)
    elseif("$SOC" STREQUAL "H3")
        add_compile_options(-march=armv8-a -mtune=cortex-a53 -mfpu=neon-vfpv4 -mfloat-abi=hard)
    endif()
endif()

message(STATUS "detected SoC: ${SOC}")