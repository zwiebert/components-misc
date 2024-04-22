#include <unity.h>

#include "weather_data.h"
#include "../openweathermap.hh"
#include "weather/weather_data.hh"

void test_json() {
  weather_data w;
  TEST_ASSERT_TRUE(weather_process_json(json, w));
  TEST_ASSERT_FLOAT_WITHIN(.001, 285.09, w.main.temp);
  TEST_ASSERT_EQUAL_UINT(988, w.main.pressure);
  TEST_ASSERT_EQUAL_UINT(75, w.get_relative_humidity_percent());
  TEST_ASSERT_FLOAT_WITHIN(.001, 3.6, w.get_wind_speed_kph());
  TEST_ASSERT_EQUAL_UINT(110, w.wind.deg);
  TEST_ASSERT_EQUAL_UINT(34, w.get_cloud_coverage_percent());
}

int main() {
  UNITY_BEGIN();

  RUN_TEST(test_json);

  return UNITY_END();
}
