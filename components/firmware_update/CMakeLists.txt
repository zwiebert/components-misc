set(srcs dummy.cc)
set(platform_srcs esp32/ota.cc) 
include("${CMAKE_CURRENT_LIST_DIR}/../../source_filter.cmake")


idf_component_register(SRCS ${srcs}
                       INCLUDE_DIRS "./include"
                       PRIV_REQUIRES  utils_misc
                                      esp_https_ota app_update esp_event mbedtls)
target_compile_options(${COMPONENT_LIB} PRIVATE "SHELL:-include sdkconfig.h" "-Wno-error=switch")
