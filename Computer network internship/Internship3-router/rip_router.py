from sim.api import *
from sim.basics import *

'''
Create your RIP router in this file.
'''
class RIPRouter (Entity):
    def __init__(self):
        # Add your code here!
        self.RouterTable=dict() #{neighbor:{dst:cost}}
        self.ports=dict()       #{neighbor:port}
        self.paths=dict()       #{dst:(neighbor,cost)}
        # pass
    def handle_rx(self, packet, port):
        def update_paths():
            path_cp=self.paths.copy()
            self.paths.clear()
            for neighbor in self.RouterTable.keys():
                for dst in self.RouterTable[neighbor].keys():
                    if dst not in self.paths.keys():
                        self.paths[dst]=(neighbor,self.RouterTable[neighbor][dst])
                    else:
                        if self.paths[dst][1]>self.RouterTable[neighbor][dst]:
                            self.paths[dst]=(neighbor,self.RouterTable[neighbor][dst])
                        else:
                            pass
            return self.paths!=path_cp
        def gen_RoutingUpdate(dest):
            routingUpdate=RoutingUpdate()
            for dst in self.paths.keys():
                if dst!=dest:
                    if self.paths[dst][0]==dest:#poisoned reverse
                        routingUpdate.add_destination(dst,100)
                    else:
                        routingUpdate.add_destination(dst,self.paths[dst][1])
            return routingUpdate
        if isinstance(packet,DiscoveryPacket):#neighbor
            self.ports[packet.src]=port
            if packet.is_link_up:
                self.RouterTable[packet.src]={packet.src:1}
            else:
                del self.RouterTable[packet.src]
        elif isinstance(packet,RoutingUpdate):#update
            if packet.src in self.RouterTable.keys():
                for dest in packet.paths.keys():
                    if packet.paths[dest]>=100:
                        self.RouterTable[packet.src][dest]=100
                    else:
                        self.RouterTable[packet.src][dest]=1+packet.paths[dest]
        else:#normal
            if self.paths.has_key(packet.dst):
                if self.paths[packet.dst][1]!=100:
                    self.send(packet,self.ports[self.paths[packet.dst][0]])
            return
        if update_paths():
            for neighbor in self.ports.keys():
                routingUpdate=gen_RoutingUpdate(neighbor)
                if len(routingUpdate.all_dests())>0:
                    self.send(routingUpdate,self.ports[neighbor])