set(srcs weather.cc openweathermap.cc weather_irrigation.cc)
set(platform_srcs "")
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake" OPTIONAL)

if(COMMAND idf_component_register)
idf_component_register(SRCS ${srcs} 
    INCLUDE_DIRS "./include"
    REQUIRES net
    PRIV_REQUIRES jsoneat kvs utils_misc
)

component_compile_options(${comp_compile_opts})
component_compile_features(${comp_compile_feats})


else()
add_library(weather STATIC ${srcs})
target_include_directories(weather PUBLIC ./include)
target_link_libraries(weather PUBLIC net PRIVATE jsoneat kvs utils_misc)

endif()
