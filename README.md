# Sine Wave Audio Generator
This project generates and processes digital audio using C++. It demonstrates how to create audio samples programmatically, write them to WAV files, apply signal clipping, and play audio directly through the system’s output.

The program performs the following tasks each time it runs:

1. Generates a 440 Hz sine wave and writes it to `sine.wav`
2. Generates a louder sine wave, applies hard clipping, and writes it to `clipped.wav`
3. Plays the clipped sine wave directly using an audio library

## Features
- Generates a mono sine wave
- Writes WAV files in 16-bit PCM format using libsndfile
- Implements hard clipping (nonlinear distortion)
- Plays audio in real time using PortAudio

## Audio Specifications
### Sine Wave (`sine.wav`)
- Channels: 1 (mono)
- Amplitude: ¼ of maximum (±8192 in 16-bit, normalized to ±0.25)
- Duration: 1 second
- Frequency: 440 Hz
- Sample Rate: 48,000 Hz

### Clipped Wave (`clipped.wav`)
- Generated at ½ amplitude (±16384 in 16-bit, normalized to ±0.5)
- Clipped to ¼ amplitude (±8192 in 16-bit, normalized to ±0.25)
- Demonstrates hard clipping distortion

## Build Instructions
### Requirements
- C++ compiler (g++)
- libsndfile
- PortAudio

### Install dependencies (Ubuntu/WSL)
```
sudo apt update
sudo apt install libsndfile1-dev portaudio19-dev
```

### Build
Use the `makefile` by using the following command:
```
make
```

### Run
```
./audio
```

## Output
After running the program, the following files will be generated:

- `sine.wav` - clean sine wave
- `clipped.wav` - clipped sine wave

## Playback Notes
The program attempts to play audio using PortAudio.

> **Note:** Audio playback may not work in environments without an audio device (e.g., WSL).

If playback fails, the WAV files are still generated correctly and can be opened in tools such as Audacity for verification.

## How It Works
### Sine Wave Generation

Audio samples are generated using the sine function:

```
sample(t) = amplitude × sin(2πft)
```

Each sample represents the waveform at a specific time step. A full second of audio at 48,000 Hz requires 48,000 samples.

### Clipping
Clipping is applied by limiting the amplitude range:

- Values greater than +0.25 are set to +0.25
- Values less than -0.25 are set to -0.25

This creates a flat-topped waveform which introduces distortion similar to a basic fuzz effect.

## What I Learned
- How to generate sine waves mathematically
- How digital audio is represented as discrete samples
- How clipping can affect waveforms and audio signals
- How external libraries can be used for audio I/O

## Future Improvements
- Allow configurable frequency and duration from command-line arguments
- Improve audio device selection handling
- Add libraries to visualize the sine waves
