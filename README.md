# AmonitorAutomaticSistem
# Tak upload sisan file arduino e, format e .cpp, be e butuh ndelok tutuk ndik push data e

=======================================================================================================
# Fuction2 sing tak bikin ndik main.cpp (code arduino ne).
# void setup () 
//abaikan iki basic e arduino
# void loop () 
//basic e arduino funsi e gae nge loop progam (istilah e gae jalankan sistem program e ndik kene)
# void stepPer() 
// abaikan disik g tak gae


# void hitungPPM () 
// Iki gae ngitung nilai PPM, hasil e tak lempar ndik variabel "float average"


# void database() 
// iki gae push data nang index.php, masuk e ndik db datasensor, value e ndik data
push data e ke db ini, ke add.php
String url = "/amonitor/add.php?data=";
url += average;


# void database2() 
//iki push data nang logpembersihan.php, masuk e ndik db dataswiper, value e ndik data (iki sing sebagai ppm awal)
push data e ke db ini, ke add2.php
String url = "/amonitor/add2.php?data=";
url += average;


# void database3() 
//iki push data nang logpembersihan.php, masuk e ndik db dataswiper, value e ndik data_2 (iki sing sebagai ppm akhir)
push data e ke db ini, ke add3.php
String url = "/amonitor/add3.php?data_2=";
url += average;


# void stepPer2()
//iki gae mekanisme swiper pembersihan otomatis e
//anggap ae ketika iki fuction iki di panggil langsung eksekusi pembersihan
//disini juga ada logic untuk ngirim data ppm akhir
if (ppm <=24){
      Serial.println("Mengirim data ppm akhir : "+ (String) average +" ke logging swiper");
      dataBase3(); // dikirim ke database2
      kondisiSwiper = false;
    }

# void tbTele()
//iki gae push notif ke telegram, ambik request konfirmasi dari user

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

# void logikaAksi()
//iki gae jalankan kabeh program e dengan kondisi if sing ws tak tentukan ndik code e..

//di jika if memenuhi akan eksekusi perintah
    konfirmasi= true;
    kondisiSwiper = true;
    dataBase(); 
    tbTele(int,int, "String");
    
===============================================================================================


# Algoritma sistem e
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
 

ndik file .cpp iku aku ws bikin fuction, database(), database2(), database3().
penjelasan
1. database(), iku push data nang index.php, masuk e ndik db datasensor, value e ndik data
2. database2(), iku push data nang logpembersihan.php, masuk e ndik db dataswiper, value e ndik data (iki sing sebagai ppm awal)
3. database3(), iku push data nang logpembersihan.php, masuk e ndik db dataswiper, value e ndik data_2 (iki sing sebagai ppm akhir)
.
oh iyo masing2 e nge get e nggae add.php, ambik add2.php, asline iso di dadi no siji ndik add.php, tapi aku durung ngerti carane, makane malih nggae add2.php XD..
