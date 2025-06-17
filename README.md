# 🔌 Smart Energy Meter using ESP32 📊

This project is a **WiFi-enabled Smart Energy Meter** built using an ESP32. It monitors **Voltage, Current, Power, Energy (kWh), and Cost (₹)** in real-time. Data is displayed on a 16x2 LCD and broadcast over WiFi using a web server. The system also allows users to download logs in `.csv` format.

![Project Overview](https://IMAGE_URL_HERE) <!-- Add circuit or setup image -->

---

## 📷 Demo Preview

- 🔋 Real-time Voltage and Current readings  
- ⚡ Power and Energy consumption tracking  
- 🧾 CSV download (openable in Excel)  
- 🌐 Web interface for remote monitoring  

![Web Dashboard](https://IMAGE_URL_HERE) <!-- Add dashboard screenshot -->

---

## 🛠️ Hardware Required

| Component                 | Quantity | Description                        |
|--------------------------|----------|------------------------------------|
| ESP32 Dev Board          | 1        | Main MCU with WiFi support         |
| ZMPT101B Voltage Sensor  | 1        | Measures AC Voltage                |
| SCT-013 / ACS712 5A      | 1        | Non-invasive current sensor        |
| LCD 16x2 with I2C Module | 1        | Displays readings locally          |
| Jumper Wires, Breadboard | -        | For connections and prototyping    |

![Components](https://IMAGE_URL_HERE) <!-- Optional: Add components photo -->

---

## 🧰 Hardware Connections

| Component   | ESP32 Pin | Description                    |
|-------------|-----------|--------------------------------|
| ZMPT101B    | GPIO 35   | Voltage sensor analog input    |
| ACS712/SCT-013 | GPIO 34 | Current sensor analog input    |
| LCD SDA     | GPIO 21   | I2C data                       |
| LCD SCL     | GPIO 22   | I2C clock                      |
| Power (5V)  | VIN/GND   | Power to all modules           |

💡 *Use proper burden/calibration resistors for accurate readings.*

---

## 🔍 Features

- Real-time monitoring on LCD and web  
- Auto-switching LCD pages every 3 seconds  
- ESP32 WiFi hotspot with live web dashboard  
- Downloadable CSV logs  
- Customizable unit cost for billing estimate  

---

## 📶 WiFi Setup

- SSID: `ESP32_Server`  
- Password: `12345678`  
- Open browser and go to: [http://192.168.4.1](http://192.168.4.1)  

---

## 📺 LCD Display

The LCD automatically toggles between two pages:

**Page 1:**  
`V: 230.5V  I: 0.23A`  
`P: 52.8W`

**Page 2:**  
`Energy: 0.150 kWh`  
`Cost: ₹0.98`

![LCD Demo](https://IMAGE_URL_HERE) <!-- Add LCD screenshot -->

---

## 🌐 Web Server Endpoints

ESP32 hosts a simple web server with:

- `/` → Live data dashboard  
- `/data.csv` → CSV download  

![CSV Button UI](https://IMAGE_URL_HERE) <!-- Add download page image -->

---

## 🧾 CSV Logging

CSV format (tab-separated):  
`Voltage	Current	Power	kWh	Cost`  
Example:  
`230.5	0.23	52.8	0.150	0.98`

Use Excel or Google Sheets to visualize data trends.

---

## 🧪 Calibration Tips

- **ZMPT101B:** Adjust `voltageSensor.setSensitivity(653.0);`  
- **ACS712 5A:** Adjust `emon.current(34, 1.0);` (try 0.95–1.1)  
- Use a multimeter for real-world calibration comparison.

---

## 📥 How to Use

1. Upload the code to ESP32 using Arduino IDE  
2. Connect to `ESP32_Server` WiFi  
3. Open browser to `http://192.168.4.1`  
4. View real-time data or download the CSV report  

---

## 🔧 To-Do / Future Enhancements

- ☁️ Add MQTT or Blynk for cloud monitoring  
- 💾 Store data on SD card  
- 🔋 Add battery backup support  

---

## 📃 License

MIT License – Free to use, modify, and share.  

---

## 🙌 Credits

- EmonLib  
- Community tutorials and forums  
- Made with ❤️ for smart energy innovation
