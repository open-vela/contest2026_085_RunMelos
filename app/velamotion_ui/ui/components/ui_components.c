/****************************************************************************
 * app/velamotion_ui/ui/components/ui_components.c
 *
 * SPDX-License-Identifier: Apache-2.0
 ****************************************************************************/

#include "../ui_internal.h"

lv_obj_t *vm_ui_create_label(lv_obj_t *parent, const char *text,
                             uint32_t color, lv_text_align_t align)
{
  lv_obj_t *label = lv_label_create(parent);
  lv_label_set_text(label, text);
  lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
  lv_obj_set_style_text_color(label, lv_color_hex(color), 0);
  lv_obj_set_style_text_align(label, align, 0);
  return label;
}

lv_obj_t *vm_ui_create_card(lv_obj_t *parent, int x, int y,
                            int width, int height)
{
  lv_obj_t *card = lv_obj_create(parent);
  lv_obj_set_size(card, width, height);
  lv_obj_set_pos(card, x, y);
  lv_obj_set_style_radius(card, 22, 0);
  lv_obj_set_style_bg_color(card, lv_color_hex(VM_COLOR_SURFACE), 0);
  lv_obj_set_style_bg_opa(card, LV_OPA_COVER, 0);
  lv_obj_set_style_border_color(card, lv_color_hex(VM_COLOR_SURFACE2), 0);
  lv_obj_set_style_border_width(card, 1, 0);
  lv_obj_set_style_pad_all(card, 16, 0);
  lv_obj_remove_flag(card, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_add_flag(card, LV_OBJ_FLAG_GESTURE_BUBBLE);
  return card;
}

lv_obj_t *vm_ui_create_button(lv_obj_t *parent, const char *text,
                              int width, int height)
{
  lv_obj_t *button = lv_button_create(parent);
  lv_obj_t *label;

  lv_obj_set_size(button, width, height);
  lv_obj_set_style_radius(button, height / 2, 0);
  lv_obj_set_style_bg_color(button, lv_color_hex(VM_COLOR_PRIMARY), 0);
  lv_obj_set_style_shadow_width(button, 0, 0);
  lv_obj_add_flag(button, LV_OBJ_FLAG_GESTURE_BUBBLE);

  label = vm_ui_create_label(button, text, VM_COLOR_BG,
                             LV_TEXT_ALIGN_CENTER);
  lv_obj_center(label);
  return button;
}

lv_obj_t *vm_ui_create_base_screen(enum vm_ui_page_e page,
                                   const char *title,
                                   const char *subtitle)
{
  lv_obj_t *screen;
  lv_obj_t *label;
  lv_obj_t *dots;
  int i;

  screen = lv_obj_create(NULL);
  lv_obj_remove_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
  lv_obj_set_style_bg_color(screen, lv_color_hex(VM_COLOR_BG), 0);
  lv_obj_set_style_bg_opa(screen, LV_OPA_COVER, 0);

  label = vm_ui_create_label(screen, title, VM_COLOR_TEXT,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_set_width(label, 260);
  lv_obj_set_pos(label, 24, 22);

  label = vm_ui_create_label(screen, subtitle, VM_COLOR_MUTED,
                             LV_TEXT_ALIGN_LEFT);
  lv_obj_set_width(label, 330);
  lv_obj_set_pos(label, 24, 48);

  dots = lv_obj_create(screen);
  lv_obj_set_size(dots, 142, 18);
  lv_obj_align(dots, LV_ALIGN_BOTTOM_MID, 0, -14);
  lv_obj_set_style_bg_opa(dots, LV_OPA_TRANSP, 0);
  lv_obj_set_style_border_width(dots, 0, 0);
  lv_obj_set_style_pad_all(dots, 0, 0);
  lv_obj_remove_flag(dots, LV_OBJ_FLAG_SCROLLABLE);

  for (i = 0; i < VM_UI_PAGE_COUNT; i++)
    {
      lv_obj_t *dot = lv_obj_create(dots);
      lv_obj_set_size(dot, i == page ? 18 : 8, 8);
      lv_obj_set_pos(dot, 8 + i * 22, 5);
      lv_obj_set_style_radius(dot, 8, 0);
      lv_obj_set_style_border_width(dot, 0, 0);
      lv_obj_set_style_bg_color(dot,
        lv_color_hex(i == page ? VM_COLOR_PRIMARY : VM_COLOR_MUTED), 0);
      lv_obj_remove_flag(dot, LV_OBJ_FLAG_SCROLLABLE);
    }

  vm_ui_attach_navigation(screen, page);
  g_vm_ui.screens[page] = screen;
  return screen;
}
