#include <WiFi.h>
#include <HTTPClient.h>

const char *ssid = "WIFI SSID";
const char *password = "WIFI PASSWORD";
const char *url = "https://api.callmebot.com/whatsapp.php?APIKEY";

unsigned long lastTime = 0; // Keep track of the last time the request was made
const int interval = 10000; // Interval between requests in milliseconds (10 seconds)

const int signalPin = 2; // Pin D2

void setup()
{
    Serial.begin(115200);

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("Connected to WiFi");
}

void loop()
{
    // Read the signal from pin D2
    int signal = digitalRead(signalPin);

    // Check if it's time to make the request and pin D2 is HIGH
    if (signal == HIGH && millis() - lastTime >= interval)
    {
        makeRequest();
        lastTime = millis(); // Update lastTime to current time
    }
}

void makeRequest()
{
    if (WiFi.status() == WL_CONNECTED)
    { // Check if connected to Wi-Fi
        HTTPClient http;

        Serial.print("Sending request...");
        http.begin(url);           // Specify the URL
        int httpCode = http.GET(); // Make the GET request

        if (httpCode > 0)
        { // Check for a successful response
            Serial.print("Response code: ");
            Serial.println(httpCode);

            String payload = http.getString(); // Get the response payload
            Serial.println(payload);           // Print the response payload
        }
        else
        {
            Serial.print("Error on HTTP request: ");
            Serial.println(httpCode);
        }

        http.end(); // Close connection
    }
    else
    {
        Serial.println("WiFi Disconnected. Reconnecting...");
        WiFi.begin(ssid, password); // Reconnect to Wi-Fi
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(1000);
            Serial.print(".");
        }
        Serial.println("Reconnected to WiFi");
    }
}
