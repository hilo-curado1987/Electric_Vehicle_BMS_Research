/*
    ChibiOS - Copyright (C) 2016 Stephane D'Alu

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    NRF51822/wdg_lld.h
 * @brief   WDG Driver subsystem low level driver header template.
 *
 * @addtogroup WDG
 * @{
 */

#ifndef _WDG_LLD_H_
#define _WDG_LLD_H_

#if (HAL_USE_WDG == TRUE) || defined(__DOXYGEN__)

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

#define WDG_MAX_TIMEOUT_MS					\
    ((uint32_t)(0xFFFFFFFFu * 1000 / NRF51_LFCLK_FREQUENCY))

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */

/**
 * @brief   WDG driver implement timeout callback.
 * @note    The default is @p FALSE.
 */
#if !defined(WDG_USE_TIMEOUT_CALLBACK) || defined(__DOXYGEN__)
#define WDG_USE_TIMEOUT_CALLBACK               FALSE
#endif
/** @} */


/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/**
 * @brief   Type of a structure representing an WDG driver.
 */
typedef struct WDGDriver WDGDriver;

/**
 * @brief   Driver configuration structure.
 * @note    It could be empty on some architectures.
 */
typedef struct {
    struct {
	uint8_t pause_on_sleep : 1;
	uint8_t pause_on_halt  : 1;
    } flags;
    uint32_t timeout_ms;
#if WDG_USE_TIMEOUT_CALLBACK == TRUE
    void (*callback)(void);
#endif
} WDGConfig;



/**
 * @brief   Structure representing an WDG driver.
 */
struct WDGDriver {
  /**
   * @brief   Driver state.
   */
  wdgstate_t                state;
  /**
   * @brief   Current configuration data.
   */
  const WDGConfig           *config;
  /* End of the mandatory fields.*/
  NRF_WDT_Type *wdt;
};

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern WDGDriver WDGD1;

#ifdef __cplusplus
extern "C" {
#endif
  void wdg_lld_init(void);
  void wdg_lld_start(WDGDriver *wdgp);
  void wdg_lld_stop(WDGDriver *wdgp);
  void wdg_lld_reset(WDGDriver *wdgp);
#ifdef __cplusplus
}
#endif

#endif /* HAL_USE_WDG == TRUE */

#endif /* _WDG_LLD_H_ */

/** @} */
