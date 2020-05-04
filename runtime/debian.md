# debian

## 同步时间

```
sudo apt-get install ntpdate -y
sudo ntpdate time.windows.com
```

同步时区

```
sudo dpkg-reconfigure tzdata
```

## install docker

```
sudo apt-get remove docker docker-engine docker.io containerd run

sudo apt-get install \
    apt-transport-https \
    ca-certificates \
    curl \
    gnupg-agent \
    software-properties-common
    
curl -fsSL https://download.docker.com/linux/debian/gpg | sudo apt-key add -

sudo apt-key fingerprint 0EBFCD88

sudo add-apt-repository \
   "deb [arch=arm64] https://download.docker.com/linux/debian \
   $(lsb_release -cs) \
   stable"
sudo apt-get update
sudo apt-get install docker-ce docker-ce-cli containerd.io
```

## Uninstall Docker Engine

1. Uninstall the Docker Engine, CLI, and Containerd packages:

   ```
   $ sudo apt-get purge docker-ce docker-ce-cli containerd.io
   ```

2. Images, containers, volumes, or customized configuration files on your host are not automatically removed. To delete all images, containers, and volumes:

   ```
   $ sudo rm -rf /var/lib/docker
   ```

You must delete any edited configuration files manually.

## nodejs

## 查看debian版本

```
https://www.jianshu.com/p/819b923595f8
```

## 升级debian10

> 更新已有软件

先将本地软件更新到最新版，然后再升级 debian 不然很有可能会出现一些未知的问题。

更新软件索引

```
sudo apt update
```

更新本地所有软件

```
sudo apt full-upgrade
```

> 升级到 debian 10 buster

升级到 debian 10 之前请请确认你没有添加过奇怪的软件源，或者编译过一些未知的东西，如果有的话请了解一下你自己之前的操作会不会对系统造成损伤，如果有的话不建议升级，容易出问题。本次升级基于官方源进行。

切换 stretch 源到 buster 源

```
sudo sed -i 's/stretch/buster/g' /etc/apt/sources.list
```

更新索引

```
sudo apt update
```

升级 debian stretch 到 debian buster

```
sudo apt upgrade
```

## npm does not support Node.js v10.19.0

```
npm install npm@latest -g
```

