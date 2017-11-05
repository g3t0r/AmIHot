# AmIHot 1.0.0


This is a program to monitor the temperature of the PC and display it to the bar charts in the terminal or in text mode


<p align="center"><img src="https://i.imgur.com/TCEDkaC.png"></p>
<p align="center"><img src="https://i.imgur.com/VVW1mEB.png"></p>

# Programs and libraries need to compile and work
 - cmake
 - lm_sensors
 - ncurses
 - libsensors

# How to install:
```bash
sudo apt-get install build-essential cmake git libsensors4-dev ncurses-dev
git clone https://github.com/g3t0r/AmIHot.git
cd AmIHot && mkdir build && cd build
cmake ..
make
sudo make install
```
