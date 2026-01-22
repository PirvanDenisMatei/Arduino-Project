# Arduino Project

This project is an attempt to work with different types of mechanical instruments such as:
- **LED lights**, for showing the status of the machine
- **passive buzzer**, for playing basic sounds
- **tilt ball switch**, for detecting if the device is tilted
- **IR (infrared) receiver module**, for taking signals from a remote
- **DC motor**, for applying torque to a component

## Goals

The main functionality of the project is playing 4 different songs (The Godfather, Super Mario Bros main theme, Pink Panther and the Romanian anthem) with the help of a remote, but it's real purpose was as a learning experience

## How it works

In the pitches.h file are kept renditions of around 90 musical notes into numbers understood by the buzzer. In the same file are kept the scores of the 4 songs, which are played when selected with the remote, whose signals are interpreted in the main.ino file.

<p align="center">
  <img width="600" height="428" alt="image" src="https://github.com/user-attachments/assets/2920a6e8-75e2-4dcb-9dc0-a0d49717ac4c" />
</p>

<p align="center">
  Simple schematic of the project
</p>
