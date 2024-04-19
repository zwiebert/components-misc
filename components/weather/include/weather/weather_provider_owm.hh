/**
 * \file  weather/weather_provider_owm.hh
 * \brief get weather data from api.openweathermap.org
 *
 */
#pragma once

#include "weather_provider.hh"
#include <string>

/**
 * \brief \ref Weather_Provider subclass for api.openweathermap.org
 *
 */
class Weather_Provider_Owm final: public Weather_Provider {

public:

  /**
   * \brief           Fetch weather data from provider
   *
   * \param[out] dst  object to store provided weather data
   * \return          success
   */
  virtual bool fetch_weather_data(weather_data &dst) const {
    return fetch_owm_data(dst, get_url());
  }

  /**
   * \brief Get  URL stored in *this -or- configured URL
   *
   * \return  null terminated string with URL or empty, if no URL was configured
   */
  const char* get_url() const {
#ifdef CONFIG_WEATHER_OWM_URL_STRING
 if (m_url == "")
   return CONFIG_WEATHER_OWM_URL_STRING;
#endif
    return m_url.c_str();
  }

  bool set_url(const char *url) {
    m_url = url;
    return true;
  }

  /**
   * \brief       fetch data from api.openweathermap.org
   * \param dst   where the fetched data goes
   * \param url   URL string with APPID from api.openweathermap.org
   */
  static bool fetch_owm_data(weather_data &data, const char *url);

private:
  std::string m_url;  ///< URL with app-ID for api.openweathermap.org
};
