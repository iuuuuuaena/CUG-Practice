import tkinter as tk
import time
import socket
from tkinter import messagebox
import ctypes
import inspect
import threading
def _async_raise(tid, exctype):
    """raises the exception, performs cleanup if needed"""
    tid = ctypes.c_long(tid)
    if not inspect.isclass(exctype):
        exctype = type(exctype)
    res = ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, ctypes.py_object(exctype))
    if res == 0:
        raise ValueError("invalid thread id")
    elif res != 1:
        # """if it returns a number greater than one, you're in trouble,
        # and you should call it again with exc=NULL to revert the effect"""
        ctypes.pythonapi.PyThreadState_SetAsyncExc(tid, None)
        raise SystemError("PyThreadState_SetAsyncExc failed")


def stop_thread(thread):
    _async_raise(thread.ident, SystemExit)
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
        self.name=''
        #多线程

    def trans(self,name):
        self.title('Chatting with '+name)
        self.name=name
        self.running=True
        self.t=threading.Thread(target=self.recvmessage,args=())
        self.t.start()
    def create(self):
        # 创建几个frame作为容器
        frame_left_top = tk.Frame(self,width=380, height=270, bg='white')
        frame_left_center = tk.Frame(self,width=380, height=100, bg='white')
        frame_left_bottom = tk.Frame(self,width=380, height=20)
        frame_right = tk.Frame(self,width=170, height=400, bg='white')
        ##创建需要的几个元素
        self.text_msglist = tk.Text(frame_left_top,bg='LightCyan')
        self.text_msg = tk.Text(frame_left_center,bg='Bisque');
        button_sendmsg = tk.Button(frame_left_bottom, text=('发送'.encode("utf-8").decode("utf-8")), command=self.sendmessage,bg='FloralWhite')
        # 创建一个绿色的tag
        self.text_msglist.tag_config('green', foreground='#008B00')
        self.text_msglist.tag_config('pink',foreground='#FF1493')
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
        #print(data_recv.decode())
        if data_recv.decode()=='03:01':
            self.text_msglist.insert(tk.END, message)
            self.text_msg.delete('0.0', tk.END)
        elif data_recv.decode()=='03:02':
            self.text_msglist.insert(tk.END, 'Offline'+'\n')
        elif data_recv.decode()=='07:01':
            self.text_msglist.insert(tk.END, 'You haven\'t login' + '\n')
        else:
            self.text_msglist.insert(tk.END,'Unknown Wrong'+'\n')
    #接收消息
    def recvmessage(self):
        while self.running:
            self.udp_cli.sendto(('04#'+self.name).encode(),self.ADDR)
            data_recv, addr = self.udp_cli.recvfrom(1024)
            if data_recv.decode()!='':
                print(data_recv.decode())
                if data_recv.decode()=='07:01':
                    tk.messagebox.showerror(title='Error',message='You are not logged in currently.')
                    return
                elif data_recv.decode()[:2]=='04':
                    #print(data_recv.decode())
                    n=eval(data_recv.decode()[3:])
                    if n>0:
                        for i in range(n):
                            mess, addr = self.udp_cli.recvfrom(1024)
                            mess_l=mess.decode().split(':')
                            msgcontent=self.name+':'+mess_l[2]+':'+mess_l[3]+':'+mess_l[4]+'\n'
                            self.text_msglist.insert(tk.END, msgcontent, 'pink')
                            self.text_msglist.insert(tk.END, ' '+':'.join(mess_l[5:]))
                else:
                    self.text_msglist.insert(tk.END, 'Unknown Wrong' + '\n')
            time.sleep(3)

    def exit(self):
        self.running=False
        #self.t.join()
        self.udp_cli.close()
        self.destroy()
if __name__ == '__main__':
    app=Chat()
    app.mainloop()