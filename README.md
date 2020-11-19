# AmonitorAutomaticSistem

## Fuction dalam program arduino.

Function wajib
```sh
void setup () 
```

Fuction wajib untuk looping program
```sh
void loop () 
```

Abaikan
```sh
void stepPer() 
```

Untuk menghitung nilai PPM, hasil di arahkan ke variabel "float average"
```sh
void hitungPPM () 
```

Untuk push data ke index.php, masuk nya di db datasensor, value ke data
```sh
void database()
```
```sh
push datanya ke db ini, ke add.php
String url = "/amonitor/add.php?data=";
url += average;
```

Abaikan
```sh
void stepPer() 
```
# void database2() 
//push data ke logpembersihan.php, masuk di db dataswiper, value nya di data (sebagai ppm awal)
push data ke db ini, ke add2.php
String url = "/amonitor/add2.php?data=";
url += average;

Abaikan
```sh
void stepPer() 
```
# void database3() 
//push data ke logpembersihan.php, masuk di db dataswiper, value nya di data_2 (sebagai ppm akhir)
push data ke ke db ini, ke add3.php
String url = "/amonitor/add3.php?data_2=";
url += average;

Abaikan
```sh
void stepPer() 
```
# void stepPer2()
//mekanisme swiper pembersihan otomatis
//disini juga ada logic untuk ngirim data ppm akhir
if (ppm <=24){
      Serial.println("Mengirim data ppm akhir : "+ (String) average +" ke logging swiper");
      dataBase3(); // dikirim ke database2
      kondisiSwiper = false;
    }

Abaikan
```sh
void stepPer() 
```
# void tbTele()
//push notif ke telegram, dan request konfirmasi dari user

//push notif nya ke 
    Serial.println("Kadar Amonia : " + (String)average);
      delay(3000);
      String ppm_value = Notif;
      ppm_value += "Kadar Amonia : ";
      ppm_value += float(average);
      ppm_value += " ppm\n";
      myBot.sendMessage(id, ppm_value, "");
      Serial.println("Mengirim data sensor ke telegram"); 
      delay(5000);
      
//request konfirmasi dari user e
    while (konfirmasi==true) //kondisi terpenuhi user di minta ngetik "on" baru eksekusi perintah selanjut e di jalankan
    
//sistem yang dijalankan fuction
    stepPer2();

Abaikan
```sh
void stepPer() 
```
# void logikaAksi()
//Untuk jalankan semua program dengan kondisi if yang sudah ditentukan sebulumnya.

//jika if memenuhi akan eksekusi perintah
    konfirmasi= true;
    kondisiSwiper = true;
    dataBase(); 
    tbTele(int,int, "String");
    
===============================================================================================


# Algoritma sistem
1. nilai ppm di baca function
   hitungPPM(); data hasil hitung di simpan ke "float average"
   
2. logika aksi baca progam, apa data d average memenuhu if? jika iya dia akan eksekusi
   konfirmasi= true;
   kondisiSwiper = true;
   dataBase(); 
   tbTele(int,int, "String");
   
   2.1. konfirmasi = true; ini akan di terima tbTele() -> masuk ke logic while
        2.1.1. tbTele akan push data ppm ke database()
        2.1.2. while -> program di dalam while akan di eksekusi jika user konfirmasi "on"
        2.1.3. jika konfirmasi "on" -> akan push data "ppm awal" ke database2(); 
        2.1.4. setelah eksekusi push data "ppm awal" ke database2() selesai, konfirmasi = false (dikembalikan ke kondisi awal / netral).
        
   2.2. kondisiSwiper = true; ini akan di terima stepPer2() -> masuk ke logic while
        2.2.1. stepPer2 akan menjalankan perintah pembersihan
        2.2.2. setelah done dan nilai data ppm turun, nilai turun iki akan di push data ke "ppm akhir" ke database3(); 
        2.2.3. setelah eksekusi push data "ppm akhir" ke database3()selesai, kondisiSwiper = false (dikembalikan ke kondisi awal / netral).

3. sistem looping ulang ke kondisi pembacaan nilai ppm.
 

di file .cpp ada fuction, database(), database2(), database3().
penjelasan
1. database(), untuk push data ke index.php, masuknya ke db datasensor, value nya data
2. database2(), untuk push data ke logpembersihan.php, masuknya ke db dataswiper, value nya data (sebagai ppm awal)
3. database3(), untuk push data ke logpembersihan.php, masuknya ke db dataswiper, value nya data_2 (sebagai ppm akhir)
.
Masing2nya me - get menggunakan add.php, dan add2.php.
