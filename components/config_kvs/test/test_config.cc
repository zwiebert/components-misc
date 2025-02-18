#if 1
#define DEFINE_COMP_SETTINGS_OBJECT
#include <config_kvs/register_settings.hh>
#endif

#include <unity.h>


#if 1
#include "../include/config_kvs/config.h"
#include "config_kvs/config_kvs.h"
#include <config_kvs/comp_settings.hh>
#include "kvs/kvs_wrapper.h"

#include "stdint.h"
#include "utils_misc/itoa.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <utils_misc/cstring_utils.hh>


static void tst_compSettings() {

  config_save_item_s("key1", "val1");
  {
    char buf[80] = "---------------";
    config_read_item_s("key1", buf, sizeof buf, "def1");
    TEST_ASSERT_EQUAL_STRING(buf, "val1");
  }

  {
    char buf[80] = "---------------";
    TEST_ASSERT_EQUAL_STRING("C_VERBOSE", comp_sett.get_kvsKey(CB_VERBOSE));
    config_save_item_s(comp_sett.get_kvsKey(CB_VERBOSE), "val2");
    config_read_item_s(comp_sett.get_kvsKey(CB_VERBOSE), buf, sizeof buf, "def2");
    TEST_ASSERT_EQUAL_STRING(buf, "val2");
  }

  {
    char buf[80] = "---------------";
    config_save_item_s(comp_sett.get_kvsKey(CB_VERBOSE), "val3");
    kvshT h;
    if ((h = kvs_open(CONFIG_APP_CFG_NAMESPACE, kvs_READ))) {
      kvsRead_charArray(h, CB_VERBOSE, buf);
      kvs_close(h);
    }
    TEST_ASSERT_EQUAL_STRING(buf, "val3");
  }

  {
    struct {
    char buf4[4] = "444";
    char buf8[8] = "8888888";
    } s;
    config_save_item_s(comp_sett.get_kvsKey(CB_VERBOSE), "abcd");
    kvshT h;
    if ((h = kvs_open(CONFIG_APP_CFG_NAMESPACE, kvs_READ))) {
      kvsRead_charArray(h, CB_VERBOSE, s.buf4);
      kvs_close(h);
    }
    TEST_ASSERT_EQUAL_STRING("abc", s.buf4);
  }
}


int main() {
  UNITY_BEGIN();

  RUN_TEST(tst_compSettings);

  return UNITY_END();
}

#endif
