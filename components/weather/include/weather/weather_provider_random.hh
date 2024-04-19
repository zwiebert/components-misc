/**
 * \file  weather/weather_provider_random.hh
 * \brief provide random mock weather data for testing purposes
 *
 */
#pragma once

#include "weather_provider.hh"
#include <cstdlib>

/**
 * \brief \ref Weather_Provider subclass for random mock weather data
 *
 */
class Weather_Provider_Random final: public Weather_Provider {
  template<typename T>
  T rando(T low_limit, T high_limit) {
    return low_limit + static_cast<T>(rand()) / (static_cast<T>(RAND_MAX / (high_limit - low_limit)));
  }
public:
  /**
   * \brief           create random weather data
   * \param[out] wd   where the fetched data goes
   */
  virtual bool fetch_weather_data(weather_data &wd) const {
    wd.main.temp = 273.15 + rando(5.0, 37.0);
    wd.main.humidity = rando(0, 100);
    wd.clouds.all = rando(0, 100);
    wd.wind.speed = rando(0, 85);

    return true;
  }
};

