# 🐠 Auto Aquarium

[![Maintenance](https://img.shields.io/badge/Maintained%3F-no-red.svg)](https://github.com/aniket-patra/Smart-Aquarium-V1.0)
[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)
[![Arduino](https://img.shields.io/badge/Arduino-00979D?style=flat&logo=Arduino&logoColor=white)](https://www.arduino.cc/)

Automatic control system for aquarium maintenance using Arduino and DS3231 RTC module.

> ⚠️ **CAUTION**: This project involves working with electrical components and may require handling of high voltage connections. Always prioritize safety, use proper insulation, and consult with a qualified electrician if you're unsure about any aspect of the installation or operation.

> 📢 **NOTE**: This project (V2.0) is now closed. For the latest updates and improvements, please check out [Smart Aquarium V3.0](https://github.com/desiFish/Smart-Aquarium-V3.0).

## 🔍 Features
- Automated lighting control
- Scheduled feeding system
- Time-based Aquarium management

## 📁 Project Structure
The project contains three main files:
- `aquaFeeder.ino` - Servo motor based automatic fish feeder
- `aquaLight.ino` - Light timing control system
- `aquaLightFeed.ino` - Combined light and feeder control

## 📚 Dependencies
Required Libraries:
- `servo.h`
- `DS3231.h` ([Download Link](http://www.rinkydinkelectronics.com/library.php?id=73))
- `string.h`
- `stdio.h`

## ❓ Support
For questions or queries, please [open an issue](https://github.com/desiFish/Smart-Aquarium-V1.0/issues).

## 📜 License
This project is licensed under the GNU General Public License v3.0

### License Summary
- You can freely use, modify and distribute this software
- Any modifications must be released under the same license
- You must disclose the source code when distributing
- Changes must be documented
- Include original license and copyright notices