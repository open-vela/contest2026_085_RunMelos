# VelaMotion LVGL application

if(CONFIG_VELAMOTION_UI)
  nuttx_add_application(
    NAME velamotion_ui
    SRCS
      velamotion_ui_main.c
      port/velamotion_ui_demo.c
      ui/velamotion_ui.c
      ui/components/ui_components.c
      ui/screens/ui_screens.c
      ui/overlays/ui_overlays.c
    STACKSIZE 32768)
endif()
