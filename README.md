# 🔋 Li-ion Battery Voltage Measurement using ESP32

A simple **Li-ion Battery Voltage Measurement System** built using an **ESP32** and a resistor voltage divider.

The system measures the battery voltage safely through the ESP32 ADC pin and displays the measured voltage on a **web-based dashboard** with a battery-level animation.

## 🚀 Project Features

* 🔋 Li-ion battery voltage measurement
* 📊 ESP32 ADC-based voltage reading
* ⚡ Resistor voltage divider for ADC protection
* 🌐 ESP32 Web Server dashboard
* 📱 Responsive web interface
* 🔋 Animated battery indicator
* 📈 Real-time voltage display
* 📊 Battery percentage calculation
* 💻 Serial Monitor voltage debugging

## 🧰 Components Required

* ESP32 Development Board
* 1 × Li-ion Battery
* 2 × Resistors
* Jumper Wires
* Breadboard
* USB Cable

## 🔌 Circuit / Voltage Divider

The Li-ion battery voltage is reduced using a resistor voltage divider before connecting it to the ESP32 ADC input.

```text
        Li-ion Battery
          +       -
          |       |
          |       +---------------- GND
          |
         R1
          |
          +---------- ESP32 ADC Pin
          |
         R2
          |
          +---------------- GND
```

### Voltage Divider Formula

The voltage at the ESP32 ADC pin is:

```text
Vout = Vin × (R2 / (R1 + R2))
```

The original battery voltage can then be calculated as:

```text
Vin = Vout × ((R1 + R2) / R2)
```

> ⚠️ **Important:** Never connect the Li-ion battery directly to an ESP32 ADC pin. Use an appropriate voltage divider and verify the ADC pin voltage before connecting the battery.

## 📐 Voltage Measurement Process

The ESP32 reads the reduced voltage using its ADC.

```text
Li-ion Battery
      ↓
Voltage Divider
      ↓
ESP32 ADC Pin
      ↓
analogRead()
      ↓
ADC Raw Value
      ↓
ADC Voltage
      ↓
Voltage Divider Calculation
      ↓
Battery Voltage
      ↓
Battery Percentage
      ↓
Web Dashboard
```

The Arduino-ESP32 ADC API provides `analogRead()` for raw ADC readings and `analogReadMilliVolts()` for calibrated millivolt readings.

## 📊 ESP32 ADC

The ESP32 uses an ADC (Analog-to-Digital Converter) to convert the analog voltage into a digital value.

For a standard ESP32 configuration:

```text
ADC Resolution = 12-bit
ADC Range      = 0 – 4095
```

The ADC raw value can then be converted into a voltage and scaled back to estimate the original battery voltage.

## 🔋 Battery Percentage

For a typical single-cell Li-ion battery, the project can estimate the battery level based on the measured voltage.

Example:

```text
4.20 V → 100%
4.00 V → ~80%
3.85 V → ~60%
3.70 V → ~40%
3.50 V → ~20%
3.20 V → ~0%
```

> These percentages are approximate. Actual Li-ion battery state-of-charge depends on the battery chemistry, load, temperature, age, and discharge characteristics.

## 🌐 Web Dashboard

The ESP32 hosts a web server that displays:

```text
┌──────────────────────────────┐
│      🔋 BATTERY MONITOR      │
│                              │
│          🔋 3.90 V           │
│                              │
│          78%                 │
│                              │
│       Battery Level          │
│                              │
│       ESP32 ONLINE           │
└──────────────────────────────┘
```

The dashboard can be opened from a device connected to the same Wi-Fi network.

Example:

```text
http://ESP32-IP-ADDRESS
```

## 💻 Technologies Used

* **ESP32**
* **Arduino IDE**
* **C/C++**
* **Wi-Fi**
* **HTML**
* **CSS**
* **JavaScript**
* **ADC**
* **Voltage Divider**

## 📁 Project Structure

```text
Li-ion-Battery-Voltage-Measurement/
│
├── code/
│   └── Battery_Voltage_Monitor.ino
│
├── web/
│   └── index.html
│
├── images/
│   ├── circuit.png
│   └── dashboard.png
│
└── README.md
```

## ⚙️ Setup

### 1. Install ESP32 Board Support

Install the ESP32 board package in Arduino IDE.

### 2. Connect the Circuit

Connect the Li-ion battery through the resistor voltage divider to an ESP32 ADC-capable GPIO.

### 3. Upload the Code

Open:

```text
Battery_Voltage_Monitor.ino
```

Select your ESP32 board and upload the program.

### 4. Open Serial Monitor

Set the baud rate according to the code, for example:

```text
115200
```

The Serial Monitor can be used to check:

```text
ADC Value
ADC Pin Voltage
Battery Voltage
Battery Percentage
Wi-Fi Status
IP Address
```

### 5. Open the Dashboard

After the ESP32 connects to Wi-Fi, copy the displayed IP address into a browser.

```text
http://ESP32-IP-ADDRESS
```

## ⚠️ Safety Notes

* Do **not** connect a Li-ion battery directly to an ESP32 ADC input.
* Always use a suitable voltage divider.
* Verify the voltage at the ADC pin with a multimeter before connecting it to the ESP32.
* Make sure the maximum possible battery voltage is within the safe ADC input range.
* Check resistor values and wiring carefully.
* Li-ion batteries can be hazardous if short-circuited, overcharged, or physically damaged.

## 🎯 Learning Objectives

This project helps demonstrate:

* ESP32 ADC operation
* Analog voltage measurement
* Voltage divider calculations
* Sensor-style analog data processing
* Battery percentage calculation
* ESP32 Wi-Fi connectivity
* Web server development
* HTML/CSS/JavaScript dashboard design
* Real-time IoT monitoring

## 🔮 Future Improvements

Possible upgrades:

* 📈 Voltage history graph
* 🔔 Low-battery warning
* 📱 Mobile-friendly dashboard
* ☁️ IoT cloud monitoring
* 🔋 Battery charging status
* 📊 Data logging
* 🔐 Secure web dashboard
* ⚡ Current measurement
* 🔋 Battery power estimation

## 👨‍💻 Author

**Sasidu Wishshanka**

BICT Student | Embedded Systems | IoT | Robotics | Networking & Cyber Security

### 🔗 Connect With Me

* GitHub: **Sasidu-Tech**
* LinkedIn: **Sasidu Wishshanka**

## 📜 License

This project is licensed under the **MIT License**.

---

⭐ If you found this project useful, consider giving the repository a **star**!

**ESP32 • IoT • Embedded Systems • Battery Monitoring**
.
