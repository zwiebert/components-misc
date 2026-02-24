/**
 * \file weather/weather_data.hh
 * \brief weather data like temperature, humidity, ...
 */

#pragma once

#include <cstdio>
#include "jsoneat/from_to_json_jsmn_cbuf.hh"

/**
 * \brief struct to hold weather data we got from \ref Weather_Provider
 *
 */
struct weather_data {
  struct {
    unsigned humidity = 0;  // relative humidity in percent
    float temp = 0;  // air temperature in Kelvin
    unsigned pressure = 0;  // air pressure in mBar (== hPa)
    JSONEAT_SER_FROM_TO(JSONEAT_KvPairs(humidity, temp, pressure));
  } main;
  struct {
    float speed = 0;  // wind speed in km/h
    unsigned int deg = 0;  // wind direction in degrees
    JSONEAT_SER_FROM_TO(JSONEAT_KvPairs(speed, deg));
  } wind;
  struct {
    unsigned all = 0;   // cloud coverage in percent
    JSONEAT_SER_FROM_TO(JSONEAT_KvPairs(all));
  } clouds;

public:
  operator bool() const {return main.temp != 0; }
public:
  float get_temp_celsius() const {
    return main.temp - 273.15;
  }
  unsigned get_relative_humidity_percent() const {
    return main.humidity;
  }
  float get_wind_speed_kph() const {
    return wind.speed;
  }
  unsigned get_cloud_coverage_percent() const {
    return clouds.all;
  }
public:
    JSONEAT_SER_FROM_TO(JSONEAT_KvPairs(main, wind, clouds));
};
