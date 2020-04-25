# linux

------

[TOC]

------

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
yum install epel-release
yum install xrdp
yum install tigervnc-server
# 设置vnc密码
vncpasswd root
/usr/sbin/sestatus -v
setenforce 0
systemctl stop firewalld
systemctl disable firewalld
systemctl start xrdp
systemctl enable xrdp
sudo firewall-cmd --permanent --add-service vnc-server
sudo systemctl restart firewalld
```

修改xrdp端口

```
vim /etc/xrdp/xrdp.ini
```

```

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

### rpm

#### 安装

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

