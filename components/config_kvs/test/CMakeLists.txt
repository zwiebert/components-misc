idf_component_register(SRC_DIRS "."
                       INCLUDE_DIRS "." ../include 
                       REQUIRES txtio config_kvs uout  unity app_config
                       PRIV_REQUIRES kvs
)

 
component_compile_options("SHELL:-include sdkconfig.h")