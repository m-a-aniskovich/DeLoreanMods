# Delorean 1:8 Scale Model Modification

This repository contains the PCB designs and firmware for a modification to the Delorean 1:8 Scale model. The files are organized into the following folders:

- **DeLoreanModsPCB**: Contains the design files for the printed circuit board (PCB) used in the modification
- **firmware**: Contains the Arduino firmware for controlling the various features of the modification
- **gerbers**: Contains the gerber files for the PCB, which can be used for manufacturing the board

## Getting Started
For ATTiny85 you will need [AttinyCore library](https://github.com/SpenceKonde/ATTinyCore) and for ATTiny13A - [MicroCore library](https://github.com/MCUdude/MicroCore). 
1. Clone the repository to your local machine
2. Open the gerbers folder, send the gerbers to PCB Manufacturer to get the PCB manufactured.
3. Open the firmware folder and upload the sketch to your board. 
4. Assemble the PCB and connect it to Delorean.

## Prerequisites

- Arduino IDE
- SPI programmer
- Altium PCB Design software
- Soldering skills

## Contributing

We welcome contributions to this repository. If you would like to contribute, please fork the repository and submit a pull request.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE.md](LICENSE.md) file for details.
