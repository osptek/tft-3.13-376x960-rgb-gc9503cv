<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 3.13″ TFT 376×960（GC9503CV · RGB）</h1>

<p align="center"><b>条形 TFT 模组 · RGB · GC9503CV</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文</p>

<p align="center">
  <img alt="Size: 3.13 inch" src="https://img.shields.io/badge/Size-3.13%22-3498DB?style=flat-square" />
  <img alt="Resolution: 376x960" src="https://img.shields.io/badge/Resolution-376%C3%97960-8E44AD?style=flat-square" />
  <img alt="Interface: RGB" src="https://img.shields.io/badge/Interface-RGB-27AE60?style=flat-square" />
  <img alt="Driver: GC9503CV" src="https://img.shields.io/badge/Driver-GC9503CV-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 3.13 寸 376×960 TFT RGB 模组（GC9503CV）产品图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **3.13 寸 376×960 TFT** 是一款 **RGB** 接口彩色显示模组，驱动芯片为 **GC9503CV**。细长分辨率适合条形 HMI、侧边状态条、竖向信息面板等场景。

规格标识（仓库名）：`3.13-tft-376x960-rgb-gc9503cv`

当前模组版本：**YDP313B002-V1**。电气与外形细节以 [`docs/YDP_313_B002_V1_1a0ff66f58.pdf`](./docs/YDP_313_B002_V1_1a0ff66f58.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 3.13 英寸 |
| 类型 | TFT（彩色） |
| 分辨率 | 376×960 |
| 接口 | RGB |
| 驱动 IC | GC9503CV |

> 完整外形尺寸、FPC 定义、供电与时序以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-S3 · GC9503CV RGB + LVGL adapter | [`examples/esp32s3_gc9503_lvgl_adapter/`](./examples/esp32s3_gc9503_lvgl_adapter/) |

## 仓库结构

```text
3.13-tft-376x960-rgb-gc9503cv/
├── README.md
├── README_EN.md
├── MODULE_VERSION.md
├── LICENSE
├── images/          # README 用图
├── docs/            # 规格书、驱动手册、初始化等
└── examples/        # 示例工程
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 产品规格书（YDP313B002-V1） | [`docs/YDP_313_B002_V1_1a0ff66f58.pdf`](./docs/YDP_313_B002_V1_1a0ff66f58.pdf) |
| 驱动 IC 数据手册（GC9503CV） | [`docs/GC_9503_CV_Data_Sheet_V1_0_1_bf6521995e.pdf`](./docs/GC_9503_CV_Data_Sheet_V1_0_1_bf6521995e.pdf) |
| 初始化序列（文本） | [`docs/GC9503CV_BOE3.13IPS(QV032DEQ-N80)_20220106_AN_V1.txt`](./docs/GC9503CV_BOE3.13IPS(QV032DEQ-N80)_20220106_AN_V1.txt) |

### 示例工程

- [ESP32-S3 GC9503CV RGB + LVGL adapter](./examples/esp32s3_gc9503_lvgl_adapter/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-FF6A00?style=for-the-badge" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>
- 有任何问题，都可以在本仓库 Issues 中提问

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
