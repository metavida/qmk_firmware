# BDN9

![BDN9](https://cdn.shopify.com/s/files/1/1851/5125/products/image_bd8d9423-950e-4aad-bea5-665d896f879a_530x@2x.jpg?v=1547909493)

A 3x3 macropad with support for up to 3 rotary encoders.


* Rev. 1.0-1.2 encoder locations: Top Right, Top Left
* Rev. 1.3 encoder locations: Top Right, Top Middle, Top Left
* Rev. 2 encoder locations: Top Right, Top Middle, Top Left


**Keyboard Maintainer:** [Bakingpy/nooges](https://github.com/nooges)

**Hardware Supported:**
* Rev. 1: Pro Micro, Elite-C, Proton C
* Rev. 2: Integrated STM32F072 microcontroller

**Hardware Availability:**
* [Keebio - BDN9 Rev. 1](https://keeb.io/products/bdn9-3x3-9-key-macropad-rotary-encoder-support)
* [Keebio - BDN9 Rev. 2](https://keeb.io/products/bdn9-rev-2-3x3-9-key-macropad-rotary-encoder-and-rgb)

Make examples for this keyboard (after setting up your build environment), select the appropriate line for your PCB revision:

    make keebio/bdn9/rev1:default
    make keebio/bdn9/rev2:default

See the [build environment setup](https://docs.qmk.fm/#/getting_started_build_tools) and the [make instructions](https://docs.qmk.fm/#/getting_started_make_guide) for more information. Brand new to QMK? Start with our [Complete Newbs Guide](https://docs.qmk.fm/#/newbs).

## TL;DR: Mac Make Instructions

### Prerequisites

1. ```bash
   brew install qmk/qmk/qmk
   ```
1. ```bash
   git clone --recurse-submodules git@github.com:metavida/qmk_firmware.git
   ```
1. ```bash
   qmk setup metavida/qmk_firmware
   ```
1. Create a keymap:
   ```bash
   keyboards/keebio/bdn9/keymaps/default keyboards/keebio/bdn9/keymaps/metavida
   ```

### Compile & Flash Keymap

1. ```bash
   qmk compile -kb keebio/bdn9/rev1 -km metavida
   ```
1. Launch the QMK Toolbox app
1. Open the `/Users/marcoswk/workspace/qmk_firmware/.build/keebio_bdn9_rev1_metavida.hex` file
1. Plug in the BDN9 keyboard. Console should read: "HID console connected: Keebio BDN9 Rev. 1"
1. Hold the reset button for 1 second, then let go. Console should read: "Caterina device connected: Arduino LLC Arduino Micro"
1. Click the "Flash" button.
1. Enjoy the new keymap!
