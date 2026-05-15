idf_component_register(SRC_DIRS "."
                       INCLUDE_DIRS "."
                       REQUIRES unity txtio)

 
component_compile_options("SHELL:-include sdkconfig.h")