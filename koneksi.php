<?php
    try {
        $host = "localhost";
        $username = "root";
        $password = "";
        $dbname = "amonitor";
 
        $PDO = new PDO("mysql:host=" . $host . ";dbname=" . $dbname . ";charset=utf8", $username, $password);
    } catch (PDOException $erro) {
        echo "Gagal Terhubung ke database : " . $erro->getMessage();
    }
 
?>