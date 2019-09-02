import sys
import getopt

import Checksum
import BasicSender
import threading
import time


'''
This is a skeleton sender class. Create a fantastic transport protocol here.
'''
# sys.argv =[sys.argv[0],'-fa.pptx','-p33122','-a127.0.0.1']
class Sender(BasicSender.BasicSender):
    def __init__(self, dest, port, filename, debug=False):
        super(Sender, self).__init__(dest, port, filename, debug)
        self.timeout=0.5
        self.top_rec = 0
        self.window_size=5
        self.datasize=1400
        self.window=dict()
        self.end=sys.maxsize
        self.seqno = 0
    # Main sending loop.
    def start(self):
        # raise NotImplementedError
        t=threading.Thread(target=self.rec_ack,args=())
        t.start()
        time.sleep(0.01)

        msg = self.infile.read(self.datasize)
        msg_type = None

        while (not msg_type == 'end'):
            if self.seqno<self.top_rec+self.window_size:
                next_msg = self.infile.read(self.datasize)
                msg_type = 'data'
                if self.seqno == 0:
                    msg_type = 'start'
                elif next_msg == "":
                    msg_type = 'end'
                    self.end=self.seqno
                packet=self.make_packet(msg_type,self.seqno,msg)
                self.send(packet)
                self.window[self.seqno]=[packet,time.time()]
                # print "sent: %s" % packet
                self.seqno+=1
                msg=next_msg

        # print 'end'
        t.join()
        self.infile.close()
    def rec_ack(self):
        while 1:
            response=self.receive(0.01)
            if response!=None and Checksum.validate_checksum(response):
                self.top_rec = eval(self.split_packet(response)[1])
                for key in self.window.keys():
                    # print key
                    if key<self.top_rec:
                        self.timeout=0.9*self.timeout+0.1*(time.time()-self.window[key][1])
                        del self.window[key]
            for key in self.window.keys():
                if time.time()-self.window[key][1]>self.timeout:
                    self.send(self.window[key][0])
                    self.window[key][1]=time.time()
            if self.top_rec==self.end+1 and len(self.window)==0:
                return
            # print self.top_rec
            # self.handle_response(response)


    def handle_timeout(self):
        pass

    def handle_new_ack(self, ack):
        pass

    def handle_dup_ack(self, ack):
        pass

    def log(self, msg):
        if self.debug:
            print msg
    def handle_response(self,response_packet):
        if Checksum.validate_checksum(response_packet):
            print "recv: %s" % response_packet
        else:
            print "recv: %s <--- CHECKSUM FAILED" % response_packet

'''
This will be run if you run this script from the command line. You should not
change any of this; the grader may rely on the behavior here to test your
submission.
'''
if __name__ == "__main__":
    def usage():
        print "BEARS-TP Sender"
        print "-f FILE | --file=FILE The file to transfer; if empty reads from STDIN"
        print "-p PORT | --port=PORT The destination port, defaults to 33122"
        print "-a ADDRESS | --address=ADDRESS The receiver address or hostname, defaults to localhost"
        print "-d | --debug Print debug messages"
        print "-h | --help Print this usage message"

    try:
        opts, args = getopt.getopt(sys.argv[1:],
                               "f:p:a:d", ["file=", "port=", "address=", "debug="])
    except:
        usage()
        exit()

    port = 33122
    dest = "localhost"
    filename = None
    debug = False

    for o,a in opts:
        if o in ("-f", "--file="):
            filename = a
        elif o in ("-p", "--port="):
            port = int(a)
        elif o in ("-a", "--address="):
            dest = a
        elif o in ("-d", "--debug="):
            debug = True
    s = Sender(dest,port,filename,debug)
    try:
        s.start()
    except (KeyboardInterrupt, SystemExit):
        exit()
