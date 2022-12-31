/************************ Adafruit IO Config *******************************/
#define IO_USERNAME "omerfaruksunar"  //Adafruit'e baglanti icin gerekli username ve key girisi
#define IO_KEY "aio_EgiZ02qR0c9jsP7luFA1Igj9lYzO"

/******************************* WIFI **************************************/

#define WIFI_SSID "ofs"      //Wifi SSID ve sifresi
#define WIFI_PASS "38383838"


#include "AdafruitIO_WiFi.h"

#if defined(USE_AIRLIFT) || defined(ADAFRUIT_METRO_M4_AIRLIFT_LITE) ||         \
    defined(ADAFRUIT_PYPORTAL)
#if !defined(SPIWIFI_SS) // wifi tanımı kart varyantında değilse

#define SPIWIFI SPI
#define SPIWIFI_SS 10 // çip seçim pini
#define NINA_ACK 9    // Busy yada ready pini
#define NINA_RESETN 6 // Reset pini
#define NINA_GPIO0 -1 
#endif
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS, SPIWIFI_SS,
                   NINA_ACK, NINA_RESETN, NINA_GPIO0, &SPIWIFI);
#else
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);
#endif
