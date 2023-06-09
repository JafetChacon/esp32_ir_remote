| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

# IR REMOTE CONTROLLER

This project is for a Infrared NEC Emiter, It needs to be programed what commands gonna send.
This uses RMT to send IR commands, and a 7 segments display to show wich command is being sent.
All inputs have its internal pullup resistors activated, so the pin is activated by a LOW level.
This project was built by command `idf.py create-project`.


## INPUT / OUTPUTS
| -------- | --------- | --------- | --------- | --------- | --------- | --------- |
| INPUTS   | Button 1  | Button 2  | Button 3  | Button 4  | Button 5  | Button 6  |
| -------- | --------- | --------- | --------- | --------- | --------- | --------- |
| ADDRESS  | D13       | D12       | D14       | D27       | D26       | D25       |
| -------- | --------- | --------- | --------- | --------- | --------- | --------- |

| -------- | --------- | --------- | --------- | --------- | --------- | --------- | ------ |
| OUTPUTS  | DispSeg_A | DispSeg_B | DispSeg_C | DispSeg_D | DispSeg_E | DispSeg_F | IR LED |
| -------- | --------- | --------- | --------- | --------- | --------- | --------- | ------ |
| ADDRESS  | D21       | D19       | D05       | D04       | D02       | D22       | D18    |
| -------- | --------- | --------- | --------- | --------- | --------- | --------- | ------ |

## Folder contents

The project contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.
