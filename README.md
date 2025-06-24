📘 Project Title:
ESP32-S3 + Zephyr RTOS: I²C-Based Temperature Monitoring System with LCD Display
-------------------------------------------------------------------------
🔧 Summary

This project uses an ESP32-S3 microcontroller running Zephyr RTOS to implement an I²C communication system where the ESP32 acts as a single master and communicates with multiple I²C slave devices:

A BME680 environmental sensor

An LCD 2004 (HD44780-based) display with I²C interface

----------------------------------------------------------------------------
🧠 What the Project Does

Initializes the I²C bus on the ESP32-S3.

Communicates with the BME680 sensor to fetch real-time temperature and pressure data.

Sends this data to the LCD to display the values.

Operates continuously in a loop, updating the display at regular intervals.

----------------------------------------------------------------------------
🏗️ Hardware Setup

Microcontroller: ESP32-S3 DevKitC

Sensor: BME680 (connected over I²C)

Display: 20x4 LCD with I²C backpack (e.g., PCF8574)

Connections:

Both BME680 and LCD share the same I²C bus

SDA and SCL lines are mapped to GPIO1 and GPIO1

Pull-up resistors (typically 4.7kΩ) are either built-in or externally added

----------------------------------------------------------------------------
🧩 Why This Setup?

Demonstrates multi-slave I²C communication using Zephyr RTOS.

Showcases how to develop custom drivers for unsupported I²C devices.

Integrates environmental sensing with real-time display output, making it ideal for embedded monitoring applications.

---------------------------------------------------------------------------
🧪 Project Goals

Learn how to configure and use Zephyr RTOS on ESP32-S3

Implement I²C communication with multiple slaves

Use real-time sensor data in embedded systems

Create a clear and educational project structure for future reuse or learning

--------------------------------------------------------------------------
💻 Software Stack

Zephyr RTOS for real-time OS and hardware abstraction

Custom BME680 driver for sensor communication

Custom LCD driver based on HD44780 over I²C

VS Code + west build system for development

------------------------------------------------------------------------
📈 Expected Output

On power-up, the system initializes the I²C bus.

Periodically reads temperature and pressure from the BME680 sensor.

Displays the readings clearly on the 20x4 LCD.

-----------------------------------------------------------------------
