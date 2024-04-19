/**
 * \file  weather/weather_irrigation.hh
 * \brief calculations about when to irrigate based on weather data
 */

#pragma once

#include "weather.hh"

float wd2rvpt(const weather_data &wd);
float wdd2rvpt_avg(const weather_data wdd[24], unsigned from_hour = 9, unsigned to_hour = 21);

/**
 * \brief  Base class for weather adapters, which modify irrigation intervals.
 *
 *         This base class acts as neutral adapter, returning  always factor 1
 *
 */
class Weather_Adapter_Neutral  {
public:
  virtual ~Weather_Adapter_Neutral() = default;
public:
  /**
   * \brief          calculate a factor to modify irrigation intervals
   *
   *                 the user should use this function to get a factor for each weather_data
   *                 from an array of past weather data, and then calculate the average.
   *                 newer data should have more weight than older data in this average
   *
   * \param[in] wd   weather data to base calculations on
   * \return         a factor based on WD.
   */
  virtual float get_factor(const weather_data &wd) const { return 1.0; }
};

/**
 * \brief /ref Weather based automatic irrigation (work on progress)
 *
 */
class Weather_Irrigation : public Weather {
public:
  /***
   * \brief        Analyze weather data (temperature, wind, clouds) of a given week day between 9:00 and 21:00
   * \param  hours hours in the past we use (at the moment not more than 24*7 hours, which are 7 days are supported)
   * \return       calculated factor which can be used to shorten or lengthen garden irrigation intervals
   */
  float get_simple_irrigation_factor(int hours = 24,
      const Weather_Adapter_Neutral &adapter = Weather_Adapter_Neutral()) const;
};
