# 计算机图形学-实习二

> 姓名：徐鸿飞
>
> 班级：111172
>
> 学号：20171002608

## 1. 层次骨架

### 1.1	读取骨架文件（*.skel）

首先看这个作业属实没看懂，也不知道skel文件的结构，通读了文章之后才发现原来是个总分结构的作业，中间有说明skel文件的结构：

> 前三个字段是浮点数给出关节相对其父关节的平移。第四个字段是其父关节的标号 (关节标号是其在.skel文件中出现的顺序，从零开始), 因此形成一个关节结点的有向无环图。根结点以−1作为其父结点，其变换是角色在世界中全局位置。 

根据作业中所给，我们循环每次读出四个数（三个浮点数，一个整数），三个浮点数创建一个Joint，整数代表父关节的标号，所以当parent=-1时，把生成的Joint赋给根节点，否则就`m_joints[parent]->children.push_back(joint);`，最后注意每次生成的Joint都push到m_joints中。

### 1.2	画Joint

因为骨架的结构是一棵树，根据提示，所以我们采用递归的方式深度递归这棵树，在每个地方画一个球。

在这之前，我们需要先实现一下矩阵栈类，矩阵用vector存储，所以实现起来也很方便。初始化时，压入一个单位矩阵，`clear/top/pop`都是直接调用vector的对应的函数即可，只有push的之后需要注意，不是直接将出传入的矩阵push，而是要先与栈顶的矩阵相乘再push。

然后就是在递归的时候，每次画球之前，push矩阵然后load栈顶矩阵，递归之后pop即可。在写这个的时候犯了小错，应该是直接用类中的栈，不能用自己new的栈？

![画Joint](.\img\画Joint.png)

### 1.3	画Bone

与画Joint类似，递归的画出骨头，递归传入父节点，画出所有连接子节点的骨头，根据作业中的描述：

在从边长为1的立方体开始(简单调用glutSolidCube( 1.0f ))之前需要：

沿z平移使盒子范围从 $[−0.5, −0.5, 0]^T$ 到 $[0.5, 0.5, 1]^T$ ，即变化矩阵为`Matrix4f::translation(0, 0, 0.5)`；

> 看了挺久才明白这里的盒子范围是盒子一条对角线的坐标。。。

进行缩放变换，将盒子范围变换到从 $[−0.025, −0.025, 0]^T$ 到 $[0.025, 0.025,‌L]^T$其中L是在递归中到下一关节的距离，则变换矩阵：`Matrix4f::scaling(0.05f, 0.05f, l)`，其中l=`child->transform.getCol(3).xyz().abs()`；

最后旋转z轴，使得其与父关节的方向对齐: `z =parentOffset.normalized()`. 由于x和y轴任意,推荐这样映射`y =(z ×rnd).normalized()`, 而 `x =(y ×z).normalized()`, 其中rnd 为  $[0, 0,1]^T$；

但是当我完成这些之后，画出的图却是有问题的，我想到上课的时候说过复合变换的矩阵是反着来的，去看了一下pdf：

![变换复合](.\img\变换复合.png)

切换了矩阵乘的顺序之后成功了。

![画Bone](.\img\画Bone.png)

### 1.4 实现关节旋转

即实现`setJointTransform`传入需要更新的关节的序号（下标index）和用户设置的绕各个轴旋转的角度，所以要写讲所有轴的旋转复合：

```c++
	Matrix4f X = Matrix4f::rotateX(rX);
	Matrix4f Y = Matrix4f::rotateY(rY);
	Matrix4f Z = Matrix4f::rotateZ(rZ);
	Matrix4f all = X * Y * Z;
```

然后再在原来平移的基础上旋转，刚开始我想着直接相乘，但是有个问题是第二次旋转的时候会是在第一次旋转的基础上进行旋转，所以行不通；因为平移的矩阵参数主要是第`[3,0:2]`，旋转的参数是`[0:2,0:2]`，所以可以直接进行设置：

```c++
	all.setCol(3, m_joints[jointIndex]->transform.getCol(3));
	m_joints[jointIndex]->transform = all;
```

![关节旋转](.\img\关节旋转.gif)

## 2. 骨架子空间变换（Skeletal Subspace Deformation）

### 2.1 文件输入： 绑定姿态网格

实习一已经做过了。

### 2.2 网格渲染

与实习一类似，不同的只是需要每次画之前需要用`glNormal3fv`指定法向量，法向量的计算方式也已经给出，只需要按照一定的顺序计算即可,其他与实习一类似。

到这里发现上一步做错了😓，用fscanf函数读取按照%f读取整数会出问题……

要注意是求叉积，不能直接\*，刚开始直接\*画出来的很奇怪。

![网格渲染](.\img\网格渲染.png)

### 2.3 文件输入: 附加权重

同样是读文件，每行17个数据，读入attachments即可。

### 2.4 实现SSD

#### 2.4.1 计算变换

首先是实现`computeBindWorldToJointTransforms`，该函数的作用就是为每个Joint设置`bindWorldToJointTransform`矩阵，所以要先知道`bindWorldToJointTransform`是什么，才能知道如何去计算，根据框架中的注释：

> 该矩阵将世界空间转换为关节空间，以实现关节的初始（“绑定”）配置。

则对于每个Joint有（以关节空间原点为例）：
$$
\begin{align*}
& Matrix_{bindWorld}=Matrix_{parrentBindWorld}*Matrix_{transform}\\
& Matrix_{identity}=Matrix_{bindWorldToJointTransform}*Matrix_{bindWorld}\\
& \therefore Matrix_{bindWorldToJointTransform}\\
& =Matrix_{identity}*Matrix_{bindWorld}^{-1}\\
& =(Matrix_{transform}^{-1}*Matrix_{parrentBindWorld}^{-1})\\
& =\prod_{i=0}^{n}(Matrix_transform^{-1})
\end{align*}
$$
然后是实现`updateCurrentJointToWorldTransforms`，即为每个Joint设置`currentJointToWorldTransform`矩阵，同样的，通过注释：

> 此矩阵将关节的“当前”配置映射到世界空间。

则对于每个Joint有（同样以关节空间原点为例）：
$$
\begin{align*}
&Matrix_{bindWorld}=Matrix_{parrentBindWorld}*Matrix_{transform}\\
&Matrix_{bindWorld}=Matrix_{currentJointToWorldTransform}*Matrix_{identity}\\
&Matrix_{currentJointToWorldTransform}=\prod_{i=0}^{n}Matrix_{transform}
\end{align*}
$$
不得不说，有些抽象……感觉这里最难理解。

#### 2.4.2 变换网格

根据`2.4.1`得出来的矩阵，变换网格就很显而易见了，再根据ppt中的伪码：

![伪码](.\img\伪码.png)

框架中没有给`Matrix4f`加法的重载，所以直接算成`Vector4f`相加即可，这样做的时候，权重一定要最后乘。

![变换网格](.\img\变换网格.gif)

（很卡……）

## 回答问题

-  如何编译和运行你的代码? 

  > 使用命令行运行Release下的可执行文件即可。

- 是否与其他同学讨论与合作? 如果是，请告诉我们你与谁交流过，以及你收到或者给予了什么样的帮助。

  > 无。

- 是否有特别有助于你完成作业的参考资料（书籍，论文，网站等）？请提供一份清单。

  > [OpenGL设置法向量](https://blog.csdn.net/Haohan_Meng/article/details/41785607)

- 代码有何已知问题吗？如果有，请提供一份列表，可能的话，描述一下你认为原因是什么，以及如果给你更多的时间，你怎样改进。这非常重要，因为如果你帮助老师理解所发生的事情，我们很有可能给更多附加分。

  > 1. 变换网格很卡顿，估计是复杂度太高了，切换成Release就好了；
  > 2. Controls窗口必须改变一下大小才能用，未发现原因？

- 你是否做了附加题？如果是，说明如何使用你做的附加分程序。如果涉及大量的工作，请描述你做了什么，并且如何做的。

  > 

- 对此作业,你想分享些什么意见？

  > 1. 做这种提供了框架的作业时，我还是觉得需要读一下代码，不用读实现文件，先读一下声明文件，看一下框架为我们提供了哪些有用的方法，以便于去跟好的实现。
  > 2. 从英文翻译过来的作业有些地方较难理解，这个文档还采用了总分式的结构但是没有说明，如果不先读一遍，直接去做的话，是做不出来的。