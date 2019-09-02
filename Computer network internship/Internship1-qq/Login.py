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
        recv=udp.sign_up(nn,np,npf)
        if recv=='01:01':
            tk.messagebox.showinfo('Welcome', 'You have successfully signed up!')
        elif recv=='01:02':
            tk.messagebox.showerror('Error', 'Password and confirm password must be the same!')
        else:
            tk.messagebox.showerror('Error', 'The user has already signed up!')
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
    entry_new_name = tk.Entry(window_sign_up, textvariable=new_name,bg='Bisque')
    entry_new_name.place(x=150, y=10)

    new_pwd = tk.StringVar()
    tk.Label(window_sign_up, text='Password: ').place(x=10, y=50)
    entry_usr_pwd = tk.Entry(window_sign_up, textvariable=new_pwd, show='*',bg='Bisque')
    entry_usr_pwd.place(x=150, y=50)

    new_pwd_confirm = tk.StringVar()
    tk.Label(window_sign_up, text='Confirm password: ').place(x=10, y=90)
    entry_usr_pwd_confirm = tk.Entry(window_sign_up, textvariable=new_pwd_confirm, show='*',bg='Bisque')
    entry_usr_pwd_confirm.place(x=150, y=90)

    btn_comfirm_sign_up = tk.Button(window_sign_up, text='Sign up', command=sign_up,bg='FloralWhite')
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
var_usr_name.set('20171002608')
entry_usr_name=tk.Entry(root,textvariable=var_usr_name,bg='Bisque')
entry_usr_name.place(x=160,y=150)
var_usr_pwd=tk.StringVar()
var_usr_pwd.set('666666')
entry_usr_pwd=tk.Entry(root,textvariable=var_usr_pwd,show='*',bg='Bisque')
entry_usr_pwd.place(x=160,y=190)


#login and sign up button
btn_login=tk.Button(root,text='Login',command=usr_login,bg='FloralWhite')
btn_login.place(x=150,y=230)
btn_sign_up=tk.Button(root,text='Sign up',command=usr_sign_up,bg='FloralWhite')
btn_sign_up.place(x=250,y=230)

root.mainloop()