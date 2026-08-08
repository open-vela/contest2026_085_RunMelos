/****************************************************************************
 * app/velamotion_ui/ui/overlays/ui_overlays.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include "../ui_internal.h"

extern void vm_ui_overlay_bind_close(lv_obj_t *button);

void vm_ui_create_overlay(void)
{
  lv_obj_t *panel;
  lv_obj_t *indicator;
  lv_obj_t *button;

  g_vm_ui.overlay = lv_obj_create(NULL);
  lv_obj_remove_flag(g_vm_ui.overlay, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(g_vm_ui.overlay, lv_color_hex(VM_COLOR_BG), 0);
  lv_obj_set_style_bg_opa(g_vm_ui.overlay, LV_OPA_COVER, 0);

  panel = vm_ui_create_card(g_vm_ui.overlay, 24, 55, 342, 330);
  lv_obj_set_style_border_color(panel, lv_color_hex(VM_COLOR_PRIMARY), 0);

  indicator = lv_obj_create(panel);
  lv_obj_set_size(indicator, 112, 112);
  lv_obj_align(indicator, LV_ALIGN_TOP_MID, 0, 24);
  lv_obj_set_style_radius(indicator, LV_RADIUS_CIRCLE, 0);
  lv_obj_set_style_border_width(indicator, 3, 0);
  lv_obj_set_style_border_color(indicator,
                                lv_color_hex(VM_COLOR_PRIMARY), 0);
  lv_obj_set_style_bg_color(indicator,
                            lv_color_hex(VM_COLOR_SURFACE2), 0);
  lv_obj_remove_flag(indicator, LV_OBJ_FLAG_SCROLLABLE);
  vm_ui_start_pulse(indicator, 60, 255, 600);

  g_vm_ui.overlay_title = vm_ui_create_label(panel, "SEARCHING",
                                             VM_COLOR_TEXT,
                                             LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.overlay_title, 290);
  lv_obj_align(g_vm_ui.overlay_title, LV_ALIGN_CENTER, 0, 32);

  g_vm_ui.overlay_message = vm_ui_create_label(panel,
                                               "Demo notification",
                                               VM_COLOR_MUTED,
                                               LV_TEXT_ALIGN_CENTER);
  lv_obj_set_width(g_vm_ui.overlay_message, 280);
  lv_obj_align(g_vm_ui.overlay_message, LV_ALIGN_CENTER, 0, 68);

  button = vm_ui_create_button(panel, "SAFE / CLOSE", 200, 48);
  lv_obj_align(button, LV_ALIGN_BOTTOM_MID, 0, -8);
  vm_ui_overlay_bind_close(button);
}
