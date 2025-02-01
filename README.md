---

# GPS Tracking with Tiva C Series TM4C123G

This project demonstrates GPS tracking using the **Tiva C Series TM4C123G LaunchPad**. The goal is to interface a GPS module (such as the **Ublox NEO-6m**) with the Tiva C board and extract location data.

## Features:
- **GPS Module Integration**: Connect the Ublox NEO-6m GPS module to the Tiva C LaunchPad.
- **UART Communication**: Implement UART communication to receive NMEA sentences from the GPS module.
- **Data Parsing**: Parse NMEA sentences to extract latitude, longitude, and other relevant information.
- **Display**: Display real-time GPS data on an LCD or serial monitor.
- **Position Logging**: Log GPS coordinates to an SD card or EEPROM.
- **Mapping**: Integrate with mapping APIs (e.g., Google Maps) to visualize the tracked path.

## Hardware Requirements:
- **Tiva C Series TM4C123GH6PM LaunchPad**
- **Ublox NEO-6m GPS Module**
- Connecting wires
- Optional: **LCD display**, **SD card module**

## Getting Started:
1. Set up the Tiva C LaunchPad development environment (e.g., Keil uVision).
2. Wire the GPS module to the Tiva C board (TX/RX pins).
3. Write code to initialize UART communication and parse NMEA sentences.
4. Display GPS data on an output device (LCD or serial monitor).
5. Implement position logging if needed.

Feel free to explore and modify the code to suit your specific requirements. Happy tracking! 🌐🛰️

![ek-tm4c123gxl-angled](https://github.com/MoustafaHashem/GPS_Tracking_System/assets/43302105/218e7517-adc4-4231-a40a-c2fe46573b4a)
