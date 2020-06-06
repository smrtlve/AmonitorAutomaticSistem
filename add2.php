<?php
    include('koneksi.php');
 
    $sensor = $_GET['data'];
    
    $sql = "INSERT INTO dataswiper (data) VALUES (:data)";
 
    $stmt = $PDO->prepare($sql);
 
    $stmt->bindParam(':data', $sensor);
 
    if($stmt->execute()) {
        echo "sukses";
    }else{
        echo "gagal";
    }
?>
