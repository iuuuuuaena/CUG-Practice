from sim.api import *
from sim.basics import *

'''
Create your RIP router in this file.
'''
class LearningSwitch (Entity):
    def __init__(self):
        # Add your code here!
        self.RouterTable = {}
        pass

    def handle_rx (self, packet, port):
        # Add your code here!
        if self.RouterTable.has_key(packet.dst):
            self.send(packet,self.RouterTable[packet.dst],flood=False)
        else:
            self.send(packet, port, flood=True)
        if not self.RouterTable.has_key(packet.src):
            self.RouterTable[packet.src]=port
        # raise NotImplementedError
