set(srcs inout.cc  txtio_mutex.cc) 
set(platform_srcs esp32/txtio_setup.cc host/inout.cc) 
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake")


if(COMMAND idf_component_register)
idf_component_register(SRCS ${srcs} 
    INCLUDE_DIRS "./include" 
    REQUIRES utils_misc
    PRIV_REQUIRES uout
                  esp_driver_uart vfs #PRIV_ESP_IDF
)

component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})

else()
add_library(txtio STATIC ${srcs})
target_include_directories(txtio PUBLIC ./include)
target_link_libraries(txtio PUBLIC utils_misc PRIVATE uout)

endif()
