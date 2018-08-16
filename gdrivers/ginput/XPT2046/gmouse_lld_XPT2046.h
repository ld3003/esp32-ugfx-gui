/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_TOUCH_H
#define _GINPUT_LLD_MOUSE_TOUCH_H

/* uGFX Includes */
#include "sdkconfig.h"
#include "ugfx_driver_config.h"

/* Touch Includes */
#include "XPT2046_adapter.h"

/* Param Include */
#include "iot_param.h"

// Resolution and Accuracy Settings
#define GMOUSE_PEN_CALIBRATE_ERROR      8
#define GMOUSE_PEN_CLICK_ERROR          6
#define GMOUSE_PEN_MOVE_ERROR           4
#define GMOUSE_FINGER_CALIBRATE_ERROR   14
#define GMOUSE_FINGER_CLICK_ERROR       18
#define GMOUSE_FINGER_MOVE_ERROR        14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_BOARD_DATA_SIZE          1

#if UGFX_LCD_DRIVER_FRAMEBUFFER_MODE
#define TOUCH_CAL_VAL_NAMESPACE   "FbUGfxParam"
#define TOUCH_CAL_VAL_KEY         "TouchCalVal"
#elif UGFX_LCD_DRIVER_API_MODE
#define TOUCH_CAL_VAL_NAMESPACE   "LcdGfxParam"
#define TOUCH_CAL_VAL_KEY         "TouchCalVal"
#else
#define TOUCH_CAL_VAL_NAMESPACE   "uGfxParam"
#define TOUCH_CAL_VAL_KEY         "touchCalVal"
#endif

static bool_t touch_init_board(GMouse *m, unsigned driverinstance)
{
    board_touch_init();
    return TRUE;
}

static GFXINLINE bool_t getpin_pressed(GMouse *m)
{
    return board_touch_is_pressed();
}

static GFXINLINE void aquire_bus(GMouse *m)
{
    /* Code here*/
}

static GFXINLINE void release_bus(GMouse *m)
{
    /* Code here*/
}

static GFXINLINE uint16_t read_value(GMouse *m, uint16_t port)
{
    return board_touch_get_position(port);
}

static GFXINLINE void touch_save_calibration(GMouse *m, const void *buf, size_t sz)
{
    iot_param_save((const char *)TOUCH_CAL_VAL_NAMESPACE, (const char *) TOUCH_CAL_VAL_KEY, (void *) buf, sz);
}
static GFXINLINE bool touch_load_calibration(GMouse *m, void *buf, size_t sz)
{
    return iot_param_load((const char *)TOUCH_CAL_VAL_NAMESPACE, (const char *) TOUCH_CAL_VAL_KEY, (void *) buf);
}

static GFXINLINE bool touch_erase_calibration(GMouse *m, void *buf, size_t sz)
{
    return iot_param_erase((const char *)TOUCH_CAL_VAL_NAMESPACE, (const char *) TOUCH_CAL_VAL_KEY);
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
