# Compiler options with hardening flags

list(APPEND compiler_options 
    -Wall -Wextra -Wpedantic 
    # add -O2 for RELEASE or MINSIZEREL
    $<$<OR:$<CONFIG:RELEASE>,$<CONFIG:MINSIZEREL>>:-O2>
    
    # disable optim and add debuging for DEBUG
    $<$<CONFIG:DEBUG>:-O0 -g -p -pg>
)

list(APPEND compiler_definitions
# $<$<OR:$<CONFIG:RELEASE>,$<CONFIG:MINSIZEREL>>:_FORTIFY_SOURCE=2>
)

list(APPEND linker_flags
)
