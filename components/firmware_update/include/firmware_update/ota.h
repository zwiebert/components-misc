/**
 * \file   firmware_update/ota.h
 * \brief  over the air firmware updates
 *
 * \param firmwareURL
 * \param cert
 * \return
 */
#pragma once


#ifdef CONFIG_APP_OTA_USE_CERT_BUNDLE

/**
 * \brief  do over the air firmware update
 *
 *         Fort https, it uses cert bundle. no longer a need to provide a certificate
 *
 * \param firmwareURL   http or https URL to firmware .bin file
 * \return              success
 */
bool ota_doUpdate(const char *firmwareURL);

#else

/**
 * \brief  do over the air firmware update
 *
 * \param firmwareURL   http or https URL to firmware .bin file
 * \param cert          certificate for https
 * \return              success
 */
bool ota_doUpdate(const char *firmwareURL, const char *cert);
#endif

/**
 * \brief   states of OTA process
 */
typedef enum { ota_NONE, ota_RUN, ota_FAIL, ota_DONE} ota_state_T;

/**
 * \brief   get the state of current OTA process
 *
 * \return  state
 */
ota_state_T ota_getState(void);

