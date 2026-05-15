set(srcs "") 
set(platform_srcs esp32/kvs_implementation.cc host/kvs_posix.cc) 
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake")

idf_component_register(SRCS ${srcs} 
    INCLUDE_DIRS "./include"
    REQUIRES nvs_flash
    PRIV_REQUIRES  utils_debug  utils_misc
)

component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})
