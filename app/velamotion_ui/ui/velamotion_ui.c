/****************************************************************************
 * app/velamotion_ui/ui/velamotion_ui.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "ui_internal.h"

struct vm_ui_context_s g_vm_ui;

static void vm_ui_splash_timeout(lv_timer_t *timer)
{
  g_vm_ui.splash_timer = NULL;
  lv_timer_delete(timer);
  vm_ui_navigate(VM_UI_PAGE_CLOCK);
}

static void vm_ui_navigation_event(lv_event_t *event)
{
  enum vm_ui_page_e page =
    (enum vm_ui_page_e)(uintptr_t)lv_event_get_user_data(event);
  lv_indev_t *indev;
  lv_dir_t direction;

  if (lv_event_get_code(event) != LV_EVENT_GESTURE)
    {
      return;
    }

  indev = lv_indev_active();
  if (indev == NULL)
    {
      return;
    }

  direction = lv_indev_get_gesture_dir(indev);
  lv_indev_wait_release(indev);

  if (direction == LV_DIR_LEFT)
    {
      page = (enum vm_ui_page_e)((page + 1) % VM_UI_PAGE_COUNT);
      vm_ui_navigate(page);
    }
  else if (direction == LV_DIR_RIGHT)
    {
      page = (enum vm_ui_page_e)((page + VM_UI_PAGE_COUNT - 1) %
                                 VM_UI_PAGE_COUNT);
      vm_ui_navigate(page);
    }
}

static void vm_ui_anim_opacity(void *object, int32_t value)
{
  lv_obj_set_style_opa((lv_obj_t *)object, value, LV_PART_MAIN);
}

static void vm_ui_overlay_close_event(lv_event_t *event)
{
  vm_ui_navigate(g_vm_ui.active_page);
}

void vm_ui_attach_navigation(lv_obj_t *screen, enum vm_ui_page_e page)
{
  lv_obj_add_event_cb(screen, vm_ui_navigation_event,
                      LV_EVENT_GESTURE, (void *)(uintptr_t)page);
}

void vm_ui_navigate(enum vm_ui_page_e page)
{
  if (page >= VM_UI_PAGE_COUNT || g_vm_ui.screens[page] == NULL)
    {
      return;
    }

  g_vm_ui.active_page = page;
  lv_screen_load_anim(g_vm_ui.screens[page], LV_SCR_LOAD_ANIM_FADE_ON,
                      180, 0, false);
}

void vm_ui_start_pulse(lv_obj_t *object, uint16_t minimum,
                       uint16_t maximum, uint32_t duration)
{
  lv_anim_t animation;

  lv_anim_init(&animation);
  lv_anim_set_var(&animation, object);
  lv_anim_set_exec_cb(&animation, vm_ui_anim_opacity);
  lv_anim_set_values(&animation, minimum, maximum);
  lv_anim_set_duration(&animation, duration);
  lv_anim_set_playback_duration(&animation, duration);
  lv_anim_set_repeat_count(&animation, LV_ANIM_REPEAT_INFINITE);
  lv_anim_set_path_cb(&animation, lv_anim_path_ease_in_out);
  lv_anim_start(&animation);
}

static void vm_ui_create_splash(void)
{
  lv_obj_t *logo;
  lv_obj_t *name;
  lv_obj_t *tagline;
  lv_obj_t *bar;

  g_vm_ui.splash = lv_obj_create(NULL);
  lv_obj_remove_flag(g_vm_ui.splash, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(g_vm_ui.splash, lv_color_hex(VM_COLOR_BG), 0);
  lv_obj_set_style_bg_opa(g_vm_ui.splash, LV_OPA_COVER, 0);

  logo = lv_obj_create(g_vm_ui.splash);
  lv_obj_set_size(logo, 112, 112);
  lv_obj_align(logo, LV_ALIGN_CENTER, 0, -55);
  lv_obj_set_style_radius(logo, 32, 0);
  lv_obj_set_style_bg_color(logo, lv_color_hex(VM_COLOR_PRIMARY), 0);
  lv_obj_set_style_bg_opa(logo, LV_OPA_COVER, 0);
  lv_obj_set_style_border_width(logo, 0, 0);
  lv_obj_remove_flag(logo, LV_OBJ_FLAG_SCROLLABLE);

  name = vm_ui_create_label(logo, "VM", VM_COLOR_BG, LV_TEXT_ALIGN_CENTER);
  lv_obj_center(name);

  name = vm_ui_create_label(g_vm_ui.splash, "VELAMOTION",
                            VM_COLOR_TEXT, LV_TEXT_ALIGN_CENTER);
  lv_obj_align(name, LV_ALIGN_CENTER, 0, 28);

  tagline = vm_ui_create_label(g_vm_ui.splash,
                               "SMART GADGET UI  /  OPENVELA",
                               VM_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
  lv_obj_align(tagline, LV_ALIGN_CENTER, 0, 57);

  bar = lv_obj_create(g_vm_ui.splash);
  lv_obj_set_size(bar, 86, 4);
  lv_obj_align(bar, LV_ALIGN_BOTTOM_MID, 0, -72);
  lv_obj_set_style_radius(bar, 4, 0);
  lv_obj_set_style_bg_color(bar, lv_color_hex(VM_COLOR_PRIMARY), 0);
  lv_obj_set_style_border_width(bar, 0, 0);
  vm_ui_start_pulse(bar, 48, 255, 500);
}

int velamotion_ui_init(void)
{
  memset(&g_vm_ui, 0, sizeof(g_vm_ui));

  vm_ui_create_splash();
  vm_ui_create_clock_screen();
  vm_ui_create_wifi_screen();
  vm_ui_create_chat_screen();
  vm_ui_create_heart_screen();
  vm_ui_create_weather_screen();
  vm_ui_create_alarm_screen();
  vm_ui_create_overlay();

  g_vm_ui.active_page = VM_UI_PAGE_CLOCK;
  lv_screen_load(g_vm_ui.splash);
  g_vm_ui.splash_timer = lv_timer_create(vm_ui_splash_timeout, 1400, NULL);
  return 0;
}

void velamotion_ui_destroy(void)
{
  int i;

  velamotion_ui_demo_model_deinit();
  if (g_vm_ui.splash_timer != NULL)
    {
      lv_timer_delete(g_vm_ui.splash_timer);
      g_vm_ui.splash_timer = NULL;
    }

  if (g_vm_ui.overlay != NULL)
    {
      lv_obj_delete(g_vm_ui.overlay);
    }

  for (i = 0; i < VM_UI_PAGE_COUNT; i++)
    {
      if (g_vm_ui.screens[i] != NULL)
        {
          lv_obj_delete(g_vm_ui.screens[i]);
        }
    }

  if (g_vm_ui.splash != NULL)
    {
      lv_obj_delete(g_vm_ui.splash);
    }

  memset(&g_vm_ui, 0, sizeof(g_vm_ui));
}

void velamotion_ui_set_time(const char *time_text,
                            const char *date_text,
                            unsigned int steps)
{
  if (g_vm_ui.clock_time != NULL && time_text != NULL)
    {
      lv_label_set_text(g_vm_ui.clock_time, time_text);
    }

  if (g_vm_ui.clock_date != NULL && date_text != NULL)
    {
      lv_label_set_text(g_vm_ui.clock_date, date_text);
    }

  if (g_vm_ui.clock_steps != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.clock_steps, "%u STEPS", steps);
    }
}

void velamotion_ui_set_connection(enum velamotion_connection_e type,
                                  const char *name, bool connected)
{
  const char *icon = type == VELAMOTION_CONNECTION_WIFI ?
                     LV_SYMBOL_WIFI : "BT";

  if (g_vm_ui.connection_icon != NULL)
    {
      lv_label_set_text(g_vm_ui.connection_icon, icon);
    }

  if (g_vm_ui.connection_name != NULL)
    {
      lv_label_set_text(g_vm_ui.connection_name,
                        name == NULL ? "No saved network" : name);
    }

  if (g_vm_ui.connection_state != NULL)
    {
      lv_label_set_text(g_vm_ui.connection_state,
                        connected ? "CONNECTED" : "NOT CONNECTED");
      lv_obj_set_style_text_color(g_vm_ui.connection_state,
          lv_color_hex(connected ? VM_COLOR_SUCCESS : VM_COLOR_WARNING), 0);
    }
}

void velamotion_ui_set_health(unsigned int heart_rate,
                              unsigned int spo2,
                              const uint8_t *history,
                              size_t history_count)
{
  size_t i;

  if (history == NULL)
    {
      history_count = 0;
    }

  if (g_vm_ui.heart_rate != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.heart_rate, "%u BPM", heart_rate);
    }

  if (g_vm_ui.heart_spo2 != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.heart_spo2, "SpO2  %u%%", spo2);
    }

  for (i = 0; i < 8 && i < history_count; i++)
    {
      int height = 18 + ((int)history[i] - 55) * 2;
      if (height < 18)
        {
          height = 18;
        }
      else if (height > 92)
        {
          height = 92;
        }

      lv_obj_set_height(g_vm_ui.heart_bars[i], height);
      lv_obj_align(g_vm_ui.heart_bars[i], LV_ALIGN_BOTTOM_LEFT,
                   18 + (int)i * 29, -15);
    }
}

void velamotion_ui_set_weather(const char *summary,
                               int temperature,
                               unsigned int humidity,
                               unsigned int air_quality)
{
  if (g_vm_ui.weather_summary != NULL && summary != NULL)
    {
      lv_label_set_text(g_vm_ui.weather_summary, summary);
    }

  if (g_vm_ui.weather_temp != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.weather_temp, "%d C", temperature);
    }

  if (g_vm_ui.weather_humidity != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.weather_humidity,
                            "HUMIDITY  %u%%", humidity);
    }

  if (g_vm_ui.weather_air != NULL)
    {
      lv_label_set_text_fmt(g_vm_ui.weather_air,
                            "AIR QUALITY  %u", air_quality);
    }
}

void velamotion_ui_set_alarms(const struct velamotion_alarm_s *alarms,
                              size_t count)
{
  size_t i;

  for (i = 0; i < 4; i++)
    {
      bool visible = alarms != NULL && i < count;
      if (!visible)
        {
          lv_obj_add_flag(g_vm_ui.alarm_rows[i], LV_OBJ_FLAG_HIDDEN);
          continue;
        }

      lv_obj_remove_flag(g_vm_ui.alarm_rows[i], LV_OBJ_FLAG_HIDDEN);
      lv_label_set_text(g_vm_ui.alarm_times[i],
                        alarms[i].time == NULL ? "--:--" : alarms[i].time);
      lv_label_set_text(g_vm_ui.alarm_titles[i],
                        alarms[i].title == NULL ? "Reminder" :
                                                 alarms[i].title);
      if (alarms[i].enabled)
        {
          lv_obj_add_state(g_vm_ui.alarm_switches[i], LV_STATE_CHECKED);
        }
      else
        {
          lv_obj_remove_state(g_vm_ui.alarm_switches[i], LV_STATE_CHECKED);
        }
    }
}

void velamotion_ui_show_overlay(enum velamotion_overlay_e type,
                                const char *message)
{
  static const char *titles[] =
  {
    "SEARCHING",
    "ALARM",
    "DANGER",
    "DOORBELL"
  };

  if (type > VELAMOTION_OVERLAY_DOORBELL || g_vm_ui.overlay == NULL)
    {
      return;
    }

  lv_label_set_text(g_vm_ui.overlay_title, titles[type]);
  lv_label_set_text(g_vm_ui.overlay_message,
                    message == NULL ? "Demo notification" : message);
  lv_screen_load_anim(g_vm_ui.overlay, LV_SCR_LOAD_ANIM_FADE_ON,
                      160, 0, false);
}

void vm_ui_overlay_bind_close(lv_obj_t *button)
{
  lv_obj_add_event_cb(button, vm_ui_overlay_close_event,
                      LV_EVENT_CLICKED, NULL);
}
