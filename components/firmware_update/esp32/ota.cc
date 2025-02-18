#ifdef CONFIG_APP_USE_OTA
#include "firmware_update/ota.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#ifdef CONFIG_APP_OTA_USE_CERT_BUNDLE
#include "esp_crt_bundle.h"
#endif
#include "stdint.h"
#include "utils_misc/cstring_utils.hh"

static const char *TAG = "esp32_ota";

static ota_state_T state;

ota_state_T ota_getState(void) { return state; }

static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch(evt->event_id) {
        case HTTP_EVENT_ERROR:
            ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
            break;
        case HTTP_EVENT_ON_CONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
            break;
        case HTTP_EVENT_HEADER_SENT:
            ESP_LOGD(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
        case HTTP_EVENT_ON_HEADER:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
        case HTTP_EVENT_ON_DATA:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
            break;
        case HTTP_EVENT_ON_FINISH:
            ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
            break;
        case HTTP_EVENT_DISCONNECTED:
            ESP_LOGD(TAG, "HTTP_EVENT_DISCONNECTED");
            break;
        case HTTP_EVENT_REDIRECT: //TODO? implement HTTP_EVENT_REDIRECT?
          ESP_LOGD(TAG, "HTTP_EVENT_REDIRECT");
          break;

    }
    return ESP_OK;
}

struct task_parm {
  csu url;
  const char *cert;
};

static void simple_ota_example_task(void *pvParameter) {
  auto parm = static_cast<task_parm*>(pvParameter);


  esp_http_client_config_t http_config = { .url = parm->url,
#ifndef CONFIG_APP_OTA_USE_CERT_BUNDLE
        .cert_pem = parm->cert,
#endif
      .event_handler = http_event_handler,
#ifdef CONFIG_APP_OTA_USE_CERT_BUNDLE
        .crt_bundle_attach = esp_crt_bundle_attach,
#endif
        .keep_alive_enable = true,
  };

  esp_https_ota_config_t config = { .http_config = &http_config, };

  state = ota_RUN;
  esp_err_t ret = esp_https_ota(&config);

  state = (ret == ESP_OK) ? ota_DONE : ota_FAIL;

  delete (parm);
  vTaskDelete(NULL);
}


static bool our_ota_doUpdate(const char *firmware_url, const char *cert) {
  auto parm = new task_parm;
  parm->url = firmware_url;
  parm->cert = cert;

  xTaskCreate(&simple_ota_example_task, "esp32_ota_update", 16384, parm, 5, NULL);
  return false;
}

#ifdef CONFIG_APP_OTA_USE_CERT_BUNDLE
bool ota_doUpdate(const char *url) {
  return our_ota_doUpdate(url, nullptr);
}
#else
#error "ca_cert.pem no longer works"
bool ota_doUpdate(const char *url, const char *cert) {
  return our_ota_doUpdate(url, cert);
}
#endif
void ota_setup()
{

}

#endif
