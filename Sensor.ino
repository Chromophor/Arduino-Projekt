#include <Arduino.h>
#include <ESP8266WiFi.h>


#include <OneWire.h>
#include <DallasTemperature.h>

//Farben der Kabel am Sensor:
//GND = GRAU !!
//3V3 = LILA !!
//D4  = GRÜN !!


#define ONE_WIRE_BUS_2 D4

OneWire oneWire_out(ONE_WIRE_BUS_2);

WiFiServer server(80);


DallasTemperature sensor_outhouse(&oneWire_out);

void setup(void)
{
    Serial.begin(9600);
    Serial.println();
    //pinMode(4, INPUT_PULLUP);

    sensor_outhouse.begin();

    WiFi.begin("Enrichment", "enrichment");
    while (WiFi.status() != WL_CONNECTED)
    { 
      delay(500);
      Serial.print(".");
    }
    Serial.println();
    Serial.println("Connected");

    server.begin();
    Serial.printf("Web server started, open %s in a web browser\n", WiFi.localIP().toString().c_str());
   
}

String prepareHtmlPage()
{
  sensor_outhouse.requestTemperatures();
    String htmlPage;
    htmlPage.reserve(1024);               // prevent ram fragmentation
    htmlPage = F("HTTP/1.1 200 OK\r\n"
               "Content-Type: text/html\r\n"
               "Connection: close\r\n"  // the connection will be closed after completion of the response
               "Refresh: 5\r\n"         // refresh the page automatically every 5 sec
               "\r\n"
               "<!DOCTYPE HTML>"
               "<html>"
               "Analog input:  ");
    htmlPage += sensor_outhouse.getTempCByIndex(0);
    htmlPage += F("</html>"
                "\r\n");
    return htmlPage;
}



void loop(void)
{
    /*
    Serial.print("Requesting temperatures...");

    sensor_outhouse.requestTemperatures();
    Serial.println(" done");


    Serial.print("Temperatur: ");
    Serial.print(sensor_outhouse.getTempCByIndex(0));
    Serial.println("  °C");
    */


  WiFiClient client = server.available();
  // wait for a client (web browser) to connect
  if (client)
  {
    Serial.println("\n[Client connected]");
    while (client.connected())
    {
      // read line by line what the client (web browser) is requesting
      if (client.available())
      {
        String line = client.readStringUntil('\r');
        Serial.print(line);
        // wait for end of client's request, that is marked with an empty line
        if (line.length() == 1 && line[0] == '\n')
        {
          client.println(prepareHtmlPage());
          break;
        }
      }
    }

    while (client.available()) {
      // but first, let client finish its request
      // that's diplomatic compliance to protocols
      // (and otherwise some clients may complain, like curl)
      // (that is an example, prefer using a proper webserver library)
      client.read();
    }

    // close the connection:
    client.stop();
    Serial.println("[Client disconnected]");
  }
}

/*
void temp()
{
  sensor_outhouse.requestTemperatures();
  int temp = sensor_outhouse.getTempCByIndex(0);
  return temp;
}
*/
