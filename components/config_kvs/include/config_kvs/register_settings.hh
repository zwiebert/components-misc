/**
 * \file config_kvs/register_settings.hh
 * \brief initialize the settings object
 *
 *        Include this header file into your main setup file and call register_settings()
 *
 *        The settings data is provided by the comp_glue.hh headers in each component which does want to have settings
 *
 */
#pragma once

#if __has_include(<config_kvs/comp_settings.hh>) &&  __has_include(<uout/uout_writer.hh>)
#include <config_kvs/comp_settings.hh>
#if __has_include(<net_http_server/comp_glue.hh>)
#include <net_http_server/comp_glue.hh>
#endif
#if __has_include(<net/comp_glue.hh>)
#include <net/comp_glue.hh>
#endif
#if __has_include(<net_mqtt_client/comp_glue.hh>)
#include <net_mqtt_client/comp_glue.hh>
#endif
#if __has_include(<stm32/comp_glue.hh>)
#include <stm32/comp_glue.hh>
#endif
#if __has_include(<txtio/comp_glue.hh>)
#include <txtio/comp_glue.hh>
#endif

/**
 * \brief  initializes the settings object by passing it to each component's register_setting() function
 *
 * \tparam settings_type       class type of settings object
 * \param[out] settings        settings object to be initialized
 */
template<typename settings_type>
constexpr void register_settings(settings_type &settings) {
#if __has_include(<net_http_server/comp_glue.hh>)
  net_http_server_register_settings(settings);
#endif
#if __has_include(<net/comp_glue.hh>)
  net_register_settings(settings);
#endif
#if __has_include(<net_mqtt_client/comp_glue.hh>)
  netMqtt_register_settings(settings);
#endif
#if __has_include(<stm32/comp_glue.hh>)
  stm32_register_settings(settings);
#endif
#if __has_include(<txtio/comp_glue.hh>)
  txtio_register_settings(settings);
#endif
}

#ifdef DEFINE_COMP_SETTINGS_OBJECT

#include "comp_settings.hh"
class CompSettings final : public Settings<configItem, CB_size> {
public:
  using Base = Settings<configItem, CB_size>;
public:
  constexpr CompSettings() {
    register_settings(*this);
 }
};
static constexpr CompSettings comp_settings_obj;
const SettingsBase<configItem> &comp_sett = comp_settings_obj;
#else
extern const SettingsBase<configItem> &comp_sett; // = comp_settings_obj;
#endif

#endif

