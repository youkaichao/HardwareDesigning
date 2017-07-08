<!--
@author:Kaichao, You
@email:youkaichao@126.com
@date:2017/7/8
    -->

<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="MainPage.aspx.cs" Inherits="hardware.MainPage" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title>云端智能家居--电子电路队</title>
    <style type="text/css">
        #TimeAndLocation {
            height: 75px;
        }

        <!--温度计的样式表-->
        .thermometer-outer {
          background: #00ffe3;
          border: 2px solid #000000;
          border-radius: 3px;
        }
        .thermometer-outer-h {
          height: 20px;
          width: 100%;
        }
        .thermometer-outer-v {
          height: 200px;
          width: 20px;
        }
        .thermometer-inner {
          background: #ff0000;
        }
        .thermometer-inner-h {
          height: 20px;
        }
        .thermometer-inner-v {
          width: 20px;
        }
    </style>

    <script src="Scripts/jquery-3.2.1.js"></script>
    <script src="Scripts/jquery.thermometer.js"></script>

    <script src="http://cdnjs.cloudflare.com/ajax/libs/jquery-easing/1.3/jquery.easing.min.js"></script>
	<script src="Scripts/jquery.easypiechart.min.js"></script>
    
</head>
<body>
    <form id="form1" runat="server">

        <!-- 展现logo-->
        <div class="logo">
            <asp:Image ID="logo" runat="server" Height="256px" ImageAlign="Top" ImageUrl="images/logo.png" Width="100%" />
        </div>

        <!--显示时间地点-->
        <div class="TimeAndLocation">
            <asp:Label ID="TimeAndLocation" runat="server" Text="" Width="100%" Height="100%" align="center" Font-Size="XX-Large"></asp:Label>
        </div>


        <div>
            <!--展示温度-->
            <div class="myThememeter" style="float:left;width:10%">
                <p style="width: 100%; text-align: center">当前室温:<%=Application["Temperature"] %>&#8451<br />
                </p>
              
                <div id="thermometer">
                    <p><%=Application["MaxTem"] %>&#8451 <br /></p>
                  <div class="thermometer" data-percent="<%=Application["percent"] %>" data-orientation="vertical" >
                    <div class="thermometer-outer thermometer-outer-v">
                        <div class="thermometer-inner thermometer-inner-v"></div>
                    </div>
                  </div>
                    <p><%=Application["MinTem"] %>&#8451 <br /></p>
                </div>
            </div>

            

            <!--展示湿度-->
            <div class="myHumidity" style="float:left;width:30%">
                <p  style="width:100%; text-align:center">当前湿度:<%=Application["Humidity"] %>%<br /></p>
                <span class="chart" data-percent="<%=Application["Humidity"] %>">
                    <span class="percent"><%=Application["Humidity"] %></span>
                </span>
            </div>

            

            <!--展示声音-->
            <div  style="float:left;width:20%" id="Sound">
                <p  style="width:100%; text-align:center">室内音频环境:<%=Application["SoundDescriptor"] %><br /></p>
                <img src="<%=Application["SoundImage"] %>" />
            </div>

            

            <!--展示光照-->
            <div  style="float:left;width:20%" id="Light">
                <p  style="width:100%; text-align:center">室内光照环境:<%=Application["LightDescriptor"] %><br /></p>
                <img src="<%=Application["LightImage"] %>" />
            </div>

            

            <!--展示超声波-->
            <div  style="float:left;width:20%" id="Ultrasonic">
                <p  style="width:100%; text-align:center">当前朝向<%=Application["Ultrasonic"] %>cm处有障碍物<br /></p>
                <img src="images/Ultrasonic.jpg" />
            </div>
        </div>

    </form>

    <!--展示温度的脚本-->
    <script>
        $('.thermometer').thermometer();

        $(function () {
            $('.chart').easyPieChart({
                easing: 'easeOutBounce',
                size: document.getElementById('thermometer').clientHeight,
                onStep: function (from, to, percent) {
                    $(this.el).find('.percent').text(Math.round(percent));
                }
            });
        });

        
    </script>

</body>
</html>
