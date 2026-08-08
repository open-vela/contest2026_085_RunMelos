/****************************************************************************
 * app/velamotion_ui/ui/velamotion_ui.h
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#ifndef VELAMOTION_UI_H
#define VELAMOTION_UI_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum velamotion_connection_e
{
  VELAMOTION_CONNECTION_WIFI = 0,
  VELAMOTION_CONNECTION_BLUETOOTH
};

enum velamotion_overlay_e
{
  VELAMOTION_OVERLAY_SEARCH = 0,
  VELAMOTION_OVERLAY_ALARM,
  VELAMOTION_OVERLAY_DANGER,
  VELAMOTION_OVERLAY_DOORBELL
};

struct velamotion_alarm_s
{
  const char *time;
  const char *title;
  bool enabled;
};

int velamotion_ui_init(void);
void velamotion_ui_destroy(void);

void velamotion_ui_set_time(const char *time_text,
                            const char *date_text,
                            unsigned int steps);
void velamotion_ui_set_connection(enum velamotion_connection_e type,
                                  const char *name, bool connected);
void velamotion_ui_set_health(unsigned int heart_rate,
                              unsigned int spo2,
                              const uint8_t *history,
                              size_t history_count);
void velamotion_ui_set_weather(const char *summary,
                               int temperature,
                               unsigned int humidity,
                               unsigned int air_quality);
void velamotion_ui_set_alarms(const struct velamotion_alarm_s *alarms,
                              size_t count);
void velamotion_ui_show_overlay(enum velamotion_overlay_e type,
                                const char *message);

void velamotion_ui_demo_model_init(void);
void velamotion_ui_demo_model_deinit(void);

#endif
