#include "config.h"                                                   //Config isimli olusturdugumuz kutuphaneyi ekliyoruz.
#include <ThingSpeak.h>                                               //ThingSpeak kutuphanesini ekliyoruz
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>                                      //Telegram kullanımı için Kutuphaneyi include ediyoruz.
#include <ArduinoJson.h>
WiFiClientSecure client;

#define BOTtoken ""      //Telegram bot token buraya yazıyoruz.
#define CHAT_ID ""                                           //Telegram Chat ID buraya yazıyoruz.
X509List cert(TELEGRAM_CERTIFICATE_ROOT); 


int count = 0;                                                        //Devremizi ilk calistirdigimizda count degerini 0 veriyoruz.


AdafruitIO_Feed *counter = io.feed("counter");                        // Adafruit'e gonderecegimiz veriyi ayarlıyoruz.
#define in D7                                                         // giris ve cikis pinlerini taimliyoruz
#define out D2

char thingSpeakAddress[] = "api.thingspeak.com";
String thingtweetAPIKey = "";                         //ThingTweet API key'i buraya yazıyoruz.
String tsData;


unsigned long channelID = ;                                    //ThingSpeak ChannelID buraya yazıyoruz.
unsigned  int field_no=1;
const char* writeAPIKey = "";                         //  Thingspeak write API Key'i buraya yazıyoruz.
const char* readAPIKey  = "";                         //  Thingspeak  read  API Key'i buraya yazıyoruz.
const char* server = "api.thingspeak.com";
UniversalTelegramBot bot(BOTtoken, client);
int rndNumber;                                                        //Twitter'a kontrol no bilgisi verecek random degeri tanımlıyoruz.
void setup() {
configTime(0, 0, "pool.ntp.org");                                     // UTC saatini NTP aracılığıyla alıyoruz.
  client.setTrustAnchors(&cert);                                      // api.telegram.org için sertifika ekliyoruz.
  // seri bağlantıyı başlat
  Serial.begin(115200);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  ThingSpeak.begin(client); 
  // seri monitörün açılmasını bekleyin
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // io.adafruit.com'a bağlanın
  io.connect();

  // bağlantı için bekleyin
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // Bağlandı
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {
  
  io.run();
  int in_value = digitalRead(in);
  int out_value = digitalRead(out);
  if(in_value == LOW)                                                 // Giris kapisindaki sensorden gecis algilanirsa count degerimizi bir artırıp gerekli uygulamalardaki kisi sayisini guncelliyoruz.
  {
    count++;
    Serial.print("Kisi sayisi:");
    Serial.println(count);
    delay(1000);
    // Adafruit IO'daki 'count' beslemesine sayımı kaydet
   bot.sendMessage(CHAT_ID, String(count), "");                       //Telegrama Mesaj gönderiyoruz.
  Serial.print("sending -> ");
  Serial.println(count);
  counter->save(count);
  rndNumber=random(5,1000); 
    ThingSpeak.writeField (channelID, field_no, count, writeAPIKey);             // ThingSpeak'e  kisi sayisini gönderiyoruz
   if (client.connect("api.thingspeak.com",80)) {                                // ThingTweet uygulaması ile tweet attırıyoruz.
      tsData = "api_key="+thingtweetAPIKey+"&status="+"Kisi sayisi="+count+"\nKontrol No:"+rndNumber;
      client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(tsData.length());
      client.print("\n\n");
      client.print(tsData);
      Serial.println("Tweet gonderildi");

    }
  }
  
  if(out_value == LOW)                                                          // Cikis kapisindaki sensorden gecis algilanirsa count degerimizi bir azaltıp gerekli uygulamalardaki kisi sayisini guncelliyoruz.
  {
    count--;
    Serial.print("Kisi sayisi:");
    Serial.println(count);
    delay(1000);
    // Adafruit IO'daki 'count' beslemesine sayımı kaydet
       bot.sendMessage(CHAT_ID, String(count), "");                             //Telegrama Mesaj gönderiyoruz.
  Serial.print("sending -> ");
  Serial.println(count);
  counter->save(count);
  rndNumber=random(5,1000); 
    ThingSpeak.writeField (channelID, field_no, count, writeAPIKey);             // ThingSpeak'e  kisi sayisini gönderiyoruz.
   if (client.connect("api.thingspeak.com",80)) {                                // ThingTweet uygulaması ile tweet attırıyoruz.
      tsData = "api_key="+thingtweetAPIKey+"&status="+"Kisi sayisi="+count+"\nKontrol No:"+rndNumber;
      client.print("POST /apps/thingtweet/1/statuses/update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(tsData.length());
      client.print("\n\n");
      client.print(tsData);
      Serial.println("Tweet gonderildi");

    }
  }


}
