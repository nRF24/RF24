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

message(STATUS "detected SoC: ${SOC}")