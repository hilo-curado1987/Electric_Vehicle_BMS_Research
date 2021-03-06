/*
    ChibiOS - Copyright (C) 2006..2015 Giovanni Di Sirio
              Copyright (C) 2015 Diego Ismirlian, TISA, (dismirlian (at) google's mail)

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

#ifndef USBH_MSD_H_
#define USBH_MSD_H_

#include "usbh.h"

#if HAL_USE_USBH && HAL_USBH_USE_MSD

/* TODO:
 *
 * - Implement of conditional compilation of multiple-luns per instance.
 * - Implement error checking and recovery when commands fail.
 *
 */


/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/


/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/


/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

#define _usbhmsd_driver_methods                                                 \
	_base_block_device_methods

struct USBHMassStorageDriverVMT {
	_usbhmsd_driver_methods
};

typedef struct USBHMassStorageLUNDriver USBHMassStorageLUNDriver;
typedef struct USBHMassStorageDriver USBHMassStorageDriver;

struct USBHMassStorageLUNDriver {
	/* inherited from abstract block driver */
	const struct USBHMassStorageDriverVMT *vmt;
	_base_block_device_data

	BlockDeviceInfo info;
	USBHMassStorageDriver *msdp;

	USBHMassStorageLUNDriver *next;
};

typedef struct USBHMassStorageDriver {
	/* inherited from abstract class driver */
	_usbh_base_classdriver_data

	/* for LUN request serialization, can be removed
	 * if the driver is configured to support only one LUN
	 * per USBHMassStorageDriver instance */
	mutex_t mtx;

	usbh_ep_t epin;
	usbh_ep_t epout;
	uint8_t ifnum;
	uint8_t max_lun;
	uint32_t tag;

	USBHMassStorageLUNDriver *luns;
} USBHMassStorageDriver;


/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/


/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

extern USBHMassStorageLUNDriver MSBLKD[HAL_USBHMSD_MAX_LUNS];
extern USBHMassStorageDriver USBHMSD[HAL_USBHMSD_MAX_INSTANCES];

#ifdef __cplusplus
extern "C" {
#endif
	/* Mass Storage Driver */
	void usbhmsdObjectInit(USBHMassStorageDriver *msdp);

	/* Mass Storage LUN Driver (block driver) */
	void usbhmsdLUNObjectInit(USBHMassStorageLUNDriver *lunp);
	void usbhmsdLUNStart(USBHMassStorageLUNDriver *lunp);
	void usbhmsdLUNStop(USBHMassStorageLUNDriver *lunp);
	bool usbhmsdLUNConnect(USBHMassStorageLUNDriver *lunp);
	bool usbhmsdLUNDisconnect(USBHMassStorageLUNDriver *lunp);
	bool usbhmsdLUNRead(USBHMassStorageLUNDriver *lunp, uint32_t startblk,
					uint8_t *buffer, uint32_t n);
	bool usbhmsdLUNWrite(USBHMassStorageLUNDriver *lunp, uint32_t startblk,
					const uint8_t *buffer, uint32_t n);
	bool usbhmsdLUNSync(USBHMassStorageLUNDriver *lunp);
	bool usbhmsdLUNGetInfo(USBHMassStorageLUNDriver *lunp, BlockDeviceInfo *bdip);
	bool usbhmsdLUNIsInserted(USBHMassStorageLUNDriver *lunp);
	bool usbhmsdLUNIsProtected(USBHMassStorageLUNDriver *lunp);
#ifdef __cplusplus
}
#endif

#endif

#endif /* USBH_MSD_H_ */
