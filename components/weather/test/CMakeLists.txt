idf_component_register(SRC_DIRS "."
                       INCLUDE_DIRS "." "../include"
                       PRIV_INCLUDE_DIRS ".." 
                       REQUIRES unity weather jsoneat)

 
component_compile_options("SHELL:-include sdkconfig.h")