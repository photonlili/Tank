Hello Tank

##移植步骤#############################
通过网络初始化工程
1.
/usr/local/etc/sshd_config
# override default of no subsystems
Subsystem       sftp    internal-sftp

2.
# password
passwd root
0

# net.sh
3.
通过zmodem上传net.sh到/DWINFile 执行 -> 执行net.sh

# project
4.
Fillzllia上传/DWINFile下所有的文件

# init project
5.
写入序列号 云用户密码
##移植步骤##############################
通过U盘初始化工程
1.通过u盘上传工程目录文件
2.修改root密码为0
3.修改sftp配置
3.1 校准触摸屏
4.启动程序，配置网络
5.启动程序，写入序列号 云用户密码
