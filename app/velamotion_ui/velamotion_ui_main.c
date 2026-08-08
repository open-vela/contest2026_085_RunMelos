/****************************************************************************
 * app/velamotion_ui/velamotion_ui_main.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include <nuttx/config.h>

#include <signal.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include "ui/velamotion_ui.h"

static volatile sig_atomic_t g_velamotion_ui_stop;

static void velamotion_ui_signal_handler(int signo)
{
  g_velamotion_ui_stop = 1;
}

int main(int argc, FAR char *argv[])
{
  lv_nuttx_dsc_t info;
  lv_nuttx_result_t result;
  struct sigaction action;
  int ret = 0;

  if (lv_is_initialized())
    {
      fprintf(stderr, "velamotion_ui: LVGL is already running\n");
      return 1;
    }

  action.sa_handler = velamotion_ui_signal_handler;
  sigemptyset(&action.sa_mask);
  action.sa_flags = 0;
  sigaction(SIGINT, &action, NULL);
  sigaction(SIGTERM, &action, NULL);

  g_velamotion_ui_stop = 0;
  lv_init();
  lv_nuttx_dsc_init(&info);

#ifdef CONFIG_LV_USE_NUTTX_LCD
  info.fb_path = "/dev/lcd0";
#endif

#ifdef CONFIG_INPUT_TOUCHSCREEN
  info.input_path = "/dev/input0";
#endif

  lv_nuttx_init(&info, &result);
  if (result.disp == NULL)
    {
      fprintf(stderr, "velamotion_ui: failed to initialize /dev/lcd0\n");
      ret = 1;
      goto out_lvgl;
    }

  if (velamotion_ui_init() < 0)
    {
      fprintf(stderr, "velamotion_ui: failed to create UI\n");
      ret = 1;
      goto out_port;
    }

  velamotion_ui_demo_model_init();
  printf("VelaMotion LVGL UI started (Ctrl+C to stop)\n");

  while (!g_velamotion_ui_stop)
    {
      uint32_t idle = lv_timer_handler();
      idle = idle == 0 ? 1 : idle;
      if (idle > 20)
        {
          idle = 20;
        }

      usleep(idle * 1000);
    }

  velamotion_ui_destroy();

out_port:
  lv_nuttx_deinit(&result);
out_lvgl:
  lv_deinit();
  printf("VelaMotion LVGL UI stopped\n");
  return ret;
}
