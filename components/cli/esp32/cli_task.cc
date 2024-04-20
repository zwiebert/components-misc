


#include <cli/cli.h>

#include <esp_system.h>
#include <esp_event.h>
#include <esp_log.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include <time.h>
#include <string.h>

static TaskHandle_t xHandle = NULL;
#define STACK_SIZE  6000


static void cli_task(void *pvParameters) {
  for(;;)
    cli_loop();
}


void cli_setup_task(bool enable) {
#ifdef CONFIG_APP_USE_TCPS_TASK
  static uint8_t ucParameterToPass;

  if (xHandle) {
    vTaskDelete(xHandle);
    xHandle = NULL;
  }

  if (!enable)
    return;

  xTaskCreate(cli_task, "cli_server", STACK_SIZE, &ucParameterToPass, tskIDLE_PRIORITY, &xHandle);
  configASSERT( xHandle );
#endif
}

