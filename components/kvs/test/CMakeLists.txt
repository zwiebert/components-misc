idf_component_register(
    SRC_DIRS "."
    INCLUDE_DIRS "." ../include 
 #   PRIV_INCLUDE_DIRS ../include/kvs
    REQUIRES unity kvs utils_misc
)

 
component_compile_options("SHELL:-include sdkconfig.h")
