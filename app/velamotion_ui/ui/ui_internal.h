/****************************************************************************
 * app/velamotion_ui/ui/ui_internal.h
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#ifndef VELAMOTION_UI_INTERNAL_H
#define VELAMOTION_UI_INTERNAL_H

#include <lvgl/lvgl.h>

#include "velamotion_ui.h"

#define VM_UI_WIDTH  390
#define VM_UI_HEIGHT 450

#define VM_COLOR_BG       0x071426
#define VM_COLOR_SURFACE  0x10233d
#define VM_COLOR_SURFACE2 0x173252
#define VM_COLOR_PRIMARY  0x27c2ff
#define VM_COLOR_ACCENT   0xff6b8a
#define VM_COLOR_SUCCESS  0x41d6a3
#define VM_COLOR_WARNING  0xffba49
#define VM_COLOR_TEXT     0xf4f8ff
#define VM_COLOR_MUTED    0x91a8c5

enum vm_ui_page_e
{
  VM_UI_PAGE_CLOCK = 0,
  VM_UI_PAGE_WIFI,
  VM_UI_PAGE_CHAT,
  VM_UI_PAGE_HEART,
  VM_UI_PAGE_WEATHER,
  VM_UI_PAGE_ALARM,
  VM_UI_PAGE_COUNT
};

struct vm_ui_context_s
{
  lv_obj_t *splash;
  lv_obj_t *screens[VM_UI_PAGE_COUNT];
  lv_obj_t *overlay;
  lv_obj_t *overlay_title;
  lv_obj_t *overlay_message;
  lv_obj_t *clock_time;
  lv_obj_t *clock_date;
  lv_obj_t *clock_steps;
  lv_obj_t *connection_icon;
  lv_obj_t *connection_name;
  lv_obj_t *connection_state;
  lv_obj_t *chat_orb;
  lv_obj_t *heart_rate;
  lv_obj_t *heart_spo2;
  lv_obj_t *heart_bars[8];
  lv_obj_t *weather_summary;
  lv_obj_t *weather_temp;
  lv_obj_t *weather_humidity;
  lv_obj_t *weather_air;
  lv_obj_t *alarm_rows[4];
  lv_obj_t *alarm_times[4];
  lv_obj_t *alarm_titles[4];
  lv_obj_t *alarm_switches[4];
  lv_timer_t *splash_timer;
  enum vm_ui_page_e active_page;
};

extern struct vm_ui_context_s g_vm_ui;

lv_obj_t *vm_ui_create_base_screen(enum vm_ui_page_e page,
                                   const char *title,
                                   const char *subtitle);
lv_obj_t *vm_ui_create_card(lv_obj_t *parent, int x, int y,
                            int width, int height);
lv_obj_t *vm_ui_create_label(lv_obj_t *parent, const char *text,
                             uint32_t color, lv_text_align_t align);
lv_obj_t *vm_ui_create_button(lv_obj_t *parent, const char *text,
                              int width, int height);
void vm_ui_attach_navigation(lv_obj_t *screen, enum vm_ui_page_e page);
void vm_ui_navigate(enum vm_ui_page_e page);
void vm_ui_start_pulse(lv_obj_t *object, uint16_t minimum,
                       uint16_t maximum, uint32_t duration);

void vm_ui_create_clock_screen(void);
void vm_ui_create_wifi_screen(void);
void vm_ui_create_chat_screen(void);
void vm_ui_create_heart_screen(void);
void vm_ui_create_weather_screen(void);
void vm_ui_create_alarm_screen(void);
void vm_ui_create_overlay(void);

#endif
