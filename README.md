# mfc_mini_register
这是我用MFC写的一个登录器框架，利用MFC的一些控件和GDI+完成的。<br>
后期会加入网络和MySQL的连接，不过MFC真的要过时了，打算用Qt写了。<br>
初学C++，没有什么项目经验，欢迎前辈们进行指教。<br>
运行截图:
<img src="https://raw.githubusercontent.com/Cirnoo/mfc_mini_register/master/mfc_register.png" width="450">

资源文件来源于网络：
[资源链接](https://blog.csdn.net/geniusice18/article/details/8393674)

---
2018.10.13更新  
忘记资源文件是通过相对文件位置导入加载的了，不能被打包加载进EXE，结果导致调试的时候运行正常，编译成EXE文件后显示一片漆黑。  
GDI+的imgae类无法直接加载资源文件，网上参考了一下别人的方法，发现只能加载PNG图片，加载bmp文件会出现奇怪的灰度图，只能暂时先这样了，QuQ.
