## Taxiphone

Taxiphone is a [Leaflabs Maple](http://leaflabs.com/devices/maple/) sketch to detect which number has been composed on a rotary phone and send the according MIDI message in order to control the sounds that are played with Ableton Live.

It can be easily adapted to [Arduino](http://arduino.cc).

It was developed with [Etrange Miroir](http://etrangemiroir.org) for the scenographic installation [L'étrange taxiphone](http://etrangemiroir.org/etrange_taxiphone.html)

# If in trouble while uploading the code

Try to upload the code through the IDE, then put the Maple in perpertual bootloader mode:

- Plug your board into the USB port.
- Hit the reset button (it’s the button labeled RESET). Notice that your board blinks quickly 6 times, then blinks slowly a few more times.
- Hit reset again, and this time push and hold the other button during the 6 fast blinks (the normal button is labeled BUT). You can release it once the slow blinks start.

Then, from the command line:

```
dfu-util -d 1EAF:0003 -a 1 -D /path/to/taxiphone.cpp.bin
```

Where `/path/to/taxiphone.cpp.bin` is mentioned in the console of the IDE.

