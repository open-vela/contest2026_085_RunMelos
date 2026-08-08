/****************************************************************************
 * app/velamotion_ui/ui/screens/ui_screens.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include "../ui_internal.h"

static void vm_ui_wifi_button_event(lv_event_t *event)
{
  static bool connected;
  connected = !connected;
  velamotion_ui_set_connection(VELAMOTION_CONNECTION_WIFI,
                               connected ? "VelaMotion Demo" :
                                           "Tap to connect",
                               connected);
}

static void vm_ui_search_button_event(lv_event_t *event)
{
  velamotion_ui_show_overlay(VELAMOTION_OVERLAY_SEARCH,
                             "Listening for your request...");
}

static void vm_ui_danger_button_event(lv_event_t *event)
{
  velamotion_ui_show_overlay(VELAMOTION_OVERLAY_DANGER,
                             "Motion alert demo. Tap SAFE to dismiss.");
}

static void vm_ui_alarm_button_event(lv_event_t *event)
{
  velamotion_ui_show_overlay(VELAMOTION_OVERLAY_ALARM,
                             "08:30  Morning medicine");
}

static void vm_ui_doorbell_button_event(lv_event_t *event)
{
  velamotion_ui_show_overlay(VELAMOTION_OVERLAY_DOORBELL,
                             "Someone is at the front door");
}

void vm_ui_create_clock_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *hero;
  lv_obj_t *label;
  lv_obj_t *card;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_CLOCK,
                                    "SMART CLOCK",
                                    "Swipe left for connectivity");

  hero = vm_ui_create_card(screen, 24, 83, 342, 194);
  lv_obj_set_style_bg_color(hero, lv_color_hex(0x0d3150), 0);

  label = vm_ui_create_label(hero, "LOCAL TIME", VM_COLOR_PRIMARY,
                             LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(label, 300);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

  g_vm_ui.clock_time = vm_ui_create_label(hero, "09:25", VM_COLOR_TEXT,
                                          LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.clock_time, 300);
  lv_obj_align(g_vm_ui.clock_time, LV_ALIGN_CENTER, 0, -12);

  g_vm_ui.clock_date = vm_ui_create_label(hero, "SAT  AUG 08",
                                          VM_COLOR_MUTED,
                                          LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.clock_date, 300);
  lv_obj_align(g_vm_ui.clock_date, LV_ALIGN_BOTTOM_MID, 0, -14);

  card = vm_ui_create_card(screen, 24, 294, 164, 100);
  label = vm_ui_create_label(card, LV_SYMBOL_WIFI "  READY",
                             VM_COLOR_SUCCESS, LV_TEXT_ALIGN_LEFT);
  lv_obj_set_width(label, 130);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 2);
  label = vm_ui_create_label(card, "Connectivity", VM_COLOR_MUTED,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, -2);

  card = vm_ui_create_card(screen, 202, 294, 164, 100);
  g_vm_ui.clock_steps = vm_ui_create_label(card, "1,286 STEPS",
                                           VM_COLOR_ACCENT,
                                           LV_TEXT_ALIGN_LEFT);
  lv_obj_set_width(g_vm_ui.clock_steps, 130);
  lv_obj_align(g_vm_ui.clock_steps, LV_ALIGN_TOP_LEFT, 0, 2);
  label = vm_ui_create_label(card, "Activity today", VM_COLOR_MUTED,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, -2);
}

void vm_ui_create_wifi_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *card;
  lv_obj_t *button;
  lv_obj_t *label;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_WIFI,
                                    "WIFI CONNECTION",
                                    "Demo page - networking is not active");

  card = vm_ui_create_card(screen, 24, 83, 342, 236);

  g_vm_ui.connection_icon = vm_ui_create_label(card, LV_SYMBOL_WIFI,
                                               VM_COLOR_PRIMARY,
                                               LV_TEXT_ALIGN_CENTER);
  lv_obj_set_size(g_vm_ui.connection_icon, 72, 40);
  lv_obj_align(g_vm_ui.connection_icon, LV_ALIGN_TOP_MID, 0, 16);
  vm_ui_start_pulse(g_vm_ui.connection_icon, 80, 255, 650);

  g_vm_ui.connection_name = vm_ui_create_label(card, "Tap to connect",
                                               VM_COLOR_TEXT,
                                               LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.connection_name, 290);
  lv_obj_align(g_vm_ui.connection_name, LV_ALIGN_CENTER, 0, -10);

  g_vm_ui.connection_state = vm_ui_create_label(card, "NOT CONNECTED",
                                                VM_COLOR_WARNING,
                                                LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.connection_state, 290);
  lv_obj_align(g_vm_ui.connection_state, LV_ALIGN_CENTER, 0, 22);

  button = vm_ui_create_button(screen, "CONNECT", 210, 52);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -69);
  lv_obj_add_event_cb(button, vm_ui_wifi_button_event,
                      LV_EVENT_CLICKED, NULL);

  label = vm_ui_create_label(screen,
                             "Bluetooth will replace this page later",
                             VM_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(label, 330);
  lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -46);
}

void vm_ui_create_chat_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *card;
  lv_obj_t *button;
  lv_obj_t *label;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_CHAT,
                                    "AI CHAT",
                                    "Voice service preview");

  card = vm_ui_create_card(screen, 24, 83, 342, 245);
  g_vm_ui.chat_orb = lv_obj_create(card);
  lv_obj_set_size(g_vm_ui.chat_orb, 132, 132);
  lv_obj_align(g_vm_ui.chat_orb, LV_ALIGN_CENTER, 0, -25);
  lv_obj_set_style_radius(g_vm_ui.chat_orb, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_border_width(g_vm_ui.chat_orb, 3, 0);
  lv_obj_set_style_border_color(g_vm_ui.chat_orb,
                                lv_color_hex(VM_COLOR_PRIMARY), 0);
  lv_obj_set_style_bg_color(g_vm_ui.chat_orb,
                            lv_color_hex(VM_COLOR_SURFACE2), 0);
  lv_obj_remove_flag(g_vm_ui.chat_orb, LV_OBJ_FLAG_SCROLLABLE);
  vm_ui_start_pulse(g_vm_ui.chat_orb, 110, 255, 850);

  label = vm_ui_create_label(g_vm_ui.chat_orb, "AI", VM_COLOR_TEXT,
                             LV_TEXT_ALIGN_CENTER);
  lv_obj_center(label);

  label = vm_ui_create_label(card, "Ready to listen",
                             VM_COLOR_MUTED, LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(label, 280);
  lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -7);

  button = vm_ui_create_button(screen, LV_SYMBOL_AUDIO "  TALK", 180, 52);
  lv_obj_align(button, LV_ALIGN_BOTTOM_LEFT, 24, -68);
  lv_obj_add_event_cb(button, vm_ui_search_button_event,
                      LV_EVENT_CLICKED, NULL);

  button = vm_ui_create_button(screen, "DOOR", 126, 52);
  lv_obj_align(button, LV_ALIGN_BOTTOM_RIGHT, -24, -68);
  lv_obj_set_style_bg_color(button, lv_color_hex(VM_COLOR_SURFACE2), 0);
  lv_obj_add_event_cb(button, vm_ui_doorbell_button_event,
                      LV_EVENT_CLICKED, NULL);
}

void vm_ui_create_heart_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *chart;
  lv_obj_t *card;
  lv_obj_t *button;
  lv_obj_t *label;
  int i;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_HEART,
                                    "HEART DETECTION",
                                    "Simulated health measurements");

  chart = vm_ui_create_card(screen, 24, 83, 342, 174);
  label = vm_ui_create_label(chart, "LIVE TREND", VM_COLOR_MUTED,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_align(label, LV_ALIGN_TOP_LEFT, 0, 0);

  for (i = 0; i < 8; i++)
    {
      g_vm_ui.heart_bars[i] = lv_obj_create(chart);
      lv_obj_set_size(g_vm_ui.heart_bars[i], 15, 35 + i * 4);
      lv_obj_align(g_vm_ui.heart_bars[i], LV_ALIGN_BOTTOM_LEFT,
                   18 + i * 29, -15);
      lv_obj_set_style_radius(g_vm_ui.heart_bars[i], 8, 0);
      lv_obj_set_style_border_width(g_vm_ui.heart_bars[i], 0, 0);
      lv_obj_set_style_bg_color(g_vm_ui.heart_bars[i],
                                lv_color_hex(VM_COLOR_ACCENT), 0);
      lv_obj_remove_flag(g_vm_ui.heart_bars[i], LV_OBJ_FLAG_SCROLLABLE);
    }

  card = vm_ui_create_card(screen, 24, 273, 164, 102);
  g_vm_ui.heart_rate = vm_ui_create_label(card, "72 BPM",
                                          VM_COLOR_ACCENT,
                                          LV_TEXT_ALIGN_LEFT);
  lv_obj_align(g_vm_ui.heart_rate, LV_ALIGN_TOP_LEFT, 0, 5);
  label = vm_ui_create_label(card, "Heart rate", VM_COLOR_MUTED,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_align(label, LV_ALIGN_BOTTOM_LEFT, 0, -5);

  card = vm_ui_create_card(screen, 202, 273, 164, 102);
  g_vm_ui.heart_spo2 = vm_ui_create_label(card, "SpO2  98%",
                                         VM_COLOR_PRIMARY,
                                         LV_TEXT_ALIGN_LEFT);
  lv_obj_align(g_vm_ui.heart_spo2, LV_ALIGN_TOP_LEFT, 0, 5);
  button = vm_ui_create_button(card, "SOS DEMO", 130, 34);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, 2);
  lv_obj_set_style_bg_color(button, lv_color_hex(VM_COLOR_ACCENT), 0);
  lv_obj_add_event_cb(button, vm_ui_danger_button_event,
                      LV_EVENT_CLICKED, NULL);
}

void vm_ui_create_weather_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *card;
  lv_obj_t *button;
  lv_obj_t *label;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_WEATHER,
                                    "WEATHER",
                                    "Offline demonstration data");

  card = vm_ui_create_card(screen, 24, 83, 342, 196);
  label = vm_ui_create_label(card, "PARTLY CLOUDY",
                             VM_COLOR_PRIMARY, LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(label, 300);
  lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 7);

  g_vm_ui.weather_temp = vm_ui_create_label(card, "24 C",
                                            VM_COLOR_TEXT,
                                            LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.weather_temp, 300);
  lv_obj_align(g_vm_ui.weather_temp, LV_ALIGN_CENTER, 0, -14);

  g_vm_ui.weather_summary = vm_ui_create_label(card,
                                               "Comfortable outside",
                                               VM_COLOR_MUTED,
                                               LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.weather_summary, 300);
  lv_obj_align(g_vm_ui.weather_summary, LV_ALIGN_BOTTOM_MID, 0, -8);

  card = vm_ui_create_card(screen, 24, 295, 164, 94);
  g_vm_ui.weather_humidity = vm_ui_create_label(card, "HUMIDITY  63%",
                                                VM_COLOR_PRIMARY,
                                                LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.weather_humidity, 130);
  lv_obj_center(g_vm_ui.weather_humidity);

  card = vm_ui_create_card(screen, 202, 295, 164, 94);
  g_vm_ui.weather_air = vm_ui_create_label(card, "AIR QUALITY  32",
                                           VM_COLOR_SUCCESS,
                                           LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.weather_air, 130);
  lv_obj_center(g_vm_ui.weather_air);

  button = vm_ui_create_button(screen, LV_SYMBOL_REFRESH, 48, 48);
  lv_obj_align(button, LV_ALIGN_TOP_RIGHT, -24, 20);
  lv_obj_add_event_cb(button, vm_ui_search_button_event,
                      LV_EVENT_CLICKED, NULL);
}

void vm_ui_create_alarm_screen(void)
{
  lv_obj_t *screen;
  lv_obj_t *button;
  int i;

  screen = vm_ui_create_base_screen(VM_UI_PAGE_ALARM,
                                    "AI REMINDERS",
                                    "Long-press service will be added later");

  for (i = 0; i < 4; i++)
    {
      lv_obj_t *row = vm_ui_create_card(screen, 24, 82 + i * 70, 342, 60);
      g_vm_ui.alarm_rows[i] = row;

      g_vm_ui.alarm_times[i] = vm_ui_create_label(row, "08:30",
                                                  VM_COLOR_PRIMARY,
                                                  LV_TEXT_ALIGN_LEFT);
      lv_obj_set_width(g_vm_ui.alarm_times[i], 62);
      lv_obj_align(g_vm_ui.alarm_times[i], LV_ALIGN_LEFT_MID, 0, 0);

      g_vm_ui.alarm_titles[i] = vm_ui_create_label(row, "Morning task",
                                                   VM_COLOR_TEXT,
                                                   LV_TEXT_ALIGN_LEFT);
      lv_obj_set_width(g_vm_ui.alarm_titles[i], 160);
      lv_obj_align(g_vm_ui.alarm_titles[i], LV_ALIGN_LEFT_MID, 72, 0);

      g_vm_ui.alarm_switches[i] = lv_switch_create(row);
      lv_obj_set_size(g_vm_ui.alarm_switches[i], 48, 26);
      lv_obj_align(g_vm_ui.alarm_switches[i], LV_ALIGN_RIGHT_MID, 0, 0);
    }

  button = vm_ui_create_button(screen, LV_SYMBOL_BELL "  TEST", 150, 46);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -49);
  lv_obj_add_event_cb(button, vm_ui_alarm_button_event,
                      LV_EVENT_CLICKED, NULL);
}
