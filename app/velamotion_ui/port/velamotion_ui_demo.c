/****************************************************************************
 * app/velamotion_ui/port/velamotion_ui_demo.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include <stdio.h>
#include <time.h>

#include <lvgl/lvgl.h>

#include "../ui/velamotion_ui.h"

static lv_timer_t *g_demo_timer;
static unsigned int g_demo_tick;

static void velamotion_ui_demo_update(lv_timer_t *timer)
{
  static const struct velamotion_alarm_s alarms[] =
  {
    {"08:30", "Morning medicine", true},
    {"12:10", "Lunch reminder", true},
    {"18:45", "Evening walk", false}
  };
  uint8_t history[8];
  char time_text[8];
  char date_text[24];
  struct tm local;
  time_t now;
  unsigned int i;

  now = time(NULL);
  if (localtime_r(&now, &local) != NULL)
    {
      strftime(time_text, sizeof(time_text), "%H:%M", &local);
      strftime(date_text, sizeof(date_text), "%a  %b %d", &local);
    }
  else
    {
      snprintf(time_text, sizeof(time_text), "09:25");
      snprintf(date_text, sizeof(date_text), "SAT  AUG 08");
    }

  for (i = 0; i < 8; i++)
    {
      history[i] = 66 + ((g_demo_tick + i * 3) % 13);
    }

  velamotion_ui_set_time(time_text, date_text, 1286 + g_demo_tick / 4);
  velamotion_ui_set_health(70 + (g_demo_tick % 7), 98,
                           history, sizeof(history));
  velamotion_ui_set_weather("Comfortable outside", 24,
                            63, 32);
  velamotion_ui_set_alarms(alarms, sizeof(alarms) / sizeof(alarms[0]));
  g_demo_tick++;
}

void velamotion_ui_demo_model_init(void)
{
  if (g_demo_timer != NULL)
    {
      return;
    }

  g_demo_tick = 0;
  velamotion_ui_demo_update(NULL);
  g_demo_timer = lv_timer_create(velamotion_ui_demo_update, 1000, NULL);
}

void velamotion_ui_demo_model_deinit(void)
{
  if (g_demo_timer != NULL)
    {
      lv_timer_delete(g_demo_timer);
      g_demo_timer = NULL;
    }
}
