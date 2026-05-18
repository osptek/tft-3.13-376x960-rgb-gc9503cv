# 3.13" 376×960 TFT RGB module (GC9503) — documentation & samples

**简体中文：** [`README.md`](README.md)

---

> This repository provides **sample projects** for this module, together with datasheets, specifications, and interface / bring-up documentation for selection reference and integration.

## Product overview

| Item | Description |
|:--|:--|
| Module | 3.13-inch **TFT** panel, **376×960** resolution |
| Interface | **RGB** |
| Driver IC | **GC9503** |
| Spec ID | **`3.13-tft-376x960-rgb-gc9503`** is the common product designation in documentation |

---

## Repository layout

### Top-level

| Path | Contents |
|:--|:--|
| `docs/` | Datasheets, specifications, initialization documentation |
| `examples/` | **Sample projects** |

### `examples/` layout

| Location | Description (internal package folder) |
|:--|:--|
| `examples/` root | **IDF代码** (RGB + LVGL adapter) |

### Sample project paths

| Description | Path |
|:--|:--|
| GC9503 RGB + LVGL adapter | `examples/esp32s3_gc9503_lvgl_adapter/` |
