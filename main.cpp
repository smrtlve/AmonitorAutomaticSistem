#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


#include "CTBot.h"
CTBot myBot;


String ssid = "MasyhaAllah";
String pass = "11111111";
//const char* host = "192.168.43.137"; //IP PC
const char* host = "192.168.137.1"; //IP PC

String token = "811342021:AAFP4OE4EYAZ0LJcQAnfl1t3KUHr3SO-84Q";
const int id = 240599031;


#define RL 10  // Nilai RL resistor smd 103 pada sensor yang di gunakan
#define m -0.417 // Kalkulasi slope (Pada grafik datasheet)
#define b 0.43 // Nilai kalkulasi (Titik tengan) 0.860 / 2 43 
#define Ro 22 // Nilai Ro yang didapat dari pembacaan nilai udara bersih
#define MQ_sensor A0 


const int IN1 = 12;
const int IN2 = 13;
const int ENA = 15;
const int Relay = 5;


const int numReadings = 5;//nilai penambilan sample pembacaan sebesar 5 kali
float readings[numReadings];      
int readIndex = 0;              
float total = 0;                  
float average = 0;   


boolean konfirmasi = false;
boolean kondisiSwiper = false;


WiFiClientSecure client;

void setup(){
  Serial.begin(115200);
  //==================Koneksi Ke Wifi, dan Localhost====================//
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  delay(100);
  //==================Koneksi Ke Wifi, dan Localhost====================//

  //==================Koneksi Ke Server Telegram====================//
  TBMessage msg;
	Serial.println("Starting TelegramBot...");
  myBot.sendMessage(id, "Lakukan 1x trigger ke sensor untuk kalibrasi dan menetralkan kondisi sistem");
  delay(3000);

	myBot.wifiConnect(ssid, pass);
	myBot.setTelegramToken(token);

	if (myBot.testConnection()){
		Serial.println("Terkoneksi ke telegram");
    myBot.sendMessage(id, "Sistem Terkoneksi ke telegram");}
	else{
		Serial.println("Koneks ke telegram GAGAL!");
  }
  delay(3000);
  myBot.sendMessage(id, "Lakukan 1x trigger ke sensor melebihi ambang batas untuk kalibrasi dan menetralkan kondisi sistem");

  //=================================================================//

  //=====================Inisialisasi Pin HW========================//
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (Relay, OUTPUT);
  digitalWrite(ENA, LOW);
  digitalWrite(Relay, LOW);
  //=================================================================//

  //=====================Preheating Sensor========================//
  for (int thisReading = 0; thisReading < numReadings; thisReading++){
    readings[thisReading] = 0;
  }
  
  for (int times = 1; times <=5; times++) {
    Serial.print("pre heating ");
    Serial.print(times);
    Serial.println(" seconds");
    delay(1000);
  }
  //=================================================================//
}


void stepPer (
  int jumlahSwiper,
  int lamaMaju, //Hitungan per 1 putaran = 10, kalibrasi koma2 sesuaikan
  int lamaMundur //Hitungan per 1 putaran = 10, kalibrasi koma2 sesuaikan
  ){
    for (int i = 1; i <= jumlahSwiper; i++){
      
    digitalWrite(Relay, HIGH); //Aktifkan WaterPump
    delay(500); //WaterPump menyala 500ms sebelum swiper

      analogWrite(ENA, 1023);
      for (int j = 0; j <=lamaMaju; j++){
        digitalWrite(IN2, HIGH);
        delay(10); //3 /1 //Kalibrasi paten jangan dirubah!!
        digitalWrite(IN2, LOW);
        delay(20); //70 /13 //Kalibrasi paten jangan dirubah!!
        Serial.println("Swiper maju");
       }
     
    Serial.println("Jeda 5 detik"); digitalWrite(Relay, LOW); delay(5000);
    
    digitalWrite(Relay, HIGH); //Aktifkan WaterPump
    delay(500); //WaterPump menyala 500ms sebelum swiper
     
      for (int k = 0; k <=lamaMundur; k++){
        digitalWrite(IN1, HIGH);
        delay(10); //3 /1 //Kalibrasi paten jangan dirubah!!
        digitalWrite(IN1, LOW);
        delay(20); //70 /13 //Kalibrasi paten jangan dirubah!!
        Serial.println("Swiper mundur");
      } 
    Serial.println("Jeda 5 detik"); digitalWrite(Relay, LOW); delay(5000);
  }
  Serial.println("Prosedur Pembersihan Selesai"); delay(3000);
  Serial.println("Memulai Ulang Sistem Pembersihan"); delay(3000);
  }


//===========================Logika Perhitungan Nilai Anonia dalam satuan PPM==============================//
float hitungPPM(){
  //=========================Hitung Nilai PPM===========================//
  float VRL; // Drop across tegangan pada sensor
  float Rs; // Resistansi sensor pada konsentrasi gas
  float ratio; // Definisi variabel rasio

  VRL = analogRead(MQ_sensor)*(5.0/1023.0); // Ukur drop tegangan dan konversikan ke 0-5V
  Rs = ((5.0*RL)/VRL)-RL; // Rumus untuk mendapatkan nilai Rs
  ratio = Rs/Ro;  // Menentukan rasio Rs/Ro

  float ppm = pow(10, ((log10(ratio)-b)/m)); // Rumus untuk kalkulasi kadar ppm amonia

  total = total - readings[readIndex];
  readings[readIndex] = ppm;
  total = total + readings[readIndex];
  readIndex = readIndex + 1;

  if (readIndex >= numReadings) {
    readIndex = 0;
  }
  average = total / numReadings; // Menampilkan rata2 kadar amonia sebanyak numReadings 
  
  Serial.print("NH3 (ppm) = " + (String)average + " "); // Menampilkan hasil ppm amonia
  Serial.println("Voltage = " + (String)VRL + " "); // Menampilkan nilai voltase 
  delay(100);

  //=================================================================//
  return average;
}
//===========================Logika Perhitungan Nilai Anonia dalam satuan PPM==============================//


//====================Kirim Data ppm diatas ambang batas Ke DB===================//
void dataBase(){
  // Mengirimkan ke alamat host dengan port 80 -----------------------------------
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  String url = "/amonitor/add.php?data=";
  url += average;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  // Mengirimkan Request ke Server -----------------------------------------------
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  // delay(5000);
}
//====================Kirim Data ppm diatas ambang batas Ke DB===================//


//======================Kirim Data Logging pembersihan Ke DB=========================//
void dataBase2(){
  // Mengirimkan ke alamat host dengan port 80 -----------------------------------
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  String url = "/amonitor/add2.php?data="; //INPUT DATA PPM AWAL
  url += average;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  // Mengirimkan Request ke Server -----------------------------------------------
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  // delay(5000);
}
//======================Kirim Data Logging pembersihan Ke DB=========================//


//======================Kirim Data Logging pembersihan Ke DB=========================//
void dataBase3(){
  // Mengirimkan ke alamat host dengan port 80 -----------------------------------
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  // Isi Konten yang dikirim adalah alamat ip si esp -----------------------------
  String url = "/amonitor/add3.php?data_2="; //INPUT DATA PPM AKHIR
  url += average;
 
  Serial.print("Requesting URL: ");
  Serial.println(url);  
  // Mengirimkan Request ke Server -----------------------------------------------
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }
  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  // delay(5000);
}
//======================Kirim Data Logging pembersihan Ke DB=========================//


void stepPer2 (int lamaMaju, int lamaMundur){ 

  while (kondisiSwiper == true){  

    digitalWrite(Relay, HIGH); //Aktifkan WaterPump
    delay(500); //WaterPump menyala 500ms sebelum swiper

      analogWrite(ENA, 1023);
      for (int j = 0; j <=lamaMaju; j++){ //300
        digitalWrite(IN2, HIGH);
        delay(10); //3 /1 //Kalibrasi paten jangan dirubah!!
        digitalWrite(IN2, LOW);
        delay(20); //70 /13 //Kalibrasi paten jangan dirubah!!
        Serial.println("Swiper maju");
       }
     
    Serial.println("Jeda 5 detik"); digitalWrite(Relay, LOW); delay(5000);
    
    digitalWrite(Relay, HIGH); //Aktifkan WaterPump
    delay(500); //WaterPump menyala 500ms sebelum swiper
     
      for (int k = 0; k <=lamaMundur; k++){ //240
        digitalWrite(IN1, HIGH);
        delay(10); //3 /1 //Kalibrasi paten jangan dirubah!!
        digitalWrite(IN1, LOW);
        delay(20); //70 /13 //Kalibrasi paten jangan dirubah!!
        Serial.println("Swiper mundur");
      } 
    Serial.println("Jeda 5 detik"); digitalWrite(Relay, LOW); delay(5000);

    hitungPPM();
    int ppm = average;

    if (ppm <=24){
      Serial.println("Mengirim data ppm akhir : "+ (String) average +" ke logging swiper");
      dataBase3();
      kondisiSwiper = false;
    }

  }
  Serial.println("Prosedur Pembersihan Selesai"); delay(3000);
  Serial.println("Memulai Ulang Sistem Pembersihan"); delay(3000);
  }


//======================Push notif dan konfirmasi ke tele=========================//
void tbTele(int lamaMaju, int lamaMundur, String Notif){
  TBMessage msg;
  //===============================Push Notif PPM Lebih ambang batas ke Tele================================//
  Serial.println("Kadar Amonia : " + (String)average);
    delay(3000);
    String ppm_value = Notif;
    ppm_value += "Kadar Amonia : ";
    ppm_value += float(average);
    ppm_value += " ppm\n";
    myBot.sendMessage(id, ppm_value, "");
    Serial.println("Mengirim data sensor ke telegram"); 
    delay(5000);
  //===============================Push Notif PPM Lebih ambang batas ke Tele================================//

  //===================================Konfirmasi Aksi Selanjutnya ke Tele================================//
    String replyKonfirm = "Konfirmasi untuk melanjutkan prosedur : \n";
    replyKonfirm += "1. (On) untuk melanjutkan prosedur pembersihan. \n";
    replyKonfirm += "2. (Selesai) untuk melanjutkan tanpa prosedur pembersihan. \n";
    //replyKonfirm += "3. Abaikan konfirmasi jika nilai ppm kurang dari 25. \n";
    myBot.sendMessage(id, replyKonfirm, "");
    delay(5000);
  //===================================Konfirmasi Aksi Selanjutnya ke Tele================================//

  //===========================Logika Konfirmasi, jika memenuhi maka konfirmasi ke while==============================//
  while (konfirmasi==true){ // Ketika konfirmasi true, maka akan menahan pembacaan sensor dan menampilkan nilai sensor terakhir
    Serial.println("Kadar amonia tersimpan di while : "+ (String) average);
    if (myBot.getNewMessage(msg)) {
      if (msg.text.equalsIgnoreCase("On")) { // Jika "On" maka sistem berjalan dengan swiper       
        myBot.sendMessage(id, "Swiper sedang bekerja");
        delay(5000); // Menahan serial print di atas untuk konfirmasi semisal (mesin sedang berjalan);                   
        //stepPer(jumlahSwiper, maju, mundur);
        Serial.println("Mengirim data ppm awal : "+ (String) average +" ke logging swiper");
        dataBase2();
        konfirmasi= false; // Mengembalikan kondisi ke normal pembacaan PPM

        stepPer2(lamaMaju,lamaMundur);
        
        myBot.sendMessage(id, "Prosedur pembersihan selesai");
        myBot.sendMessage(id, "Memulai ulang sistem pembersihan");
      }
      else if (msg.text.equalsIgnoreCase("Selesai")) {  // Jika "Selesai" maka sistem berjalan tanpa swiper
        konfirmasi= false;
        myBot.sendMessage(id, "Membaca ulang nilai sensor"); 
      }
      else {
        String reply = "Konfirmasi untuk melanjutkan prosedur : \n";
        reply += "1. Ketik (On) untuk melanjutkan prosedur pembersihan. \n";
        reply += "2. Ketik (Selesai) untuk melanjutkan tanpa prosedur pembersihan. \n";
        myBot.sendMessage(id, reply, "");
      }
    }
  delay(1);
  }
  //===========================Logika Konfirmasi, jika memenuhi maka konfirmasi ke while==============================//
}
//======================Push notif dan konfirmasi ke tele=========================//



//===========================Logika Eksekusi yang akan dijalankan==============================//
void logikaAksi(){
  int nilaippm = average;
  
  int lamaMaju = 10;//300
  int lamaMundur = 10;//240

  if (nilaippm <= 20){
    konfirmasi= false;
  } 

  else if (nilaippm >= 20 && nilaippm <= 24){
    konfirmasi= false;
    //tbTele(0,0, "Bau amonia mulai tercium \n"); // isi untuk logika swiper maju dan mundur
    myBot.sendMessage(id, "Bau amonia mulai tercium \n");
    myBot.sendMessage(id, "Membaca ulang nilai sensor");
  } 
  
  else if (nilaippm >= 25 && nilaippm <= 30){
    delay(5000);
    konfirmasi= true;
    kondisiSwiper = true;
    dataBase(); 
    tbTele(lamaMundur,lamaMundur, "Kadar amonia melebihi ambang batas! \n");
  } 
  
  else if (nilaippm >= 31 && nilaippm <= 50){
    delay(5000);
    konfirmasi= true;
    kondisiSwiper = true;
    dataBase();
    tbTele(lamaMundur,lamaMundur, "Kadar amonia berbahaya! \n");
  }

  else {
    delay(5000);
    konfirmasi= true;
    kondisiSwiper = true;
    dataBase();
    tbTele(lamaMundur,lamaMundur, "Kadar amonia sangat berbahaya! \n");
  }
}
//===========================Logika Eksekusi yang akan dijalankan==============================//

void loop() {
  hitungPPM();
  logikaAksi();
}

