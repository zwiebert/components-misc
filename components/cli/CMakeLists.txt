set(srcs cli.cc
         cmdline_get.cc  cmdline_parse.cc  cmdline_set.cc cmdline_process.cc
         mutex.cc) 
set(platform_srcs esp32/cli_task.cc) 
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake")


if(COMMAND idf_component_register)
idf_component_register(SRCS ${srcs} 
    INCLUDE_DIRS "./include"  
    REQUIRES uout jsoneat 
    PRIV_REQUIRES utils_debug utils_misc  
                  esp_event  #PRIV_ESP_IDF
)

component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})

else()
add_library(cli STATIC ${srcs})
target_include_directories(cli PUBLIC ./include)
target_link_libraries(cli PUBLIC uout jsoneat PRIVATE utils_debug utils_misc)

endif()
