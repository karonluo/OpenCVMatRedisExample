## 成都云图睿视科技有限公司 Karon Luo

### 转载声明

若需要将代码放到其他代码平台和论坛，请提供免费的下载方式并标注该代码的 github 的链接地址。

如放到 CSDN 时，请设置 0 积分下载。

感谢！

### 将 OpenCV Mat 存 取 Redis 例子

该例子的作用，用于一个视频源的视频数据提供给多个进程使用。

本例子使用了 Redis 作为内存管理方案，用于可能的分布式。

如果改为 共享内存，使用内存文件进行管理，则只能用于单机，但性能优于Redis进行内存管理。

例子代码依赖：OpenCV 4.2.0 \ Redis-Server \ libhiredis-dev

apt -y install redis-server libhiredis-dev

在操作系统 Ubuntu 18.04 中测试通过
