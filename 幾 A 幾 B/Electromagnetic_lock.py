import random
import turtle
password = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
random.shuffle(password) #設定門的密碼
electricity = 1 #通電中
print("正確密碼為",password[0] ,password[1] ,password[2] ,password[3])

def drawpic():#畫共同部分
    turtle.pencolor("purple")
    turtle.left(60)
    turtle.forward(25)
    turtle.right(60)
    turtle.forward(60)
    turtle.right(120)
    turtle.forward(25)
    turtle.right(60)
    turtle.forward(60)
    turtle.penup()
    turtle.goto(23,0)
    turtle.pendown()
    turtle.write("鐵片",font=("Arial", 12, "normal"))#以上為畫鐵片
    turtle.penup()
    turtle.goto(-10,35)
    turtle.pendown()
    turtle.right(120)
    turtle.forward(25)
    turtle.right(60)
    turtle.forward(100)
    turtle.right(120)
    turtle.forward(25)
    turtle.right(60)
    turtle.forward(100)
    turtle.penup()
    turtle.goto(-10,15)
    turtle.penup()
    turtle.goto(17,35)
    turtle.pendown()
    turtle.write("矽鋼片",font=("Arial", 12, "normal"))#以上為畫矽鋼片
    turtle.penup()
    turtle.pencolor("orange")
    turtle.goto(17,57)
    turtle.pendown()
    turtle.right(90)
    turtle.forward(40)
    turtle.right(90)
    turtle.forward(150)#以上為畫電線
    turtle.left(90)
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(40)
    turtle.right(90)
    turtle.forward(40)
    turtle.right(90)
    turtle.forward(40)
    turtle.right(90)
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(10)
    turtle.penup()
    turtle.goto(193,97)
    turtle.pendown()
    turtle.forward(15)
    turtle.penup()
    turtle.goto(130,117)
    turtle.pendown()
    turtle.write("識別裝置(控制開關)",font=("Arial", 12, "normal"))#以上為畫識別裝置
    turtle.penup()
    turtle.goto(208,97)
    turtle.pendown()
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(100)#以上為畫電線
    turtle.right(90)
    turtle.forward(50)
    turtle.left(90)
    turtle.forward(100)
    turtle.left(90)
    turtle.forward(100)
    turtle.left(90)
    turtle.forward(100)
    turtle.left(90)
    turtle.forward(50)
    turtle.penup()
    turtle.goto(200,-70)
    turtle.pendown()
    turtle.write("電源",font=("Arial", 20, "normal"))#以上為畫電源
    turtle.penup()
    turtle.goto(-20,-120)
    turtle.pensize(5)
    turtle.pencolor("brown")
    turtle.pendown()
    turtle.right(90)
    turtle.forward(270)
    turtle.right(90)
    turtle.forward(320)
    turtle.right(90)
    turtle.forward(270)
    turtle.right(90)
    turtle.forward(320)
    turtle.penup()
    turtle.goto(3,150)
    turtle.pensize(1)
    turtle.pendown()
    turtle.write("電磁鎖簡易構造圖",font=("Arial", 25, "normal"))#以上為畫電磁鎖簡易構造圖
    turtle.penup()
    turtle.goto(-50,-110)
    turtle.pencolor("blue")
    turtle.left(90)
    turtle.pendown()
    turtle.right(90)
    turtle.forward(250)
    turtle.penup()
    turtle.goto(-255,-110)
    turtle.right(90)
    turtle.pendown()
    turtle.forward(205)
    turtle.right(90)
    turtle.forward(120)
    turtle.right(90)
    turtle.forward(205)
    turtle.penup()
    turtle.goto(-250,-110)
    turtle.right(180)
    turtle.pendown()
    turtle.forward(200)
    turtle.right(90)
    turtle.forward(110)
    turtle.right(90)
    turtle.forward(200)#以上為畫門框
    turtle.penup()
    turtle.goto(-120,-10)
    turtle.right(180)
    turtle.pencolor("orange")
    turtle.pendown()
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(20)
    turtle.right(90)
    turtle.forward(20)
    turtle.penup()
    turtle.goto(-120,15)
    turtle.pendown()
    turtle.write("辨識裝置",font=("Arial", 10, "normal"))#以上為畫辨識裝置
    turtle.penup()
    turtle.goto(-40,150)
    turtle.pensize(5)
    turtle.pencolor("brown")
    turtle.left(90)
    turtle.pendown()
    turtle.forward(270)
    turtle.right(90)
    turtle.forward(270)
    turtle.right(90)
    turtle.forward(270)
    turtle.right(90)
    turtle.forward(270)
    turtle.penup()
    turtle.goto(-248,160)
    turtle.pensize(1)
    turtle.pendown()
    turtle.write("實際應用",font=("Arial", 25, "normal"))#以上為畫實際應用
    turtle.penup()
    
def switchoff():#當電磁鎖通電時
    turtle.goto(177,97)
    turtle.pendown()
    turtle.pencolor("gray")
    turtle.forward(16)
    turtle.penup()
    turtle.goto(170,78)
    turtle.pendown()
    turtle.write("開關on",font=("Arial", 9, "normal"))#以上為畫on 的開關
    turtle.penup()
    turtle.goto(-250,-110)
    turtle.pencolor("blue")
    turtle.color("blue")
    turtle.begin_fill()
    turtle.left(90)
    turtle.pendown()
    turtle.forward(200)
    turtle.right(90)
    turtle.forward(110)
    turtle.right(90)
    turtle.forward(200)
    turtle.hideturtle()
    turtle.end_fill()
    turtle.penup()
    turtle.goto(-212,100)
    turtle.pendown()
    turtle.write("門close",font=("Arial", 10, "normal"))#以上為將門塗色
    turtle.penup()
    turtle.goto(-155,-5)
    turtle.pencolor("gray")
    turtle.color("gray")
    turtle.pendown()
    turtle.begin_fill()
    turtle.circle(5)
    turtle.end_fill()#以上為畫門的手把

def clearoff():#刪除電磁鎖通電時的圖
    for i in range(0,31):
        turtle.undo()

def switchon():#當電磁鎖沒有通電時
    turtle.goto(177,97)
    turtle.left(30)
    turtle.pendown()
    turtle.pencolor("gray")
    turtle.forward(16)
    turtle.penup()
    turtle.goto(170,78)
    turtle.pendown()
    turtle.write("開關off",font=("Arial", 9, "normal"))#以上為畫off 的開關
    turtle.penup()
    turtle.goto(-250,-110)
    turtle.pencolor("blue")
    turtle.color("blue")
    turtle.begin_fill()
    turtle.left(60)
    turtle.pendown()
    turtle.forward(200)
    turtle.right(120)
    turtle.forward(110)
    turtle.right(60)
    turtle.forward(200)
    turtle.hideturtle()
    turtle.end_fill()
    turtle.penup()
    turtle.goto(-211,100)
    turtle.pendown()
    turtle.write("門open",font=("Arial", 10, "normal"))#以上為將門塗色
    turtle.penup()
    turtle.goto(-175,-50)
    turtle.pencolor("gray")
    turtle.color("gray")
    turtle.pendown()
    turtle.begin_fill()
    turtle.circle(5)
    turtle.end_fill()#以上為畫門的手把
    
drawpic()
switchoff()
while (electricity == 1):
    k=0 #判斷輸入是否符合要求
    A=0 #有幾個數字位置都相同
    B=0 #有幾個只有數字相同
    print('輸入門的密碼(玩法和"幾A幾B"相同，數字不可重複，例如:1234)')
    Userinput=input()
    userinput=int(Userinput)
    if((userinput//10000)>0):
        print('只能輸入4個數字')
        continue
    input1=userinput//1000
    input2=(userinput//100)%10
    input3=(userinput//10)%10
    input4=userinput%10
    userin = [input1,input2,input3,input4]
    for i in range(0,4):
        for j in range(0,4):
            if (i!=j):
                if(userin[i]==userin[j]):
                    print('不能重複輸入相同的數字')
                    k=1
                    break
        if(k==1):
            break
    if(k==1):
        continue
    print(userin)
    for i in range(0,4):
        for j in range(0,4):
            if(userin[j]==password[i]):
                B=B+1
                if(i==j):
                    A=A+1
    B=B-A
    print(A,'A',B,'B')
    print('A為位置和數字皆正確；B為只有數字正確位置不正確')
    if(A==4):
        clearoff()
        switchon()
        print('密碼正確，圖片已更改')
        electricity = 0
        break
