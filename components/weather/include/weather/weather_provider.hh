/**
 * \file  weather/weather_provider.hh
 * \brief Interface for weather data provider
 *
 */
#pragma once

#include "weather_data.hh"

/**
 * \brief  Interface class of  a weather data provider
 *
 */
class Weather_Provider {
public:

  /**
   * \brief           Fetch weather data from provider
   *
   * \param[out] dst  object to store provided weather data
   * \return          success
   */
  virtual bool fetch_weather_data(weather_data &dst) const = 0;

public:
  virtual ~Weather_Provider() = default;
};

