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
    #用户注册
    def sign_up(self,num,pwd,pwd_confirm):
        data='01#'+num+'#'+pwd+'#'+pwd_confirm+'#'
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