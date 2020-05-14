# linux

## centos
### 安装GNOME图形化界面
```sh
yum groupinstall "GNOME Desktop"
# systemctl set-default multi-user.target  //设置成命令模式
systemctl set-default graphical.target  //设置成图形模式
```
### 配置VNC远程
```
rpm -qa|grep epel
yum -y install epel-release
yum -y install xrdp
yum -y install tigervnc-server
# 设置vnc密码
vncpasswd root
/usr/sbin/sestatus -v
setenforce 0
systemctl stop firewalld
systemctl disable firewalld
sudo systemctl restart firewalld
systemctl start xrdp
systemctl enable xrdp
sudo firewall-cmd --permanent --add-service vnc-server

```
修改xrdp端口
```
vim /etc/xrdp/xrdp.ini
```

Failed:
  python-urllib3.noarch 0:1.10.2-7.el7

```sh
mkdir /data/backup
cd /usr/lib/python2.7/site-packages/urllib3/packages
mv ./ssl_match_hostname* /data/backup/
sudo yum install python-urllib3 
```

genome login failed to display 0

```sh
wrong password
```

### rpm安装软件

```sh
rpm -ivh egwegwe.rpm
```

卸载

```sh
rpm -e gwegewg.rpm
```

### fzf

```sh
git clone --depth 1 https://github.com/junegunn/fzf.git ~/.fzf
cd ~/.fzf/
./install
```

### 批量杀死进程

```sh
 ps -ef | grep java | grep -v grep | awk '{print $2}' | xargs kill -9
```

### 查找

```sh
find / -name httpd.conf
```

代码补全

```
yum -y install bash-completion
source /etc/profile.d/bash_completion.sh
```

## 安装vmware

```
chmod a+x VMware-Workstation-Full-12.1.1-3770994.x86_64.bundle
./VMware-Workstation-Full-12.1.1-3770994.x86_64.bundle
```

serial key 15

```
FU512-2DG1H-M85QZ-U7Z5T-PY8ZD
```

bug

VMware Workstation recommends 2 GB of system swap space for the set of currently running virtual machines. 0 bytes of system swap space is available. For optimum performance increase the amount of system swap space, or configure all virtual machine memory to use reserved host RAM under Preferences.

```
If you have sufficient host memory (eg. >=8GB) and your VMs are configured for sufficiently small memory usage (e.g. >=4GB) you can run the VM completely in memory. Add the following line to the bottom of your /etc/vmware/config file:
prefvmx.minVmMemPct = "100"
When you restart VMware Player, all your VMs will run completely in memory without using swap space.
```

## 安装virtualbox

1. Create the repository config file /etc/yum.repos.d/virtualbox.repo:
```
[virtualbox]
name=VirtualBox
baseurl=http://download.virtualbox.org/virtualbox/rpm/el/$releasever/$basearch
enabled=1
gpgcheck=1
gpgkey=https://www.virtualbox.org/download/oracle_vbox.asc
```
2. Install VirtualBox-6.1 rpm package:
```
# yum install VirtualBox-6.1
```
## rsync

```
rsync -avzHe "ssh -p 10001" /tmp/log/* root@45.249.93.194:/data/project/cp/changfu/
```

#### 常用参数

```sh
-v :展示详细的同步信息
-a :归档模式，相当于 -rlptgoD
    -r :递归目录
    -l :同步软连接文件
    -p :保留权限
    -t :将源文件的"modify time"同步到目标机器
    -g :保持文件属组
    -o :保持文件属主
    -D :和--devices --specials一样，保持设备文件和特殊文件
-z :发送数据前，先压缩再传输
-H :保持硬链接
-n :进行试运行，不作任何更改
-P same as --partial --progress
    --partial :支持断点续传
    --progress :展示传输的进度
--delete :如果源文件消失，目标文件也会被删除
--delete-excluded :指定要在目的端删除的文件
--delete-after :默认情况下，rsync是先清理目的端的文件再开始数据同步；如果使用此选项，则rsync会先进行数据同步，都完成后再删除那些需要清理的文件。
--exclude=PATTERN :排除匹配PATTERN的文件
--exclude-from=FILE :如果要排除的文件很多，可以统一写在某一文件中
-e ssh :使用SSH加密隧道传输
```

## more

```

```

## less

**参数说明**：

- -b <缓冲区大小> 设置缓冲区的大小
- -e 当文件显示结束后，自动离开
- -f 强迫打开特殊文件，例如外围设备代号、目录和二进制文件
- -g 只标志最后搜索的关键词
- -i 忽略搜索时的大小写
- -m 显示类似more命令的百分比
- -N 显示每行的行号
- -o <文件名> 将less 输出的内容在指定文件中保存起来
- -Q 不使用警告音
- -s 显示连续空行为一行
- -S 行过长时间将超出部分舍弃
- -x <数字> 将"tab"键显示为规定的数字空格
- /字符串：向下搜索"字符串"的功能
- ?字符串：向上搜索"字符串"的功能
- n：重复前一个搜索（与 / 或 ? 有关）
- N：反向重复前一个搜索（与 / 或 ? 有关）
- b 向上翻一页
- d 向后翻半页
- h 显示帮助界面
- Q 退出less 命令
- u 向前滚动半页
- y 向前滚动一行
- 空格键 滚动一页
- 回车键 滚动一行
- [pagedown]： 向下翻动一页
- [pageup]： 向上翻动一页

## route

```
route
ip route show

```

**命令：**

```
route del default gw 47.244.157.40
route add default gw 47.244.157.40
```

## iptables

```
-t<表>：指定要操纵的表；
-A：向规则链中添加条目；
-D：从规则链中删除条目；
-i：向规则链中插入条目；
-R：替换规则链中的条目；
-L：显示规则链中已有的条目；
-F：清楚规则链中已有的条目；
-Z：清空规则链中的数据包计算器和字节计数器；
-N：创建新的用户自定义规则链；
-P：定义规则链中的默认目标；
-h：显示帮助信息；
-p：指定要匹配的数据包协议类型；
-s：指定要匹配的数据包源ip地址；
-j<目标>：指定要跳转的目标；
-i<网络接口>：指定数据包进入本机的网络接口；
-o<网络接口>：指定数据包要离开本机所使用的网络接口。
```

**开放指定的端口**

```
iptables -A INPUT -s 127.0.0.1 -d 127.0.0.1 -j ACCEPT               #允许本地回环接口(即运行本机访问本机)
iptables -A INPUT -m state --state ESTABLISHED,RELATED -j ACCEPT    #允许已建立的或相关连的通行
iptables -A OUTPUT -j ACCEPT         #允许所有本机向外的访问
iptables -A INPUT -p tcp --dport 22 -j ACCEPT    #允许访问22端口
iptables -A INPUT -p tcp --dport 80 -j ACCEPT    #允许访问80端口
iptables -A INPUT -p tcp --dport 21 -j ACCEPT    #允许ftp服务的21端口
iptables -A INPUT -p tcp --dport 20 -j ACCEPT    #允许FTP服务的20端口
iptables -A INPUT -j reject       #禁止其他未允许的规则访问
iptables -A FORWARD -j REJECT     #禁止其他未允许的规则访问
```

**清除已有iptables规则**

```
iptables -F
iptables -X
iptables -Z
```

**屏蔽IP**

```
iptables -I INPUT -s 123.45.6.7 -j DROP       #屏蔽单个IP的命令
iptables -I INPUT -s 123.0.0.0/8 -j DROP      #封整个段即从123.0.0.1到123.255.255.254的命令
iptables -I INPUT -s 124.45.0.0/16 -j DROP    #封IP段即从123.45.0.1到123.45.255.254的命令
iptables -I INPUT -s 123.45.6.0/24 -j DROP    #封IP段即从123.45.6.1到123.45.6.254的命令是
```

**查看已添加的iptables规则**

```
iptables -L -n -v
Chain INPUT (policy DROP 48106 packets, 2690K bytes)
 pkts bytes target     prot opt in     out     source               destination         
 5075  589K ACCEPT     all  --  lo     *       0.0.0.0/0            0.0.0.0/0           
 191K   90M ACCEPT     tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp dpt:22
1499K  133M ACCEPT     tcp  --  *      *       0.0.0.0/0            0.0.0.0/0           tcp dpt:80
4364K 6351M ACCEPT     all  --  *      *       0.0.0.0/0            0.0.0.0/0           state RELATED,ESTABLISHED
 6256  327K ACCEPT     icmp --  *      *       0.0.0.0/0            0.0.0.0/0           

Chain FORWARD (policy ACCEPT 0 packets, 0 bytes)
 pkts bytes target     prot opt in     out     source               destination         

Chain OUTPUT (policy ACCEPT 3382K packets, 1819M bytes)
 pkts bytes target     prot opt in     out     source               destination         
 5075  589K ACCEPT     all  --  *      lo      0.0.0.0/0            0.0.0.0/0  
```

**删除已添加的iptables规则**

将所有iptables以序号标记显示，执行：

```
iptables -L -n --line-numbers
```

比如要删除INPUT里序号为8的规则，执行：

```
iptables -D INPUT 8
```

## firewall

启动命令如下

```
systemctl start firewalld
```

状态查看

```
systemctl status firewalld
```

停止运行

```
systemctl stop firewalld
```

禁止开机运行

```
systemctl disable firewalld
```

允许开机允许

```
systemctl enable firewalld
```

## 查看硬件信息

内存

```
free -m
```

cpu

```
# 总核数 = 物理CPU个数 X 每颗物理CPU的核数 
# 总逻辑CPU数 = 物理CPU个数 X 每颗物理CPU的核数 X 超线程数

# 查看物理CPU个数
cat /proc/cpuinfo| grep "physical id"| sort| uniq| wc -l

# 查看每个物理CPU中core的个数(即核数)
cat /proc/cpuinfo| grep "cpu cores"| uniq

# 查看逻辑CPU的个数
cat /proc/cpuinfo| grep "processor"| wc -l

cat /proc/cpuinfo | grep name | cut -f2 -d: | uniq -c
```

ansible

安装

```
yum install epel-release
yum install ansible
```

## ssh

修改ssh端口

```
vim /etc/ssh/sshd_config
Port 10001
```

在centos7下重启服务不再是 service 服务名称 动作 这样的方式的.而是:

systemctl 动作 服务名.service

1. 查看sshd服务是否启动了.

```
systemctl status sshd.service
```

看到的这样的信息就可以确定是启动了.

2. 如果没有启动,则需要启动该服务:

```
systemctl start sshd.service
```

3. 如果需要重启sshd服务可使得

```
systemctl restart sshd.service
```

4. 设置为开机启动可使用:

```
systemctl enable sshd.service
```

## DNS

> Could not resolve host: mirrorlist.centos.org; Unknown error

This indicates that you either (a) don't have a properly configured DNS server or (b) your network configuration isn't correct and you can't connect to a DNS server to check the hostname `mirrorlist.centos.org`.

Try using `ping 8.8.8.8`. If this fails, try `ping `. If that also fails, your local network configuration is wrong and you'll have to check the configuration.

If you can ping `8.8.8.8`, try using `host`, `nslookup` or `dig` to check the DNS settings like `host google.com` or `dig google.com`. If these fail, you need to check your DNS settings. Check `/etc/resolv.conf` to see what's configured.

**UPDATE**

Since `/etc/resolv.conf` is blank, you need to setup a DNS resolver. I would suggest entering the following into the file using `nano` or `vi` (or whatever your comfortable using):

```
vim /etc/resolv.conf
nameserver 8.8.8.8
```

Save this file, then try `yum update` again.

You can also try other DNS hosts if you would rather, such as `8.8.8.8` or `8.8.4.4` or any of the OpenDNS hosts.

> error: Bind to port 10001 on 0.0.0.0 failed: Permission denied.

## selinux

**查看selinux状态**

```
sestatus
```

**临时关闭**

```
setenforce 0
```

**永久关闭**,**可以修改配置文件/etc/selinux/config,将其中SELINUX设置为disabled**。

```
cat /etc/selinux/config
SELINUX=disabled 
```

## 重装yum



> 检查CentOS 7版本

```
cat /etc/centos-release
```

> 寻找对应的文件下载

**[http://vault.centos.org](http://vault.centos.org/) 找到对应的依赖下载**

我的CentOS7版本完整路径为：http://vault.centos.org/7.5.1804/os/x86_64/Packages/

rpm -i --force --nodeps 

使用wget下载文件：

```
 python-2.7.5-68.el7.x86_64.rpm
 python-iniparse-0.4-9.el7.noarch.rpm
 python-libs-2.7.5-68.el7.x86_64.rpm
 python-pycurl-7.19.0-19.el7.x86_64.rpm
 python-urlgrabber-3.10-8.el7.noarch.rpm
 rpm-python-4.11.3-32.el7.x86_64.rpm 
 yum-3.4.3-158.el7.centos.noarch.rpm
 yum-metadata-parser-1.1.4-10.el7.x86_64.rpm
 yum-plugin-fastestmirror-1.1.31-45.el7.noarch.rpm
```

>安装依赖

单个安装方式（针对多个文件一个一个安装）
`rpm -ivh --replacepkgs python-2.7.5-68.el7.x86_64.rpm`

批量安装方式

```
rpm -Uvh --replacepkgs python*.rpm
rpm -Uvh --replacepkgs rpm-python*.rpm yum*.rpm
```

注意

> **无论是单个安装还是批量安装，若是出现安装依赖的问题，针对报错的依赖 复制下来 ；**
>
> **在`http://vault.centos.org/7.5.1804/os/x86_64/Packages/`（结合自己实际的CentOS7版本地址）上进行搜索依赖包，下载到CentOS7机子上，安装报错的依赖包**

>完成测试

输入命令`yum`和`python -V`

## 同步时间

> 设置时区（CentOS 7）

先执行命令`timedatectl status|grep 'Time zone'`查看当前时区，如果不是中国时区（Asia/Shanghai），则需要先设置为中国时区，否则时区不同会存在时差。

```bash
#已经是Asia/Shanghai，则无需设置
[root@xiaoz shadowsocks]# timedatectl status|grep 'Time zone'
       Time zone: Asia/Shanghai (CST, +0800)
```

执行下面的命令设置时区

```bash
#设置硬件时钟调整为与本地时钟一致
timedatectl set-local-rtc 1
#设置时区为上海
timedatectl set-timezone Asia/Shanghai
```

> 使用ntpdate同步时间

目前比较常用的做法就是使用ntpdate命令来同步时间，使用方法如下：

```bash
#安装ntpdate
yum -y install ntpdate
#同步时间
ntpdate -u  pool.ntp.org
#同步完成后,date命令查看时间是否正确
date
```

## scp

```

```

## rsync

`Rsync` 远程同步主要有两种方式：使用远程`shell（ssh或rsh）` 或使用`rsync`的`daemon`方式

常用参数

```jsx
-v :展示详细的同步信息
-a :归档模式，相当于 -rlptgoD
    -r :递归目录
    -l :同步软连接文件
    -p :保留权限
    -t :将源文件的"modify time"同步到目标机器
    -g :保持文件属组
    -o :保持文件属主
    -D :和--devices --specials一样，保持设备文件和特殊文件
-z :发送数据前，先压缩再传输
-H :保持硬链接
-n :进行试运行，不作任何更改
-P same as --partial --progress
    --partial :支持断点续传
    --progress :展示传输的进度
--delete :如果源文件消失，目标文件也会被删除
--delete-excluded :指定要在目的端删除的文件
--delete-after :默认情况下，rsync是先清理目的端的文件再开始数据同步；如果使用此选项，则rsync会先进行数据同步，都完成后再删除那些需要清理的文件。
--exclude=PATTERN :排除匹配PATTERN的文件
--exclude-from=FILE :如果要排除的文件很多，可以统一写在某一文件中
-e ssh :使用SSH加密隧道传输
```

本地文件同步

```bash
[root@sync opt]# rsync -avH /opt/resource/ /tmp/desc/
# 如果没有desc目录，会自动创建
```

远程文件同步--shell方式

```bash
# 
# 从本地传到远端，目标文件会被写成ssh登录用户的属组和属主（如下 www）
[root@sync opt]# rsync -avH /opt/nginx-1.12.1/ www@172.18.50.125:/tmp/nginx/
# 使用 ssh 加密隧道方式传输，保障数据的安全性
[root@sync opt]# rsync -avHe ssh /opt/nginx-1.12.1/ www@172.18.50.125:/tmp/nginx/

# 从远端传到本地，只要对目标文件有读的权限，就可以同步到本地
[root@sync opt]# rsync -avH www@172.18.50.125:/tmp/nginx/ /tmp/nginx/

# 如果远程服务器ssh端口不是默认的22
[root@sync opt]# rsync -avHezP "ssh -p 11222" /opt/nginx-1.12.1/ www@172.18.50.125:/tmp/nginx/

rsync -avHe "ssh -p 10001" /data/backup/database/20200429-0457-lottery.sql-tar.gz root@47.244.157.40:/data/backup/database/
```

远程文件同步--daemon方式

```css
服务器A： 172.18.50.125(daemon)
服务器B： 172.18.50.110
系统： Centos 7
Rsync版本：3.0.9
```

- 创建 `rsync` 服务的目录和配置文件

```bash
[root@50_125 ~]# mkdir /etc/rsync 
[root@50_125 ~]# cd /etc/rsync
[root@50_125 rsync]# touch rsyncd.conf
[root@50_125 rsync]# touch rsyncd.secrets
[root@50_125 rsync]# touch rsyncd.motd
[root@50_125 rsync]# chmod 600 rsyncd.secrets 
```

## 内核版本

```
cat /etc/issue
```

## 压缩解压

**.gz压缩包(不带tar)**，用gzip命令即可(-d选项可以解压)
格式：

```
gzip XXX.gz -d 解压位置
```

**.tar.gz压缩包**，需要使用tar命令的-z和-f选项(解压需要-x)
格式：

```
tar -zxf XXX.tar.gz -C 解压位置1
```

**注意：**后面的-C是大写C，如果不指定解压位置需要去掉-C，系统会把压缩包中所有文件解压到当前工作文件夹

## 查看进程

```
htop
```

