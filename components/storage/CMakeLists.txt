set(srcs esp32/storage.c) 
set(platform_srcs "")
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake" OPTIONAL)

idf_component_register(
    SRCS ${srcs} 
    INCLUDE_DIRS "./include" 
    PRIV_INCLUDE_DIRS "./include/storage" 
    PRIV_REQUIRES  utils_debug 
                  spiffs #PRIV_ESP_IDF
 )

component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})
