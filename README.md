# VoiceMeeter Tray Control

Tray application to control Voicemeeter parameters. Synchronizes Windows volume/mute controls to VoiceMeeter, making keyboard volume keys, headset controls etc. work at adjusting VoiceMeeter controls.

## Installation

1. Download latest version from [releases](https://github.com/Maickeli/voicemeeter_tray_control/releases/).
2. Run voicemeeter_tray_control.exe 

## Building

This project is a basic C++ application built using CMake.

### Requirements

* C++ compiler (MSVC)
* CMake

### Build steps

1. **Clone the repository**
    ```bash
    git clone https://github.com/Maickeli/voicemeeter_tray_control.git
    cd voicemeeter_tray_control
    ```

2.  **Compile**
    
    The app can be built like any basic CMake project:
    ```bash
    # Create a build directory and navigate into it
    mkdir build
    cd build

    # Configure the project
    cmake ..

    # Compile the project
    cmake --build .
    ```

## Licensing

This utility (the source code and compiled executable) is licensed under the **MIT License** (see the `LICENSE` file for details).

#### VoiceMeeter Software Licensing

This application controls the VoiceMeeter software and uses its API to function. License for the Voicemeeter software is separate from the license for this utility.
This project is **not** affiliated with VoiceMeeter or VB-Audio Software.
Please refer to the official VB-Audio website for the latest Voicemeeter licensing terms.