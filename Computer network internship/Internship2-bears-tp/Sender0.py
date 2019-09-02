import sys
import getopt

import Checksum
import BasicSender

'''
This is a skeleton sender class. Create a fantastic transport protocol here.
'''
# sys.argv =[sys.argv[0],'-fa.pptx','-p33122','-a127.0.0.1']
class Sender(BasicSender.BasicSender):
    def __init__(self, dest, port, filename, debug=False):
        super(Sender, self).__init__(dest, port, filename, debug)

    # Main sending loop.
    def start(self):
        # raise NotImplementedError
        seqno = 0
        msg = self.infile.read(1470)
        msg_type = None
        window_size=5
        window=dict()
        top_rec =0
        while not msg_type == 'end' or len(window)!=0:
            while len(window)<window_size and msg_type!='end':
                next_msg = self.infile.read(1470)
                msg_type = 'data'
                if seqno == 0:
                    msg_type = 'start'
                elif next_msg == "":
                    msg_type = 'end'
                packet=self.make_packet(msg_type,seqno,msg)
                window[seqno]=packet
                # print "sent: %s" % packet
                seqno+=1
                msg=next_msg
                # if msg_type=='end':
                #     break
            for w in sorted(window):
                self.send(window[w])
                # print window[w].split('|')[:2]
            while True:
                response=self.receive(0.5)
                if response==None or not Checksum.validate_checksum(response):
                    break
                top_rec=eval(response.split('|')[1])
                self.handle_response(response)
            for key in window.keys():
                if key<top_rec:
                    del window[key]

        self.infile.close()


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
