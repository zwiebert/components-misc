#include "include/weather/weather_provider_owm.hh"
#include "jsmn/jsmn_iterate.hh"
#include "net/http_client.h"

#include <utils_misc/allocate_buffer.hh>

#include <cstring>
#include <cstdlib>
#include <cassert>

using jp = Jsmn<100>;
using jpit = jp::Iterator;
using tok_processObj_funT = bool (*)(weather_data &weather, jpit &it);

static const tok_processObj_funT tok_processRootChilds_funs[] = { //

    [](weather_data &weather, jpit &it) -> bool { // Process object: main
      if (it.keyIsEqual("main", JSMN_OBJECT)) {
        auto count = it[1].size;
        for (it += 2; count > 0 && it; --count) {
          assert(it->type == JSMN_STRING);
          if (!(it.takeValue(weather.main.humidity, "humidity") || it.takeValue(weather.main.temp, "temp") || it.takeValue(weather.main.pressure, "pressure"))) {
it.skip_key_and_value();
}
}
        return true;
      }
      return false;
    },

    [](weather_data &weather, jpit &it) -> bool { // Process object: wind
      if (it.keyIsEqual("wind", JSMN_OBJECT)) {
        auto count = it[1].size;
        for (it += 2; count > 0 && it; --count) {
          assert(it->type == JSMN_STRING);

          if (!(it.takeValue(weather.wind.speed, "speed") || it.takeValue(weather.wind.deg, "deg"))) {
            it.skip_key_and_value();
          }
        }
        return true;
      }
      return false;
    },

    [](weather_data &weather, jpit &it) -> bool {   // Process object: clouds
      if (it.keyIsEqual("clouds", JSMN_OBJECT)) {

        auto count = it[1].size;
        for (it += 2; count > 0 && it; --count) {
          assert(it->type == JSMN_STRING);

          if (!(it.takeValue(weather.clouds.all, "all"))) {
            it.skip_key_and_value();
          }
        }
        return true;
      }
      return false;
    },

    [](weather_data &weather, jpit &it) -> bool { // Throw away unwanted objects
      return it.skip_key_and_value();
    }};

bool weather_process_json(const char *json, weather_data &weather) {
  auto jsmn = jp(json);

  if (!jsmn)
    return false;

  auto it = jsmn.begin();
  if (it->type == JSMN_OBJECT) { // root object
    auto count = it->size;
    for (++it; count > 0 && it; --count) {
      assert(it->type == JSMN_STRING);

      for (auto fun : tok_processRootChilds_funs) {
        if (fun(weather, it))
          break;
      }
    }
    return true;
  }

  return false;
}

bool Weather_Provider_Owm::fetch_owm_data(weather_data &data, const char *url) {
  if (!url)
    return false;

  // alloc buffer for current content_length, which is 471
  AllocateBuffer buf(750);

  if (httpClient_getToBuffer(url, buf, buf.size()))
    if (weather_process_json(buf, data)) {
      return true;
    }

  return false;
}

