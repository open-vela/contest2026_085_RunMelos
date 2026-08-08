# UI assets

The first openvela port deliberately uses LVGL primitives and built-in symbols.
The original ESPWatch raster assets and EAF files are not copied, which keeps
the firmware small and avoids importing assets without an explicit license.

Future project-owned images can be converted to LVGL 9 RGB565 C arrays and
registered explicitly in the application build files.
