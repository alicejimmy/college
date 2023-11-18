using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Net;//匯入網路通訊協定相關函數
using System.Net.Sockets;//匯入網路插座功能函數
using System.Threading;//匯入多執行緒功能函數
using Microsoft.VisualBasic.PowerPacks;//匯入VB向量繪圖功能

namespace 五子棋Demo
{
    public partial class Form1 : Form
    {
        public static int begin = 1;//協助判斷是否已經按下Strat!!鍵 0是已經按下 1尚未按下
        Socket T;//通訊物件
        Thread Th;//網路監聽執行緒
        string User;//使用者
        int player = 0;//0是沒人 1是甲方 2是乙方
        int now = 0;//現在換誰出棋 1是甲方 2是乙方
        int XX, YY;//存對手在上一回合下棋的座標，用來在自己棋盤上畫上對手出的棋子
        int[,] map = new int[9, 9];//存目前棋盤下棋的情況 0是沒棋子 1是甲方的黑棋 2乙方的白棋
        string stringx, stringy;//協助傳送對手在上一回合下棋的座標
        int end = 1;//0是遊戲已結束 1是遊戲還沒結束
        int key = 0;//協助判斷雙方是否都有按下START鍵
        int member = 0;//紀錄當前上線人數

        public Form1()
        {
            InitializeComponent();
        }
        private void Form1_Load(object sender, EventArgs e)
        {
        }

        private void Form1_MouseClick(object sender, MouseEventArgs e)//當滑鼠點擊遊戲視窗
        {
            if (end == 0)//遊戲已結束
            {
                textBox1.Text = "遊戲已結束請關閉視窗";
                return;
            }
            if (end == 1)//遊戲尚未結束
            {
                if (key < 2)//有一方沒按下START鍵
                {
                    textBox1.Text = "請雙方都按下 Start!! 鍵";
                    return;
                }
                else
                {
                    int x, y;//所選擇下棋位置的9*9座標
                    int Q, R;//協助將x,y轉換成9*9的座標位置
                    if (begin == 1)//尚未登入伺服器或按下Strat!!鍵
                    {
                        textBox1.Text = "請登入伺服器或按下 Start!! 鍵";
                        return;
                    }
                    if (begin == 0)//已登入伺服器且按下Strat!!鍵
                    {
                        if (member == 1)
                        {//有一人中斷連線
                            textBox1.Text = "對手已中斷連線!請關閉視窗";
                        }
                        else if (member == 2)
                        {
                            if (player != now)//非此玩家的回合
                            {
                                textBox1.Text = "Please wait for another player";
                                return;
                            }
                            else if (player == now)//為此玩家的回合
                            {
                                if (e.X < 30 || e.X > 420 || e.Y < 30 || e.Y > 420)//下棋位置超出棋盤範圍
                                {
                                    textBox1.Text = "Please click on the board";
                                    return;
                                }
                                /*以下為將滑鼠點擊位置的x和y轉換成棋盤上的9*9座標*/
                                x = e.X - 15 - 30;
                                Q = x / 45;
                                R = x % 45;
                                if (R <= 22)
                                {
                                    Q = Q;
                                }
                                else if (R > 22)
                                {
                                    Q += 1;
                                }
                                x = Q;
                                y = e.Y - 15 - 30;
                                Q = y / 45;
                                R = y % 45;
                                if (R <= 22)
                                {
                                    Q = Q;
                                }
                                else if (R > 22)
                                {
                                    Q += 1;
                                }
                                y = Q;
                                /*以上為將滑鼠點擊位置的x和y轉換成棋盤上的9*9座標*/
                                if (map[y, x] == 1 || map[y, x] == 2)//下棋位置已經有棋子了
                                {
                                    textBox1.Text = "Please don't put the chess where there are chess";
                                    textBox1.Text = x.ToString() + y.ToString() + map[y, x].ToString();
                                    return;
                                }
                                map[y, x] = now;//將下棋位置寫入map陣列
                                PutChess(x, y);//畫棋子
                                               /*以下為傳送此次下棋位置給對手*/
                                stringx = x.ToString();
                                stringy = y.ToString();
                                Send("5" + stringx);
                                Send("6" + stringy);
                                /*以上為傳送此次下棋位置給對手*/
                                Check(x, y, now);//檢查是否有任一方勝利
                            }
                        }
                    }
                }
            }
        }

        private void PutChess(int x, int y)//畫棋子
        {
            int realx, realy;//棋子實際該放入的座標
            realx = x * 45 + 30;
            realy = y * 45 + 30;
            if (now == 1)//為黑棋
            {
                Graphics paintchess = this.CreateGraphics();
                Brush brush = new SolidBrush(Color.Black);
                paintchess.FillEllipse(brush, realx, realy, 30, 30);
            }
            else if (now == 2)//為白棋
            {
                Graphics paintchess = this.CreateGraphics();
                Brush brush = new SolidBrush(Color.White);
                paintchess.FillEllipse(brush, realx, realy, 30, 30);
            }
        }

        private void Check(int Lx, int Ly, int c)//檢查是否有任一方勝利
        {
            int total = 0;//檢查棋盤目前有幾顆棋子
            int Count = 0, a, b;//Count輔助計算是否有五顆相同顏色的棋子連成一線
            /*以下為下棋位置的整個直排的檢查*/
            a = Lx;
            b = 0;
            while (b < 9)
            {
                int k = map[b, a];
                if (k == c)
                {
                    Count++;
                }
                if (Count == 5)
                {
                    message(c);
                    return;
                }
                if (k != c)
                {
                    Count = 0;
                }
                b += 1;
            }
            /*以上為下棋位置的整個直排的檢查*/
            /*以下為下棋位置的整個橫排的檢查*/
            b = Ly;
            Count = 0;
            a = 0;
            while (a < 9)
            {
                int k = map[b, a];
                if (k == c)
                {
                    Count++;
                }
                if (Count == 5)
                {
                    message(c);
                    return;
                }
                if (k != c)
                {
                    Count = 0;
                }
                a += 1;
            }
            /*以上為下棋位置的整個橫排的檢查*/
            /*以下為下棋位置的由左到右的斜排檢查*/
            Count = 0;
            a = Lx;
            b = Ly;
            if (a > b)
            {
                a = a - b;
                b = 0;
            }
            else if (a < b)
            {
                b = b - a;
                a = 0;
            }
            else if (a == b)
            {
                a = 0;
                b = 0;
            }
            while (a >= 0 && b >= 0 && a < 9 && b < 9)//往右下檢查
            {
                int k = map[b, a];
                if (k == c)
                {
                    Count++;
                }
                if (Count == 5)
                {
                    message(c);
                    return;
                }
                if (k != c)
                {
                    Count = 0;
                }
                a += 1;
                b += 1;
            }
            /*以上為下棋位置的由左上到右下的斜排檢查*/
            /*以下為下棋位置的由左下到右上的斜排檢查*/
            Count = 0;
            a = Lx;
            b = Ly;
            if (a > b)
            {
                a = a + b;
                b = 0;
            }
            else if (a < b)
            {
                b = b - a;
                a = 8;
            }
            else if (a == b)
            {
                a = 8;
                b = 0;
            }

            while (a >= 0 && b >= 0 && a < 9 && b < 9)//往左下
            {
                int k = map[b, a];
                if (k == c)
                {
                    Count++;
                }
                if (Count == 5)
                {
                    message(c);
                    return;
                }
                if (k != c)
                {
                    Count = 0;
                }
                a -= 1;
                b += 1;
            }
            /*以上為下棋位置的由左下到右上的斜排檢查*/

            for (int i = 0; i < 9; i++)
            {
                for (int j = 0; j < 9; j++)
                {
                    if (map[j, i] != 0)
                    {
                        total += 1;
                    }
                }
            }
            if (total == 81)
            {
                c = 3;
                message(c);
                return;
            }
        }

        private void message(int c)//若有五個以上的相同顏色連成一線，則輸出訊息
        {
            if (c == 1)
            {
                if (player == 1)
                {
                    textBox2.Text = "You win";
                }
                if (player == 2)
                {
                    textBox2.Text = "You lose";
                }
                MessageBox.Show("Winner is Black!!!!!");
            }
            if (c == 2)
            {
                if (player == 2)
                {
                    textBox2.Text = "You win";
                }
                if (player == 1)
                {
                    textBox2.Text = "You lose";
                }
                MessageBox.Show("Winner is White!!!!!");
            }
            if (c == 3)
            {
                textBox2.Text = "平手";
                MessageBox.Show("平手");
            }
            end = 0;
        }

        private void button1_Click(object sender, EventArgs e)//Start!! 鍵
        {
            begin = 0;//已按下Start!! 鍵
            button1.Enabled = false;//讓Start!! 鍵只能按一次
            textBox2.Text = "Now is Black";
            now = 1;//黑色先下棋
            key++;
            if (player == 0)//先按下Start!! 鍵者為甲方(黑棋)
            {
                textBox1.Text = "你為黑棋，黑棋先出";
                player = 1;
                Send("2" + key.ToString());//使另一方為乙方(白棋)

            }
            if (player == 2)
            {
                Send("2" + key.ToString());
            }
            for (int i = 0; i < 9; i++)//清空棋盤
            {
                for (int j = 0; j < 9; j++)
                {
                    map[i, j] = 0;
                }
            }
        }

        private void Listen()
        {
            EndPoint ServerEP = (EndPoint)T.RemoteEndPoint; //Server 的 EndPoint
            byte[] B = new byte[1023]; //接收用的 Byte 陣列
            int inLen = 0; //接收的位元組數目
            string Msg; //接收到的完整訊息
            string St; //命令碼
            string Str; //訊息內容(不含命令碼)
            while (true)//無限次監聽迴圈
            {
                try
                {
                    inLen = T.ReceiveFrom(B, ref ServerEP);//收聽資訊並取得位元組數
                }
                catch (Exception)//產生錯誤時
                {
                    T.Close();//關閉通訊器
                    ListBox1.Items.Clear();//清除線上名單
                    MessageBox.Show("伺服器斷線了！");//顯示斷線
                    button3.Enabled = true;//連線按鍵恢復可用
                    Th.Abort();//刪除執行緒
                }
                Msg = Encoding.Default.GetString(B, 0, inLen); //解讀完整訊息
                St = Msg.Substring(0, 1); //取出命令碼 (第一個字)
                Str = Msg.Substring(1); //取出命令碼之後的訊息   

                switch (St)//依命令碼執行功能
                {
                    case "L"://接收線上名單
                        ListBox1.Items.Clear(); //清除名單
                        string[] M = Str.Split(','); //拆解名單成陣列
                        member = M.Length;
                        for (int i = 0; i < M.Length; i++)
                        {
                            ListBox1.Items.Add(M[i]); //逐一加入名單
                        }
                        textBox1.Text = "已連線伺服器！" + "\r\n";//若是連線成功則輸出文字
                        button3.Enabled = false;//讓連線按鈕無法使用避免重複連線
                        break;
                    case "2"://使另一方為乙方(白棋)
                        if (player == 0)
                        {

                            textBox1.Text = "你為白棋，白棋後出";
                            player = 2;
                        }
                        key = int.Parse(Str);
                        break;
                    case "5"://接收對手下棋位置的x
                        XX = int.Parse(Str);
                        break;
                    case "6"://接收對手下棋位置的y，並在自己的棋盤上畫上對手的棋子，且換人下棋
                        YY = int.Parse(Str);
                        another(XX, YY);
                        if (end == 1)
                        {
                            if (now == 1)
                            {
                                textBox2.Text = "Now is White";
                                now = 2;
                            }
                            else if (now == 2)
                            {
                                textBox2.Text = "Now is Black";
                                now = 1;
                            }
                        }
                        break;
                }
            }
        }

        private void another(int XX, int YY)//在自己的棋盤上畫上對手的棋子，並檢查對手是否勝利
        {
            if (player != now)
            {
                PutChess(XX, YY);
                map[YY, XX] = now;
                Check(XX, YY, now);
            }
        }

        private void Send(string Str)
        {
            byte[] B = Encoding.Default.GetBytes(Str); //翻譯文字為Byte陣列
            T.Send(B, 0, B.Length, SocketFlags.None); //使用連線物件傳送資料
        }

        private void Form1_Load_1(object sender, EventArgs e)
        {

        }

        private void button3_Click(object sender, EventArgs e)
        {
            CheckForIllegalCrossThreadCalls = false; //忽略跨執行緒錯誤
            User = textBox5.Text;//使用者名稱
            string IP = textBox4.Text;//伺服器IP
            int Port = int.Parse(textBox3.Text);//伺服器Port
            //建立通訊物件，參數代表可以雙向通訊的TCP連線
            try
            {
                IPEndPoint EP = new IPEndPoint(IPAddress.Parse(IP), Port);//伺服器的連線端點資訊
                T = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                T.Connect(EP); //連上伺服器的端點EP(類似撥號給電話總機)
                Th = new Thread(Listen); //建立監聽執行緒
                Th.IsBackground = true; //設定為背景執行緒
                Th.Start(); //開始監聽
                button1.Enabled = true;//可以按下STRART鍵
                Send("0" + User);  //連線後隨即傳送自己的名稱給伺服器
                textBox1.Text = "人數已滿！請關閉視窗重新開啟" + "\r\n";//預設輸出人數已滿
            }
            catch (Exception)
            {
                textBox1.Text = "無法連上伺服器！"; //連線失敗時顯示訊息
                return;
            }
            button3.Enabled = false; //讓連線按鍵失效，避免重複連線
        }

        protected override void WndProc(ref Message msg)//若是關閉視窗
        {
            const int WM_SYSCOMMAND = 0x0112;
            const int SC_CLOSE = 0xF060;
            if (msg.Msg == WM_SYSCOMMAND && ((int)msg.WParam == SC_CLOSE))
            {
                Send("9" + User); //傳送自己的離線訊息給伺服器
                T.Close(); //關閉網路通訊器
                           // 點選winform右上關閉按鈕
                           // 加入想要的邏輯處理
                this.Close();
                Environment.Exit(Environment.ExitCode);
                InitializeComponent();
                return;
            }
            base.WndProc(ref msg);
        }
    }
}
