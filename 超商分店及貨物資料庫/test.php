<?php

    $connect_DB = mysqli_connect('127.0.0.1', 'test', 'test');
    if($connect_DB){
        //echo '連線成功';
    } 
    else{
        echo '連線失敗';
        exit();
    } 

    $flag = mysqli_select_db($connect_DB, 'test');
    if($flag){
        //echo '資料庫可用';
    } 
    else{
        echo '資料庫不可用';
        exit();
    } 

    mysqli_query($connect_DB, "SET NAMES 'utf8'");

    $sql1 = "select * from `過往紀錄的每日賣出金額` WHERE `過往紀錄的每日賣出金額`.`賣出金額`>=90 order by `過往紀錄的每日賣出金額`.`當天日期` ASC";
    $result1 = mysqli_query($connect_DB, $sql1);
    $result_sec1 = [];
    while($row = mysqli_fetch_array($result1, MYSQLI_NUM)){
        $result_sec1[] = $row;
    }

    $sql2 = "select `商品進貨資料`.`店面代碼`,`商品進貨資料`.`進貨日期` from `商品進貨資料` where `商品進貨資料`.`商品名稱`='7_雀巢雪梨茶'";
    $result2 = mysqli_query($connect_DB, $sql2);
    $result_sec2 = [];
    while($row = mysqli_fetch_array($result2, MYSQLI_NUM)){
        $result_sec2[] = $row;
    }

    $sql3 = "select `店面`.`店名`,`店面`.`地址`,`店面`.`超商名稱` from `店面` where `店面`.`地址` like '%國學街%' and `店面`.`超商名稱`='全家便利商店'";
    $result3 = mysqli_query($connect_DB, $sql3);
    $result_sec3 = [];
    while($row = mysqli_fetch_array($result3, MYSQLI_NUM)){
        $result_sec3[] = $row;
    }

?>


<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>資料庫系統HW3</title>
    <style>
        .box{
            width: 1250px;
            height: 490px;
            background-image: url("https://picsum.photos/1250/130/?random=1");
            background-repeat: no-repeat;
            margin: auto;
        }
        .column{
            width: 375px;
            height: 320px;
            background-color: #E8E8D0;
            float: left;
            margin: 10px;
            padding: 10px;
            border: 1px #888888;
            position:relative;
            top: 130px;
            overflow: hidden;
        }
        h1{
            text-align:center;
        }
        h2{
            text-align:center;
        }
        h3{
            text-align:center;
        }
        table{
            width: 375px; 
            text-align:center;
        }
    </style>
</head>
	<body style="background-color: #FFFCEC">
		<h1>HW3</h1>
        <div class="box">
            <div class="column">
                <h2>問題一</h2>
                <p>找出過去每日有賣出超過90元的日期。</p>
                <h3>答案</h3>
                <table style="border:3px #808040 solid;" cellpadding="5" border='1'>
                    <tr>
                        <th>當天日期</th>
                        <th>賣出金額</th>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec1[0][0]); ?> </td>
                        <td> <?php print_r($result_sec1[0][1]); ?> </td>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec1[1][0]); ?> </td>
                        <td> <?php print_r($result_sec1[1][1]); ?> </td>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec1[2][0]); ?> </td>
                        <td> <?php print_r($result_sec1[2][1]); ?> </td>
                    </tr>
                </table>
                
            </div>
            
            <div class="column">
                <h2>問題二</h2>
                <p>找出有進貨 ”7_雀巢雪梨茶” 的商店代碼及進貨日期。</p>
                <h3>答案</h3>
                <table style="border:3px #808040 solid;" cellpadding="5" border='1'>
                    <tr>
                        <th>店面代碼</th>
                        <th>進貨日期</th>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec2[0][0]); ?> </td>
                        <td> <?php print_r($result_sec2[0][1]); ?> </td>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec2[1][0]); ?> </td>
                        <td> <?php print_r($result_sec2[1][1]); ?> </td>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec2[2][0]); ?> </td>
                        <td> <?php print_r($result_sec2[2][1]); ?> </td>
                    </tr>
                </table>
            </div>

            <div class="column">
                <h2>問題三</h2>
                <p>找出在國學街上全家的完整地址跟店名。</p>
                <h3>答案</h3>
                <table style="border:3px #808040 solid;" cellpadding="5" border='1'>
                    <tr>
                        <th>店名</th>
                        <th>地址</th>
                        <th>超商名稱</th>
                    </tr>
                    <tr>
                        <td> <?php print_r($result_sec3[0][0]); ?> </td>
                        <td> <?php print_r($result_sec3[0][1]); ?> </td>
                        <td> <?php print_r($result_sec3[0][2]); ?> </td>
                    </tr>
                </table>
            </div>
        </div>

        
	</body>
</html>