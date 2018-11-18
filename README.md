# mfc_mini_game_framwork

开发环境：vs2012，Qt5.3，MySQL 

## 简介
这是一个多人游戏对战平台框架,包含一个用MFC设计的客户端和一个用Qt设计的服务器以及一个斗地主游戏示例程序  
使用GDI+重写了MFC的相关控件，并设计了自己的图形界面类库与图像处理函数  
使用TCP协议和心跳包保活机制处理客户端和服务器的连接，使用select模型管理多客户端与服务器的通信，游戏大厅系统支持多人在线联机  
使用MySQL管理玩家的信息  
## 截图  

### 登录界面   
<img src="https://raw.githubusercontent.com/Cirnoo/Online-Game-Platform-Framework/Netwok/screenshot/login_dlg.png" width="450"> <br>
### 游戏界面  
<img src="https://raw.githubusercontent.com/Cirnoo/Online-Game-Platform-Framework/Netwok/screenshot/game_ready.jpg" width="550"> <br>
##### 抢地主
<img src="https://raw.githubusercontent.com/Cirnoo/Online-Game-Platform-Framework/Netwok/screenshot/game_2.png" width="550"> <br>
这里面用到了一些自己写的GDI+图像处理函数，以后有时间可以整理出来。即便用GDI+，MFC处理图像依然比较麻烦，一般能用PS处理的我就用PS了。
资源文件来源于网络：
[资源链接](https://blog.csdn.net/geniusice18/article/details/8393674)

---  
Original  
这是我用MFC写的一个游戏登录器框架，利用MFC的一些控件和GDI+完成的。<br>
初学C++，没有什么项目经验，欢迎前辈们进行指教。<br>

---  

2018.10.13 更新  
忘记资源文件是通过相对文件位置导入加载的了，不能被打包加载进EXE，结果导致虽然调试的时候运行正常，但是编译成EXE文件后显示一片漆黑，打开出错。  
GDI+的imgae类无法直接加载资源文件，网上参考了一下别人的方法，发现只能加载PNG图片，加载bmp文件会出现奇怪的灰度图，只能暂时先这样了，QuQ.

--- 

2018.10.28 更新  
服务器网络通信部分基本完成，剩下主要就是游戏部分了，这个框架是通用的，这里将会用斗地主做一个demo。  
服务器是用Qt写的，事实证明Qt和MFC的socket类是可以正常通信的。
需要注意的是，vs使用的是GBK编码，Qt默认使用UTF-8，通信会产生乱码，由于vs不支持UTF-8，所以只能把Qt设置成gbk编码了。
gbk编码下qDebug()不支持中文输出，使用std::cout正常。  
[服务器链接](https://github.com/Cirnoo/game-server)



