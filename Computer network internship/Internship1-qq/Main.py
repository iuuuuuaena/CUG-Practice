import tkinter as tk
from tkinter import messagebox
import Chat
import socket
import threading
import time
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
        self.name_entry=tk.Entry(self,textvariable=self.var_name,bg='Bisque')
        self.name_entry.place(x=10,y=10,height=30,width=200)
        self.btn_add=tk.Button(self,text='Add',command=self.add_friend)
        self.btn_add.place(x=220,y=10)
        self.btn_del = tk.Button(self, text='Delete', command=self.del_friend)
        self.btn_del.place(x=270, y=10)

        #好友列表
        self.lb_var=tk.StringVar()
        self.lb=tk.Listbox(self,listvariable=self.lb_var,height=33,width=40,bg='lightCyan')
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
            #print(data.decode())
            datalist=data.decode().split('#')
            #发送消息
            if datalist[0]=='03':
                recv=self.udp.chatOne(self.friends[datalist[1]],datalist[2])
                self.udp_ser.sendto(recv.encode(),addr)
            #接收消息
            elif datalist[0]=='04':
                messagelist=self.udp.recvOne(self.friends[datalist[1]])
                #print(messagelist)
                if messagelist=='07:01' or messagelist[3:]=='0':
                    self.udp_ser.sendto(messagelist.encode(), addr)
                else:
                    length=len(messagelist)
                    self.udp_ser.sendto(('04:'+str(length)).encode(),addr)
                    for i in range(length):
                        self.udp_ser.sendto(messagelist[i].encode(), addr)
            #time.sleep(0.1)

    #添加好友
    def add_friend(self):
        f_name=self.var_name.get()
        if f_name in self.all:
            print('add')
            self.lb.insert('end',f_name)
            self.friends[f_name]=self.all[f_name]
            self.var_name.set('')
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
        #print('chat with '+name)
        newchat=Chat.Chat()
        newchat.trans(name)
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
        entry_new_name = tk.Entry(root_change, textvariable=new_name,bg='Bisque')
        entry_new_name.place(x=150, y=10)

        old_pwd = tk.StringVar()
        tk.Label(root_change, text='Old Password:').place(x=10, y=50)
        entry_old_pwd = tk.Entry(root_change, textvariable=old_pwd, show='*',bg='Bisque')
        entry_old_pwd.place(x=150, y=50)

        new_pwd = tk.StringVar()
        tk.Label(root_change, text='Password: ').place(x=10, y=90)
        entry_usr_pwd = tk.Entry(root_change, textvariable=new_pwd, show='*',bg='Bisque')
        entry_usr_pwd.place(x=150, y=90)

        new_pwd_confirm = tk.StringVar()
        tk.Label(root_change, text='Confirm password: ').place(x=10, y=130)
        entry_usr_pwd_confirm = tk.Entry(root_change, textvariable=new_pwd_confirm, show='*',bg='Bisque')
        entry_usr_pwd_confirm.place(x=150, y=130)

        btn_comfirm_sign_up = tk.Button(root_change, text='Change Password', command=changepwd,bg='FloralWhite')
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
            #self.running=False
            #self.t.join(0.01)
            Chat.stop_thread(self.t)
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