<?php
$servername = "localhost";
$username = "root";
$password = "root";

$conn = mysqli_connect($servername,$username,$password,'itsa');

if(!$conn){
	die("Connection failed:" . mysqli_connect_error());

}

$stars = $_GET['stars'];

echo $stars;



$sql = "SELECT votes FROM feedback";
$result = mysqli_query($conn,$sql);
echo $result;

$sql = "UPDATE feedback set votes= $result+$stars";
if ($conn->query($sql) === TRUE) {
    echo "Record updated successfully";
} else {
    echo "Error updating record: " . $conn->error;
}

mysqli_close($conn);

?>
