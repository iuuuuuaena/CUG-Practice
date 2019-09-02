```
你还必须提供README.txt或README.pdf文件以及您的解决方案。 这应该包含：
1.你（和你的同伴）的名字。
2.你在实施路由器时遇到了哪些挑战？
3.命名未在额外说明中指定的功能，以改善您的路由器。
4.命名您实施的额外说明选项; 描述他们做了什么以及他们如何工作。
```
***目录***

[TOC]
# 姓名
111172-徐鸿飞-20171002608

# 遇到的挑战
刚开始拿到这个实习题目感觉无从下手，因为原本的代码比较多，读完老师的readme知道了我们的工作只需要实现两个函数：
分别是learning_switch的handle_rx()与rip_router的handle_rx()

## learning_switch中的handle_rx()
其中learning_switch中的实现较为简单，利用给出的伪码直接实现即可：
> 使用目标ID检索交换机中的路由表
> if  在路由表中找到目标ID的入口项 {
>      则在对应（指定）的端口转发包
> }
> else flood
但是伪码中没有提到路由表的构建，实现时要注意路由表的构建。

## rip_router中的handle_rx()
rip_router是一种距离向量路由，所以基于Bellman-Ford算法来实现；也给出了伪码：
> if isinstance(packet, DiscoverPacket)：
> 将packet.src存放在路由表中
> elif isinstance(packet, RoutingUpdate)：
> 更新自己的路由表
> 如果有更新，将路由表flood出去。
> 将自己的路由表信息flood出去的时候，你需要构建自己的RoutingUpdate包，包里面存	放的就是路由表的信息。
> else：
> 查找路由表，进行发包

在实现这个代码之前，我们需要知道每个包的构造情况（虽然老师说不要看代码），查看sim/api.py中的Packet类，sim/basics中的DiscoverPacket和RoutingUpdate都基于Packet来实现，了解了包的结构之后更利于我们写代码。
rip_router中主要有三个表：
```python
self.RouterTable=dict() #{neighbor:{dst:cost}}
self.ports=dict()       #{neighbor:port}
self.paths=dict()       #{dst:(neighbor,cost)}
```
	- RouterTable是一个大表，存储路由要发送到目标经过每个邻居的花费；
	- ports纪录每个邻居的端口；
	- paths纪录要发送目标花费最小的邻居以及花费；
然后就可以通过伪码来实现具体的代码了；其中主要是路由表的更新以及本路由中最短路径的更新，只有在最短路径有更新时，将路由表flood出去。
	- 路由表的更新：收到邻居包且有连接时，花费为1，无连接则删除这个项；收到其他路由发送的更新包时，根据包内容更新自己的路由表；
	- 最短路径的更新：实现较为简单，遍历路由表，找对应目标花费最小的邻居即可；
最后是创建更新表，对应不同的目标路由，要实现毒性逆转，当最小花费的邻居是目标路由时，记cost为∞（100），其他直接拷贝paths即可，然后根据port中的纪录，将更新表flood出去。
# Link Weights and SmartDV
emmmmm