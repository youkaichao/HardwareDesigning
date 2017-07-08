/*
 * @author:Kaichao, You
 * @email:youkaichao@126.com
 * @date:2017/7/8
 */

using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;


namespace hardware
{
    
    public partial class MainPage : System.Web.UI.Page
    {
        static bool first = true;
        protected void Page_Load(object sender, EventArgs e)
        {
            if(first)
            {
                //设置默认值
                Application.Lock();

                Application["TimeAndLocation"] = "当前地点：清华大学紫荆公寓1号楼 当前时间：" + DateTime.Now.ToString();
                Application["Temperature"] = "35";
                Application["Humidity"] = 50;
                Application["MaxTem"] = 40;
                Application["MinTem"] = 0;
                Application["Sound"] = "0";
                Application["SoundDescriptor"] = "安静";//在HTML中显示的文字
                Application["SoundImage"] = "images/quiet.png";//在HTML中显示的图片

                Application["Light"] = "0";
                Application["LightDescriptor"] = "幽暗";//在HTML中显示的文字
                Application["LightImage"] = "images/dark.png";//在HTML中显示的图片

                Application["Ultrasonic"] = "0";//超声波测距

                Application.UnLock();

                first = false;
            }

            Application["TimeAndLocation"] = "当前地点：清华大学紫荆公寓1号楼 当前时间：" + DateTime.Now.ToString();

            if (Request.QueryString["Temperature"] == null)
            {//页面被别人请求
                TimeAndLocation.Text = (string)Application["TimeAndLocation"];
            }
            else
            {//自己在传输数据
                Application["Temperature"] = Request.QueryString["Temperature"];
                Application["Humidity"] = Request.QueryString["Humidity"];
                Application["Sound"] = Request.QueryString["Sound"];//值为字符串的0或者1
                Application["Light"] = Request.QueryString["Light"];//值为字符串的0或者1
                Application["Ultrasonic"] = Request.QueryString["Ultrasonic"];

                if ((String)Application["Sound"] == "1")
                {
                    Application["SoundDescriptor"] = "喧嚣";
                    Application["SoundImage"] = "images/noisy.jpg";//在HTML中显示的图片
                }
                else
                {
                    Application["SoundDescriptor"] = "安静";
                    Application["SoundImage"] = "images/quiet.png";//在HTML中显示的图片
                }

                if ((String)Application["Light"] == "1")
                {
                    Application["LightDescriptor"] = "亮堂";
                    Application["LightImage"] = "images/bright.png";//在HTML中显示的图片
                }
                else
                {
                    Application["LightDescriptor"] = "幽暗";
                    Application["LightImage"] = "images/dark.png";//在HTML中显示的图片
                }

            }
            


            //温度计的显示百分比
            
            Application["percent"] = (int.Parse((String)Application["Temperature"]) - (int)Application["MinTem"]) / 
                (double)((int)Application["MaxTem"] - (int)Application["MinTem"]) * 100; 
        }
    }
}