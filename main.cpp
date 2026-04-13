/* Sine Wave Audio Generator */

/*
    Sine wave parameters:
        Channels per frame: 1 (mono)
        Sample format: 16 bit signed (values in the range -32767..32767)
        Amplitude: ¼ maximum possible 16-bit amplitude (values in the range -8192..8192)
        Duration: one second
        Frequency: 440Hz (440 cycles per second)
        Sample Rate: 48000 samples per second
*/

#include <iostream>
#include <cmath>

int main() {
    const int sampleRate = 48000; // samples per second
    const double frequency = 440.0; // frequency of the sine wave in Hz
    const double amplitude = 8192.0; // amplitude of the sine wave (¼ of max 16-bit value)
    const int durationInSeconds = 1; // duration of the audio in seconds
    const int channels = 1; // mono



    return 0;
}