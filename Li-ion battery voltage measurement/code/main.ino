#include <WiFi.h>
#include <WebServer.h>

// ===============================
// Wi-Fi
// ===============================
const char* ssid = "Infinix HOT 40 Pro";
const char* password = "12345678";

// ===============================
// Battery Voltage Divider
// ===============================
#define BATTERY_PIN 34

const float R1 = 10000.0;   // 10kΩ
const float R2 = 10000.0;   // 10kΩ

const float ADC_REFERENCE = 3.52;
const float ADC_RESOLUTION = 4095.0;

// ===============================
// Web Server
// ===============================
WebServer server(80);

// ===============================
// Read Battery Voltage
// ===============================
float readBatteryVoltage() {

  // Take several readings and average them
  long total = 0;

  for (int i = 0; i < 20; i++) {
    total += analogRead(BATTERY_PIN);
    delay(2);
  }

  float adcValue = total / 20.0;

  // Convert ADC raw value to ADC pin voltage
  float pinVoltage =
      adcValue * (ADC_REFERENCE / ADC_RESOLUTION);

  // Convert ADC voltage back to actual battery voltage
  float batteryVoltage =
      pinVoltage * ((R1 + R2) / R2);

  return batteryVoltage;
}

// ===============================
// Battery Percentage
// ===============================
int calculatePercentage(float voltage) {

  // Approximate percentage for a single Li-ion cell
  // 4.20V = 100%
  // 3.00V = 0%

  int percentage =
      ((voltage - 3.00) / (4.20 - 3.00)) * 100;

  percentage = constrain(percentage, 0, 100);

  return percentage;
}

// ===============================
// Dashboard HTML
// ===============================
const char MAIN_PAGE[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html>

<head>

<meta name="viewport"
content="width=device-width, initial-scale=1">

<title>ESP32 Battery Monitor</title>

<style>

* {
  box-sizing: border-box;
}

body {
  margin: 0;
  font-family: Arial, sans-serif;
  background: linear-gradient(135deg, #07111f, #102a43);
  color: white;
  min-height: 100vh;
}

.header {
  text-align: center;
  padding: 30px 15px 15px;
}

.header h1 {
  margin: 0;
  font-size: 30px;
  letter-spacing: 2px;
}

.header p {
  color: #9fb3c8;
  margin-top: 8px;
}

.container {
  max-width: 850px;
  margin: auto;
  padding: 20px;
}

.card {
  background: rgba(255,255,255,0.08);
  border: 1px solid rgba(255,255,255,0.12);
  border-radius: 25px;
  padding: 30px;
  text-align: center;
  box-shadow: 0 15px 40px rgba(0,0,0,0.3);
}

.battery {
  width: 220px;
  height: 105px;
  border: 5px solid #fff;
  border-radius: 15px;
  margin: 25px auto;
  position: relative;
  padding: 7px;
}

.battery:after {
  content: "";
  position: absolute;
  right: -18px;
  top: 32px;
  width: 13px;
  height: 35px;
  background: white;
  border-radius: 0 5px 5px 0;
}

.level {
  height: 100%;
  width: 0%;
  border-radius: 7px;
  background: linear-gradient(90deg, #00e676, #76ff03);
  transition: width 0.5s;
}

.voltage {
  font-size: 52px;
  font-weight: bold;
  margin: 10px 0;
}

.unit {
  font-size: 22px;
  color: #9fb3c8;
}

.percentage {
  font-size: 28px;
  margin-top: 10px;
}

.status {
  margin: 20px auto;
  padding: 12px 25px;
  border-radius: 30px;
  display: inline-block;
  background: #00c853;
  font-weight: bold;
}

.info {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 15px;
  margin-top: 25px;
}

.info-box {
  background: rgba(255,255,255,0.06);
  padding: 18px;
  border-radius: 15px;
}

.label {
  color: #9fb3c8;
  font-size: 14px;
}

.value {
  font-size: 20px;
  margin-top: 7px;
  font-weight: bold;
}

.footer {
  text-align: center;
  color: #718096;
  margin-top: 25px;
  font-size: 13px;
}

</style>

</head>

<body>

<div class="header">

<h1>🔋 ESP32 BATTERY MONITOR</h1>

<p>Real-Time Battery Voltage Dashboard</p>

</div>

<div class="container">

<div class="card">

<div class="battery">

<div class="level" id="batteryLevel"></div>

</div>

<div class="voltage">

<span id="voltage">0.00</span>

<span class="unit">V</span>

</div>

<div class="percentage">

<span id="percentage">0</span>%

</div>

<div class="status" id="status">

READING...

</div>

<div class="info">

<div class="info-box">

<div class="label">
ADC RAW
</div>

<div class="value" id="adc">
0
</div>

</div>

<div class="info-box">

<div class="label">
ADC PIN VOLTAGE
</div>

<div class="value">

<span id="pinVoltage">0.00</span> V

</div>

</div>

<div class="info-box">

<div class="label">
DIVIDER
</div>

<div class="value">
10kΩ / 10kΩ
</div>

</div>

<div class="info-box">

<div class="label">
UPDATE
</div>

<div class="value">
2 Seconds
</div>

</div>

</div>

</div>

<div class="footer">

ESP32 Battery Monitoring System

</div>

</div>

<script>

function updateData() {

fetch("/api/data")

.then(response => response.json())

.then(data => {

document.getElementById("voltage")
.innerText = data.battery.toFixed(2);

document.getElementById("percentage")
.innerText = data.percentage;

document.getElementById("adc")
.innerText = data.adc;

document.getElementById("pinVoltage")
.innerText = data.pinVoltage.toFixed(2);

document.getElementById("batteryLevel")
.style.width = data.percentage + "%";

let status = document.getElementById("status");

if (data.battery >= 4.0) {

status.innerText = "BATTERY FULL";

status.style.background = "#00c853";

}

else if (data.battery >= 3.6) {

status.innerText = "BATTERY GOOD";

status.style.background = "#00c853";

}

else if (data.battery >= 3.3) {

status.innerText = "BATTERY LOW";

status.style.background = "#ff9800";

}

else {

status.innerText = "CHARGE BATTERY";

status.style.background = "#f44336";

}

})

.catch(error => {

document.getElementById("status")
.innerText = "CONNECTION ERROR";

});

}

updateData();

setInterval(updateData, 2000);

</script>

</body>

</html>

)rawliteral";

// ===============================
// Main Page
// ===============================
void handleRoot() {

  server.send_P(
    200,
    "text/html",
    MAIN_PAGE
  );
}

// ===============================
// API
// ===============================
void handleAPI() {

  long total = 0;

  for (int i = 0; i < 20; i++) {

    total += analogRead(BATTERY_PIN);

    delay(2);
  }

  float adcValue = total / 20.0;

  float pinVoltage =
      adcValue *
      (ADC_REFERENCE / ADC_RESOLUTION);

  float batteryVoltage =
      pinVoltage *
      ((R1 + R2) / R2);

  int percentage =
      calculatePercentage(batteryVoltage);

  String json = "{";

  json += "\"adc\":";
  json += String(adcValue, 0);

  json += ",";

  json += "\"pinVoltage\":";
  json += String(pinVoltage, 3);

  json += ",";

  json += "\"battery\":";
  json += String(batteryVoltage, 2);

  json += ",";

  json += "\"percentage\":";
  json += String(percentage);

  json += "}";

  server.send(
    200,
    "application/json",
    json
  );
}

// ===============================
// Setup
// ===============================
void setup() {

  Serial.begin(115200);

  delay(1000);

  // ADC setup
  analogReadResolution(12);

  pinMode(
    BATTERY_PIN,
    INPUT
  );

  Serial.println();
  Serial.println("==============================");
  Serial.println(" ESP32 BATTERY MONITOR");
  Serial.println("==============================");

  // Wi-Fi
  WiFi.begin(
    ssid,
    password
  );

  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);

    Serial.print(".");
  }

  Serial.println();

  Serial.println("WiFi Connected!");

  Serial.print("ESP32 IP Address: ");

  Serial.println(
    WiFi.localIP()
  );

  // Web routes
  server.on(
    "/",
    handleRoot
  );

  server.on(
    "/api/data",
    handleAPI
  );

  server.begin();

  Serial.println("Web Server Started!");
}

// ===============================
// Loop
// ===============================
void loop() {

  server.handleClient();

}