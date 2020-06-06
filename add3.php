<?php
    include('koneksi.php');
 
    $sensor = $_GET['data_2'];
    
    $sql = "INSERT INTO dataswiper (data_2) VALUES (:data_2)";
 
    $stmt = $PDO->prepare($sql);
 
    $stmt->bindParam(':data_2', $sensor);
 
    if($stmt->execute()) {
        echo "sukses";
    }else{
        echo "gagal";
    }
?>
