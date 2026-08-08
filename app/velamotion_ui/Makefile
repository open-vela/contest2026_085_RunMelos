############################################################################
# VelaMotion LVGL application
############################################################################

include $(APPDIR)/Make.defs

PROGNAME  = velamotion_ui
PRIORITY  = SCHED_PRIORITY_DEFAULT
STACKSIZE = 32768
MODULE    = $(CONFIG_VELAMOTION_UI)

MAINSRC = velamotion_ui_main.c
CSRCS += port/velamotion_ui_demo.c
CSRCS += ui/velamotion_ui.c
CSRCS += ui/components/ui_components.c
CSRCS += ui/screens/ui_screens.c
CSRCS += ui/overlays/ui_overlays.c

include $(APPDIR)/Application.mk
