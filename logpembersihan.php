<!DOCTYPE html>
  <html>
    <head>  
        <meta http-equiv=refresh content=60>
        <title>Logging Pembersihan</title>
    </head>
  
      <body>
        <style>
          #wntable {
            border-collapse: collapse;
            width:45%;
          }
  
          #wntable td, #wntable th {
            border: 1px solid #ddd;
            padding: 5px;
          }R
  
          #wntable tr:nth-child(even){background-color: #f2f2f2;}
  
          #wntable tr:hover {background-color: #ddd;}

          #wntable th {
            padding-top: 12px;
            padding-bottom: 12px;
            text-align: center;
            background-color: #337ab7;
            color: white;
          }

        </style>
  
        <div id="cards" class="cards" align="center" align>
          <h1> Logging Data Pembersihan Terakhir</h1>

          <button style="width: 200px; height: 25px;" onclick="window.location.href='./index.php'">Data Sensor</button>
          <button style="width: 200px; height: 25px;" onclick="window.location.href='./logpembersihan.php'">Logging Data Pembersihan</button>
          <br>
          <br>

          <form action="" method="post">
              <input type="date" name="data">
              <input type="time" name="data">
              <input type="submit" name="submit" value="Cari Data">
          </form>

        <?php
          include('koneksi.php');
          if($_SERVER['REQUEST_METHOD'] == "POST") {
              $dataWaktu = $_POST['data'];
              $sql = "SELECT * FROM dataswiper WHERE waktu LIKE '%" . $dataWaktu . "%' ORDER BY id DESC";
          }else{
              $dataActual = date('Y-m');
              $sql = "SELECT * FROM dataswiper WHERE waktu LIKE '%" . $dataActual . "%' ORDER BY id DESC";
          }
  
          $stmt = $PDO->prepare($sql);
          $stmt->execute();
          echo "<br>";
          echo "<table id=wntable>";
          echo "<tr> <th>Waktu</th> 
                     <th>Tanggal</th>
                     <th>Log PPM Awal</th>
                     <th>Log PPM Akhir</th>
                     <th>Durasi Pembersihan (/s)</th></tr>";

          //proses seleksi
          //membuat variabel array untuk menampung data yg diseleksi
          $tampung = array();
          //untuk kolom data
          $tampung['awal'] = array();
          //untuk kolom data2
          $tampung['akhir'] = array();
          while ($tampil = $stmt->fetch(PDO::FETCH_OBJ)){
                //cek apakah data tidak kosong
                if ($tampil->data != '') {
                  //jika data tidak kosong maka 1 baris nilai di data tadi akan ditampung di variabel array awal
                  $tampung['awal'][] = array(
                    'waktu' => date('H:i:s', strtotime($tampil->waktu)), 
                    'tanggal' => date('d M Y', strtotime($tampil->waktu)), 
                    'data' => $tampil->data, 
                    'durasi' => date('i:s', strtotime($tampil->waktu)) 
                  );
                }

                //cek apakah data2 kosong
                if ($tampil->data_2 != '') {
                  //jika data tidak kosong maka 1 baris nilai di data tadi akan ditampung di variabel array awal
                  $tampung['akhir'][] = array(
                    'waktu' => date('H:i:s', strtotime($tampil->waktu)), 
                    'tanggal' => date('d M Y', strtotime($tampil->waktu)), 
                    'data' => $tampil->data_2, 
                    'durasi' => date('i:s', strtotime($tampil->waktu)) 
                  );
                }
              
                //jika data dan data2 kosong, maka tidak akan dieksekusi
          }
          
          //proses output ke tabel
          foreach ($tampung['akhir'] as $key => $value) {
              echo "<tr align=center>";
              echo "<td>" . $value['waktu'] . "</td>";
              echo "<td>" . $value['tanggal'] . "</td>";
              echo "<td>" . $tampung['awal'][$key]['data'] . "</td>";
              echo "<td>" . $value['data'] . "</td>";

              //proses pengurangan durasi
              //ini durasi dari array data2
              $date1 = new DateTime($value['waktu']);
              //ini durasi dari array data
              $date2 = new DateTime($tampung['awal'][$key]['waktu']);
              $diff = $date1->diff($date2);
              // var_dump($diff);
              // die();
              echo "<td>" . $diff->format('%s'). "</td>";
              echo "</tr>";
          }
          echo "</div>";
          echo "</table>";
        ?>
        </div>
    </body>
  </html>