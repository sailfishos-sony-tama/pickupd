# Pickup gesture monitoring daemon

This Sailfish daemon monitors taps from sensorfwd and requests turning
on display on receiving the tap by communicating with MCE. Sensor is
stopped when the display is on and armed on switching off the display.

It is intended to be used on Sailfish devices having
[SENSOR_TYPE_PICK_UP_GESTURE](https://source.android.com/devices/sensors/sensor-types#pick_up_gesture)
which is hooked as a tapadaptor using hybrispickupadaptor of
sensorfwd.
