# UI fonts

The initial port uses the configured LVGL default font. This avoids the 2.3 MB
full Chinese font from ESPWatch. When Chinese copy is finalized, generate a
small glyph subset containing only the strings used by VelaMotion.
