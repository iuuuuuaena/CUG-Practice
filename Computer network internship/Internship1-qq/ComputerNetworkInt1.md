---
title: 计算机网络实习一--QQ
date: 2019-03-13 13:38:16
tags: [Python,tkinter,socket]
categories: 实习
toc: true
menu_highlight: true
---
# UDP-主要负责和服务端联系的类
```python
import socket
class UDP:
    # 初始化
    def __init__(self):
        self.HOST = '202.114.196.97'
        self.PORT = 21568
        self.BUFSIZ = 1024
        self.ADDR = (self.HOST, self.PORT)
        self.udpCliSock=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        print('初始化')
    def __del__(self):
        self.udpCliSock.close()
    #修改密码
    def changePsd(self,usr_name,usr_old_pwd,usr_new_pwd,usr_pwd_confirm):
        data='01#'+usr_name+'#'+usr_old_pwd+'#'+usr_new_pwd+'#'+usr_pwd_confirm+'#'
        self.send(data)
        return self.recv()
    #用户登陆
    def login(self,usr_num,usr_pwd):
        data='02#'+usr_num+'#'+usr_pwd+'#'
        self.send(data)
        return self.recv()
    #向单个好友发送消息
    def chatOne(self,frd_num,message):
        data='03#'+frd_num+'#'+message+'#'
        self.send(data)
        return self.recv()
    #接受单个好友消息
    def recvOne(self,frd_num):
        data='04#'+frd_num+'#'
        self.send(data)
        recv_data=self.recv()
        if recv_data=='07:01' or recv_data[3:]=='0':
            return recv_data
        else:
            messages=list()
            num=eval(recv_data[3:])
            data='05#'+frd_num+'#'
            for i in range(num):
                self.send(data)
                messages.append(self.recv())
        return messages
    #接受多个好友消息
    def recvAll(self):
        data = '08#'
        self.send(data)
        recv_data = self.recv()
        if recv_data=='07:01' or recv_data[3:]=='0':
            return recv_data
        else:
            messages=list()
            num=eval(recv_data[3:])
            data='09#'
            for i in range(num):
                self.send(data)
                messages.append(self.recv())
        return messages
    #离线
    def Offline(self):
        data='06#'
        self.send(data)
        return self.recv()
    '''--------------------------------------------------------'''
    #发送信息
    def send(self,data):
        self.udpCliSock.sendto(data.encode(), self.ADDR)
    #接受信息
    def recv(self):
        data, addr = self.udpCliSock.recvfrom(self.BUFSIZ)
        #print(data.decode())
        return data.decode()
    def __del__(self):
        self.udpCliSock.close()
```
	首先在类初始化时，绑定要联系的服务端地址，在类对象被销毁时，关闭被创建的套接字。其他函数按照通信协议直接编写。
# Login-登陆界面
```python
import tkinter as tk
import tkinter.messagebox
import pickle
import UDP
import Main

#command
def login(usr_name,usr_pwd):
    # 创建新窗口
    # root.destroy()
    # newwindow = Main.MainWindow()
    # newwindow.trans(udp)
    # newwindow.mainloop()
    recv = udp.login(usr_name, usr_pwd)
    if recv == '02:01':
        tk.messagebox.showinfo(title='ok', message='login successful')
        #udp.Offline()
        # 创建新窗口
        root.destroy()
        newwindow=Main.MainWindow()
        newwindow.trans(udp)
        newwindow.mainloop()

    elif recv == '02:02':
        tk.messagebox.showerror(title='Error', message='Wrong password')
    elif recv == '02:03':
        tk.messagebox.showerror(title='Error', message='User does not exist')
    elif recv == '02:04':
        tk.messagebox.showwarning(title='Warning', message='User has logged in')
        root.destroy()
        newwindow = Main.MainWindow()
        newwindow.trans(udp)
        newwindow.mainloop()
    else:
        tk.messagebox.showerror(title='Error', message='unknown wrong')

def usr_login():
    usr_name=var_usr_name.get()
    usr_pwd=var_usr_pwd.get()
    login(usr_name, usr_pwd)

def usr_sign_up():
    def sign_up():
        np=new_pwd.get()
        npf=new_pwd_confirm.get()
        nn=new_name.get()
        # 发送注册请求
        # if np != npf:
        #     tk.messagebox.showerror('Error', 'Password and confirm password must be the same!')
        # 已经注册：
        #     tk.messagebox.showerror('Error', 'The user has already signed up!')
        # 注册成功：
        #     exist_usr_info[nn] = np
        #     with open('usrs_info.pickle', 'wb') as usr_file:
        #         pickle.dump(exist_usr_info, usr_file)
        #     tk.messagebox.showinfo('Welcome', 'You have successfully signed up!')
        #     window_sign_up.destroy()
    window_sign_up=tk.Toplevel(root)
    Main.center_window(window_sign_up,350,200)
    window_sign_up.title('Sign up window')

    new_name = tk.StringVar()
    new_name.set('example@python.com')
    tk.Label(window_sign_up, text='User name: ').place(x=10, y=10)
    entry_new_name = tk.Entry(window_sign_up, textvariable=new_name)
    entry_new_name.place(x=150, y=10)

    new_pwd = tk.StringVar()
    tk.Label(window_sign_up, text='Password: ').place(x=10, y=50)
    entry_usr_pwd = tk.Entry(window_sign_up, textvariable=new_pwd, show='*')
    entry_usr_pwd.place(x=150, y=50)

    new_pwd_confirm = tk.StringVar()
    tk.Label(window_sign_up, text='Confirm password: ').place(x=10, y=90)
    entry_usr_pwd_confirm = tk.Entry(window_sign_up, textvariable=new_pwd_confirm, show='*')
    entry_usr_pwd_confirm.place(x=150, y=90)

    btn_comfirm_sign_up = tk.Button(window_sign_up, text='Sign up', command=sign_up)
    btn_comfirm_sign_up.place(x=150, y=130)

udp=UDP.UDP()
root=tk.Tk()
root.title('Welcome to Chat')
Main.center_window(root,450,300)

#image
canvas=tk.Canvas(root,height=140,width=500)
image_file=tk.PhotoImage(file='./Resources/welcome.gif')
image=canvas.create_image(0,0,anchor='nw',image=image_file)
canvas.pack(side='top')

#user information
tk.Label(root,text='User name:').place(x=50,y=150)
tk.Label(root,text='Password:').place(x=50,y=190)
var_usr_name=tk.StringVar()
var_usr_name.set('2017100xxxx')
entry_usr_name=tk.Entry(root,textvariable=var_usr_name)
entry_usr_name.place(x=160,y=150)
var_usr_pwd=tk.StringVar()
entry_usr_pwd=tk.Entry(root,textvariable=var_usr_pwd,show='*')
entry_usr_pwd.place(x=160,y=190)

#login and sign up button
btn_login=tk.Button(root,text='Login',command=usr_login)
btn_login.place(x=150,y=230)
btn_sign_up=tk.Button(root,text='Sign up',command=usr_sign_up)
btn_sign_up.place(x=250,y=230)

root.mainloop()
```
	Login是整个程序的入口，利用tkinter创建界面，提供登陆与注册功能。在此段代码中，new一个UDP的对象，并在登陆成功后传递给Main类。
# Main类-程序的主窗口
```python
import tkinter as tk
from tkinter import messagebox
import Chat
import socket
import threading
def center_window(root, width, height):
    screenwidth = root.winfo_screenwidth()
    screenheight = root.winfo_screenheight()
    size = '%dx%d+%d+%d' % (width, height, (screenwidth - width)/2, (screenheight - height)/2)
    #print(size)
    root.geometry(size)

class MainWindow(tk.Tk):
    def __init__(self):
        super().__init__()
        #self.geometry('345x700')
        center_window(self,345,700)
        self.title('Sample Chat')
        self.protocol("WM_DELETE_WINDOW",func=self.exit)
        self.read_file()
        #添加与删除好友
        self.var_name=tk.StringVar()
        self.name_entry=tk.Entry(self,textvariable=self.var_name)
        self.name_entry.place(x=10,y=10,height=30,width=200)
        self.btn_add=tk.Button(self,text='Add',command=self.add_friend)
        self.btn_add.place(x=220,y=10)
        self.btn_del = tk.Button(self, text='Delete', command=self.del_friend)
        self.btn_del.place(x=270, y=10)

        #好友列表
        self.lb_var=tk.StringVar()
        self.lb=tk.Listbox(self,listvariable=self.lb_var,height=33,width=40)
        for item in self.friends:
            self.lb.insert('end',item)
        self.lb.place(x=10,y=50)

        #聊天、退出、与修改密码
        self.btn_chat = tk.Button(self, text='Chat', command=self.chat,width=10)
        self.btn_chat.place(x=10, y=650)
        self.btn_quit = tk.Button(self, text='Exit', command=self.exit,width=10)
        self.btn_quit.place(x=100, y=650)
        self.btn_changePwd = tk.Button(self, text='Change Password', command=self.change_pwd,width=15)
        self.btn_changePwd.place(x=200, y=650)
        self.udp_ser=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)

        addr=('',21567)
        self.udp_ser.bind(addr)

        #多线程
        self.running=True
        self.t=threading.Thread(target=self.pro_mess,args=())
        self.t.start()

    #消息处理
    def pro_mess(self):
        while self.running:
            data,addr=self.udp_ser.recvfrom(1024)
            print(data.decode())
            datalist=data.decode().split('#')
            #发送消息
            if datalist[0]=='03':
                recv=self.udp.chatOne(self.friends[datalist[1]],datalist[2])
                self.udp_ser.sendto(recv.encode(),addr)
            #接收消息
            elif datalist[0]=='04':
                messagelist=self.udp.recvOne(self.friends[datalist[1]])
                if messagelist=='07:01' or messagelist[3:]=='0':
                    self.udp_ser.sendto(messagelist.encode(), addr)
                else:
                    length=len(messagelist)
                    self.udp_ser.sendto(str(length).encode(),addr)
                    for i in range(length):
                        self.udp_ser.sendto(messagelist[i].encode(), addr)

    #添加好友
    def add_friend(self):
        f_name=self.var_name.get()
        if f_name in self.all:
            print('add')
            self.lb.insert('end',f_name)
            self.friends[f_name]=self.all[f_name]
        else:
            tk.messagebox.showwarning(title='Can\'t find',message='Please check your input')
    #删除好友
    def del_friend(self):
        print('delete')
        del self.friends[self.lb.get('active')]
        self.lb.delete(self.lb.curselection())
    #创建聊天
    def chat(self):
        name=self.lb.get('active')
        print('chat with '+name)
        newchat=Chat.Chat()
        newchat.trans(name,self.friends[name])
        newchat.mainloop()
    #修改密码
    def change_pwd(self):
        print('修改密码')
        def changepwd():
            nn = new_name.get()
            np = new_pwd.get()
            op = old_pwd.get()
            npf = new_pwd_confirm.get()
            recv = self.udp.changePsd(nn, op, np, npf)
            if recv == '01:01':
                tk.messagebox.showerror(title='Error', message='User initial password error')
            elif recv == '01:02':
                tk.messagebox.showerror(title='Error', message='Two passwords are inconsistent')
            elif recv == '01:03':
                isLogin = tk.messagebox.askyesno(title='OK',
                                                 message='Change password successfully, whether to log in directly?')
                if isLogin:
                    pass# login(nn, np)
            elif recv == '01:04':
                tk.messagebox.showerror(title='Error', message='User does not exist')
            else:
                print(recv)
                tk.messagebox.showerror(title='Error', message='Unknown wrong')

        root_change = tk.Toplevel(self)
        center_window(root_change, 350, 250)
        root_change.title('Change Password')

        new_name = tk.StringVar()
        new_name.set('2017100xxxx')
        tk.Label(root_change, text='User name: ').place(x=10, y=10)
        entry_new_name = tk.Entry(root_change, textvariable=new_name)
        entry_new_name.place(x=150, y=10)

        old_pwd = tk.StringVar()
        tk.Label(root_change, text='Old Password:').place(x=10, y=50)
        entry_old_pwd = tk.Entry(root_change, textvariable=old_pwd, show='*')
        entry_old_pwd.place(x=150, y=50)

        new_pwd = tk.StringVar()
        tk.Label(root_change, text='Password: ').place(x=10, y=90)
        entry_usr_pwd = tk.Entry(root_change, textvariable=new_pwd, show='*')
        entry_usr_pwd.place(x=150, y=90)

        new_pwd_confirm = tk.StringVar()
        tk.Label(root_change, text='Confirm password: ').place(x=10, y=130)
        entry_usr_pwd_confirm = tk.Entry(root_change, textvariable=new_pwd_confirm, show='*')
        entry_usr_pwd_confirm.place(x=150, y=130)

        btn_comfirm_sign_up = tk.Button(root_change, text='Change Password', command=changepwd)
        btn_comfirm_sign_up.place(x=150, y=170)
    #读文件
    def read_file(self):
        self.all=dict()
        self.friends=dict()
        try:
            file_All=open('./Resources/AllPeople.txt','r',encoding='utf-8')
            for line in file_All:
                self.all[line[:-13]]=line[-12:-1]
            #print(self.all)
            file_All.close()
        except:
            print('Error_All')
        try:
            #self.file_Friends=open('./Resources/Friends.txt','r+',encoding='utf-8')
            with open('./Resources/Friends.txt','r+',encoding='utf-8') as f:
                for line in f:
                    self.friends[line[:-13]] = line[-12:-1]
            #print(self.friends)
            #file_Friends.close()
        except:
            print('Error_Friends')
    #退出时重写文件
    def write_file(self):
        try:
            with open('./Resources/Friends.txt','r+',encoding='utf-8') as f:
                f.seek(0)
                f.truncate()#清空文件以重写
                #f= open('./Resources/Friends.txt', 'r+', encoding='utf-8')
                for item in self.friends:
                    s=item+':'+str(self.friends[item])+'\n'
                    f.write(s)
            # self.file_Friends.close()
        except:
            print('Write Error')
    def trans(self,_udp):
        self.udp=_udp
        print('udp连接成功')
    #退出
    def exit(self):
        if tk.messagebox.askyesno(title='quit?',message='Do you sure you want to quit?'):
            print('离线')
            self.running=False
            #self.t.join()
            self.write_file()
            self.udp_ser.close()
            self.udp.Offline()
            del self.udp
            self.destroy()
    # def __del__(self):
    #     print('del')
    #     self.write_file()
    # def exit(self):
    #     print('离线')
    #     self.write_file()
    #     #self.quit()
    #     self.destroy()

if __name__ == '__main__':
    app=MainWindow()
    app.mainloop()
```
	程序的主窗口，提供添加与删除好友功能。添加与删除好友功能利用读取文件的方式，所以无法同步至服务器，只能在本地进行。
	好友列表显示采用tkinter的Listbox显示，选择一个好友按chat按钮开始聊天,创建一个新的Chat类的对象。
	在类初始化时创建一个新的套接字来与各个子窗口联系。
	类中的pro_mess函数处理来自各个聊天子窗口的消息，先接受子窗口的消息，判断消息类型，然后通过传入的udp与服务器端联系，并将服务器端返回的消息发送回子窗口，pro_mess函数通过一个新的线程来运行，但是有bug：
		> 关闭套接字总发送在该线程关闭后。所以会导致“OSError: [WinError 10038] 在一个非套接字上尝试了一个操作。”同时也会引起一系列的关于threading的错误。
	该问题待解决。
# Chat-与好友聊天的子窗口
```python
import tkinter as tk
import time
import socket
from tkinter import messagebox
import threading
def center_window(root, width, height):
    screenwidth = root.winfo_screenwidth()
    screenheight = root.winfo_screenheight()
    size = '%dx%d+%d+%d' % (width, height, (screenwidth - width)/2, (screenheight - height)/2)
    #print(size)
    root.geometry(size)
class Chat(tk.Tk):
    def __init__(self):
        super().__init__()
        #self.geometry('345x700')
        center_window(self,570,425)
        self.title('Chatting with ' + 'xxx')
        self.create()
        self.protocol("WM_DELETE_WINDOW",func=self.exit)

        self.udp_cli=socket.socket(socket.AF_INET,socket.SOCK_DGRAM)
        self.ADDR=('localhost',21567)
        #多线程
        self.running=True
        self.t=threading.Thread(target=self.recvmessage,args=())
        self.t.start()
    def trans(self,name,port):
        self.title('Chatting with '+name)
        self.name=name
        self.PORT=port
    def create(self):
        # 创建几个frame作为容器
        frame_left_top = tk.Frame(self,width=380, height=270, bg='white')
        frame_left_center = tk.Frame(self,width=380, height=100, bg='white')
        frame_left_bottom = tk.Frame(self,width=380, height=20)
        frame_right = tk.Frame(self,width=170, height=400, bg='white')
        ##创建需要的几个元素
        self.text_msglist = tk.Text(frame_left_top)
        self.text_msg = tk.Text(frame_left_center);
        button_sendmsg = tk.Button(frame_left_bottom, text=('发送'.encode("utf-8").decode("utf-8")), command=self.sendmessage)
        # 创建一个绿色的tag
        self.text_msglist.tag_config('green', foreground='#008B00')
        # 使用grid设置各个容器位置
        frame_left_top.grid(row=0, column=0, padx=2, pady=5)
        frame_left_center.grid(row=1, column=0, padx=2, pady=5)
        frame_left_bottom.grid(row=2, column=0)
        frame_right.grid(row=0, column=1, rowspan=3, padx=4, pady=5)
        frame_left_top.grid_propagate(0)
        frame_left_center.grid_propagate(0)
        frame_left_bottom.grid_propagate(0)
        # 把元素填充进frame
        self.text_msglist.grid()
        self.text_msg.grid()
        button_sendmsg.grid(sticky=tk.E)
    def sendmessage(self):
        # 在聊天内容上方加一行 显示发送人及发送时间
        msgcontent = ('我:'.encode("utf-8").decode("utf-8")) + time.strftime("%Y-%m-%d %H:%M:%S",
                                                                            time.localtime()) + '\n '
        self.text_msglist.insert(tk.END, msgcontent, 'green')
        message=self.text_msg.get('0.0', tk.END)
        data='03#'+self.name+'#'+message
        self.udp_cli.sendto(data.encode(),self.ADDR)
        data_recv,addr=self.udp_cli.recvfrom(1024)
        if data_recv.decode()=='03:01':
            self.text_msglist.insert(tk.END, message)
            self.text_msg.delete('0.0', tk.END)
        elif data_recv.decode()=='03:02':
            self.text_msglist.insert(tk.END, 'Offline'+'\n')
        else:
            self.text_msglist.insert(tk.END,'Unknown Wrong'+'\n')
    #接收消息
    def recvmessage(self):
        while self.running:
            print(self.name)
            self.udp_cli.sendto(('04#'+self.name).encode(),self.ADDR)
            data_recv, addr = self.udp_cli.recvfrom(1024)
            if data_recv.decode()=='07:01':
                tk.messagebox.showerror(title='Error',message='You are not logged in currently.')
                return
            else:
                n=eval(data_recv.decode()[3:])
                if n>0:
                    for i in range(n):
                        mess, addr = self.udp_cli.recvfrom(1024)
                        mess_l=mess.decode().split(':')
                        msgcontent=self.name+mess_l[2]+'\n'
                        self.text_msglist.insert(tk.END, msgcontent, 'red')
                        self.text_msglist.insert(tk.END, mess_l[3])
            time.sleep(30)

    def exit(self):
        self.running=False
        #self.t.join()
        self.udp_cli.close()
        self.destroy()
if __name__ == '__main__':
    app=Chat()
    app.mainloop()
```
	与好友聊天的子窗口，在本类中采用一套类似于与服务器端联系的协议与主窗口联系。窗口的布局直接采用了老师提供的参考代码，但是封装了一下。
	本类中的bug：还是多线程的问题，玄学在多线程的函数中无法访问类成员。
	发现问题时在trans之前开启了线程 所以没有找到类成员name
	
----
# 先写道这里，待完善