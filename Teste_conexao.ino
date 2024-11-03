/*
*  ESP32 WiFi Scanner Example. Examples > WiFi > WiFiScan
*  Full Tutorial @ https://deepbluembedded.com/esp32-wifi-library-examples-tutorial-arduino/
*/
 
#include "WiFi.h"
 
 int numero = 0;
 #define Botao 2

 boolean Estado_botao = true;
 boolean Estado_botao_anterior = true;

void setup()
{
    Serial.begin(115200);
    pinMode(Botao, INPUT_PULLUP);
 
    // Set WiFi to station mode and disconnect from an AP if it was previously connected.
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
     Serial.println("Setup done");
}
 
void loop()
{
  Estado_botao = digitalRead(Botao);
  delay(10);

    if (!Estado_botao == true && Estado_botao_anterior == true){
      
        numero = numero + 1;
        Serial.print("leitura número = ");
        Serial.println(numero);
        leitura_wifi();      
      }    
      Estado_botao_anterior = Estado_botao;

      delay(10);
     
}

void leitura_wifi(){

Serial.println("Scan start");
    
        // WiFi.scanNetworks will return the number of networks found.
        int n = WiFi.scanNetworks();
        Serial.println("Scan done");
        if (n == 0) {
            Serial.println("no networks found");
        } else {
            Serial.print(n);
            Serial.println(" networks found");
            Serial.println("Nr | SSID                             | RSSI | CH | Encryption");
            for (int i = 0; i < n; ++i) {
                // Print SSID and RSSI for each network found
                Serial.printf("%2d",i + 1);
                Serial.print(" | ");
                Serial.printf("%-32.32s", WiFi.SSID(i).c_str());
                Serial.print(" | ");
                Serial.printf("%4d", WiFi.RSSI(i));
                Serial.print(" | ");
                Serial.printf("%2d", WiFi.channel(i));
                Serial.print(" | ");
                switch (WiFi.encryptionType(i))
                {
                case WIFI_AUTH_OPEN:
                    Serial.print("open");
                    break;
                case WIFI_AUTH_WEP:
                    Serial.print("WEP");
                    break;
                case WIFI_AUTH_WPA_PSK:
                    Serial.print("WPA");
                    break;
                case WIFI_AUTH_WPA2_PSK:
                    Serial.print("WPA2");
                    break;
                case WIFI_AUTH_WPA_WPA2_PSK:
                    Serial.print("WPA+WPA2");
                    break;
                case WIFI_AUTH_WPA2_ENTERPRISE:
                    Serial.print("WPA2-EAP");
                    break;
                case WIFI_AUTH_WPA3_PSK:
                    Serial.print("WPA3");
                    break;
                case WIFI_AUTH_WPA2_WPA3_PSK:
                    Serial.print("WPA2+WPA3");
                    break;
                case WIFI_AUTH_WAPI_PSK:
                    Serial.print("WAPI");
                    break;
                default:
                    Serial.print("unknown");
                }
              
                Serial.println();

                delay(10);
            }
        }
        Serial.println("");
    
        // Delete the scan result to free memory for code below.
        WiFi.scanDelete();  
        // Wait a bit before scanning again.
        delay(10);
}
