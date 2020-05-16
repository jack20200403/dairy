# docker

## install

```sh
sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
sudo yum install -y yum-utils
sudo yum-config-manager \
    --add-repo \
    https://download.docker.com/linux/centos/docker-ce.repo
sudo yum-config-manager --enable docker-ce-nightly
sudo yum -y install docker-ce docker-ce-cli containerd.io
yum list docker-ce --showduplicates | sort -r
sudo yum -y install docker-ce-<VERSION_STRING> docker-ce-cli-<VERSION_STRING> containerd.io
sudo yum -y install docker-ce-18.09.0-3.el7 docker-ce-cli-18.09.0-3.el7 containerd.io
sudo systemctl start docker
sudo systemctl enable docker
docker --version
```

## 修改默认数据目录

```sh
systemctl stop docker
mv /var/lib/docker /data/setup/
ln -s /data/setup/docker /var/lib/docker
systemctl start docker
```

## uninstall

```
sudo yum remove docker \
                  docker-client \
                  docker-client-latest \
                  docker-common \
                  docker-latest \
                  docker-latest-logrotate \
                  docker-logrotate \
                  docker-engine
sudo yum -y remove docker-ce docker-ce-cli containerd.io
rm -rf /var/lib/docker
```

####  cannot remove '/var/lib/docker' device or resource busy

```
lsof +D /var/lib/docker
lsof +D /var/lib/docker | awk '{print $2}'| xargs kill -9
ps -ef | grep rtprecv | grep -v grep | awk '{print $2}' | xargs kill -9
umount /var/lib/docker/containers/3415751455dfe81192e860bee688197d2de5d91873090a59b88da1a24870e879/mounts/shm
umount /var/lib/docker/containers/3f028b9d20216349a71a73d3622861c64eb50d8113fad99508927013b9012c5d/mounts/shm
```



## portainer

```sh
docker volume create portainer_data
docker run -d -p 10007:8000 -p 10008:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
```

```
swarm
docker service create \
    --name portainer \
    --publish 10003:9000 \
    --publish 10004:8000 \
    --replicas=1 \
    --constraint 'node.role == manager' \
    --mount type=bind,src=/data/setup/portainer,dst=/data \
    portainer/portainer
$ curl -L https://downloads.portainer.io/portainer-agent-stack.yml -o portainer-agent-stack.yml
$ docker stack deploy --compose-file=portainer-agent-stack.yml portainer
```

java8111

```
docker pull java:8u111
```

## jar 启动

```sh
#!/bin/bash
docker run -tdi \
--name tg_center_be \
--net net_tg --ip 172.19.0.2 \
-v $PWD:/www/wwwroot/ \
java:8u111 \
sh -c 'cd  /www/wwwroot/ && chmod -R +x ./* && ./run.sh'
```

```sh
docker service create \
--name tg_center_be \
--mode global \
--mount type=volume,source=tg_center_be_voluem,destination=/www/wwwroot/,volume-label="tg_center_be" \
java:8u111 \
sh -c 'cd  /www/wwwroot/ && chmod -R +x ./* && ./run.sh'
```



## create network

```sh
docker network create --subnet=172.19.0.0/16 net_tg
```

### docker0: iptables: No chain/target/match by that name. 报错

```
service docker restart
```

### no route to host

```
service docker restart
```



### docker run -d自动停止

```sh
选项只是在deamon模式下运行一个容器。
所以让你的容器连续运行的技巧是指向Docker中的shell文件，它将保持你的应用程序运行。你可以尝试一个start.sh文件
 Eg: docker run -d centos sh /yourlocation/start.sh 
这start.sh应该指向一个永无止境的应用程序。
```

## docker swarm

```
docker swarm init --advertise-addr <MANAGER-IP>
docker swarm init --advertise-addr 45.249.93.194 --data-path-port 10008
```

解决云服务器docker swarm节点间无法通信问题
原创wavesheep 最后发布于2020-01-30 19:49:23 阅读数 253  收藏
展开
原因
如果你的swarm运行在默认端口，那么你就可能和我一样遇到了VXLAN默认端口4789/udp被云服务厂商阻断的问题。比如阿里云在文档中提到了这点，链接->阿里云添加udp监听文档。

解决方案
这个问题在docker:v19.03之前无法直接解决。19.03版本，docker在swarm init之上增加了–data-path-port uint32 的配置项用于更改docker swarm的VXLAN端口。
下面以指定端口5789/udp为例

```
sudo docker swarm init --data-path-port 5789
```

开放端口

```
2376
2377
2379
7946
4789
TCP port 2376 for secure Docker client communication. This port is required for Docker Machine to work. Docker Machine is used to orchestrate Docker hosts.
TCP port 2377. This port is used for communication between the nodes of a Docker Swarm or cluster. It only needs to be opened on manager nodes.
TCP and UDP port 7946 for communication among nodes (container network discovery).
UDP port 4789 for overlay network traffic (container ingress networking).
```

join

修改hostname

```
vim /etc/hostname
reboot
```

```sh
docker swarm join --token SWMTKN-1-6dovo6h7qb9ghke005hyfozxnjyw3nfovb4ljnsomsircfasbq-76itehv4u2nt71xwynkfi2ubo 45.249.93.194:2377
```

leave

```
 docker swarm leave
```

delete

```sh
docker node ls
docker node rm fj6978y2l1ppfmf0sayxsiye6
```

### 在不同主机上的容器之间通信

- 初始化swarm集群
- 在manager节点创建一个overlay网络
- 在manager节点上创建一个容器，加入这个网络
- 在worker节点上创建一个容器，加入这个网络
- 这两个容器之间可以ping通

```swift
docker swarm init    //manager节点
docker swarm join --token <your_token> <your_ip_address>:2377  //worker节点
docker network create --driver=overlay --attachable netTg    //manager节点
docker run -it --name alpine03 --network netTg alpine   //manager节点
docker run -dit --name alpine2 --network netTg alpine   //worker节点
docker run -dit --name alpine3 --network netTg alpine 
docker run -dit --name alpine4 --network netTg alpine
ping -c 2 alpine2   //manager节点
```

Error grabbing logs: rpc error: code = Unknown desc = warning: incomplete log stream. some logs could not be retrieved for the following reasons: node uvnej3i26e7d1dgjpehydcqw2 is not available

```

```



## docker-compose

install

```sh
sudo curl -L "https://github.com/docker/compose/releases/download/1.25.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
docker-compose --version
```

外部网络

```
networks:
  netTg:
    external:
      name: netTg
```

删除容器

```
docker rm `docker ps -aq`
```

## 远程访问

```

```

## 构建镜像

```shell
docker build -t registry-intl.cn-hangzhou.aliyuncs.com/com-tg/com-tg-center-cron-admin:2020.5.15.SNAPSHOT .
```

## dockerfile语法

1、FROM

> 语法：



```dockerfile
FROM <image>[:<tag>]
```

> 解释：设置要制作的镜像基于哪个镜像，FROM指令必须是整个Dockerfile的第一个指令，如果指定的镜像不存在默认会自动从  Docker Hub上下载。

2、MAINTAINAER

> 语法：



```dockerfile
MAINTAINER <name>
```

> 解释：MAINTAINER指令允许你给将要制作的镜像设置作者信息。

3、RUN

> 语法：



```dockerfile
1、RUN <command>  #将会调用/bin/sh -c <command>
2、RUN ["executable", "param1", "param2"] #将会调用exec执行，以避免有些时候shell方式执行时的传递参数问题，而且有些基础镜像可能不包含/bin/sh
```

> 解释：RUN指令会在一个新的容器中执行任何命令，然后把执行后的改变提交到当前镜像，提交后的镜像会被用于Dockerfile中定义的下一步操作，RUN中定义的命令会按顺序执行并提交，这正是Docker廉价的提交和可以基于镜像的任何一个历史点创建容器的好处，就像版本控制工具一样。

4、ENTRYPOINT

> 语法:



```dockerfile
1、ENTRYPOINT ["executable", "param1", "param2"]        #将会调用exec执行，首选方式
2、ENTRYPOINT command param1 param2             #将会调用/bin/sh -c执行
```

> 解释：ENTRYPOINT指令中指定的命令会在镜像运行时执行，在Dockerfile中只能存在一个，如果使用了多个ENTRYPOINT指令，则只有最后一个指令有效。ENTRYPOINT指令中指定的命令(exec执行的方式)可以通过docker run来传递参数，例如docker run <images> -l启动的容器将会把-l参数传递给ENTRYPOINT指令定义的命令并会覆盖CMD指令中定义的默认参数(如果有的话)，但不会覆盖该指令定义的参数，例如ENTRYPOINT ["ls","-a"]，CMD ["/etc"],当通过docker run <image>启动容器时该容器会运行ls -a /etc命令，当使用docker run <image> -l启动时该容器会运行ls -a -l命令，-l参数会覆盖CMD指令中定义的/etc参数。

*注意：
 ①当使用ENTRYPOINT指令时生成的镜像运行时只会执行该指令指定的命令。
 ②当出现ENTRYPOINT指令时CMD指令只可能(当ENTRYPOINT指令使用exec方式执行时)被当做ENTRYPOINT指令的参数使用，其他情况则会被忽略。*

5、CMD

> 语法：



```dockerfile
1、CMD ["executable", "param1", "param2"]    #将会调用exec执行，首选方式
2、CMD ["param1", "param2"]        #当使用ENTRYPOINT指令时，为该指令传递默认参数
3、CMD <command> [ <param1>|<param2> ]        #将会调用/bin/sh -c执行
```

> 解释：CMD指令中指定的命令会在镜像运行时执行，在Dockerfile中只能存在一个，如果使用了多个CMD指令，则只有最后一个CMD指令有效。当出现ENTRYPOINT指令时，CMD中定义的内容会作为ENTRYPOINT指令的默认参数，也就是说可以使用CMD指令给ENTRYPOINT传递参数。

*注意：RUN和CMD都是执行命令，他们的差异在于RUN中定义的命令会在执行docker build命令创建镜像时执行，而CMD中定义的命令会在执行docker run命令运行镜像时执行，另外使用第一种语法也就是调用exec执行时，命令必须为绝对路径。*

6、EXPOSE

> 语法：



```dockerfile
EXPOSE <port> [.....]
```

> 解释：EXPOSE指令用来告诉Docker这个容器在运行时会暴露哪些端口，Docker在连接不同的容器(使用–link参数)时使用这些信息。

7、ENV

> 语法：



```dockerfile
ENV <key> <value>
```

> 解释：
>  ENV指令用于设置环境变量，在Dockerfile中这些设置的环境变量也会影响到RUN指令，当运行生成的镜像时这些环境变量依然有效，如果需要在运行时更改这些环境变量可以在运行docker run时添加–env <key>=<value>参数来修改。

*注意：最好不要定义那些可能和系统预定义的环境变量冲突的名字，否则可能会产生意想不到的结果。*

8、ADD

> 语法：



```dockerfile
ADD <src> <dest>
```

> 解释：
>  ADD指令用于从指定路径拷贝一个文件或目录到容器的指定路径中，<src>是一个文件或目录的路径，也可以是一个url，路径是相对于该Dockerfile文件所在位置的相对路径，<dest>是目标容器的一个绝对路径，例如/home/yooke/Docker/Dockerfile这个文件中定义的，那么ADD /data.txt /db/指令将会尝试拷贝文件从/home/yooke/Docker/data.txt到将要生成的容器的/db/data.txt，且文件或目录的属组和属主分别为uid和gid为0的用户和组，如果是通过url方式获取的文件，则权限是600。

*注意：
 ①如果执行docker build – < somefile即通过标准输入来创建时，ADD指令只支持url方式，另外如果url需要认证，则可以通过RUN wget …或RUN curl …来完成，ADD指令不支持认证。*

*②路径必须与Dockerfile在同级目录或子目录中，例如不能使用ADD ../somepath，因为在执行docker build时首先做的就是把Dockerfile所在目录包含子目录发送给docker的守护进程。*

*③如果是一个url且不是以”/“结尾，则会下载文件并重命名为。*

*④如果是一个url且以“/”结尾，则会下载文件到/，url必须是一个正常的路径形式，“[http://example.com](https://link.jianshu.com?t=http://example.com)”像这样的url是不能正常工作的。*

*⑤如果<src>是一个本地的压缩包且<dest>是以“/”结尾的目录，则会调用“tar -x”命令解压缩，如果<dest>有同名文件则覆盖，但<src>是一个url时不会执行解压缩.

- 

9、COPY

> 语法：



```dockerfile
COPY <src> <dest>
```

> 解释：用法与ADD相同，不过<src>不支持使用url，所以在使用docker build – < somefile时该指令不能使用。

10、VOLUME

> 语法：



```dockerfile
VOLUME ["samepath"]
```

> 解释：
>  VOLUME指令用来设置一个挂载点，可以用来让其他容器挂载以实现数据共享或对容器数据的备份、恢复或迁移。

11、USER

> 语法：



```dockerfile
USER [username|uid]
```

> 解释：
>  USER指令用于设置用户或uid来运行生成的镜像和执行RUN指令。

12、WORKDIR

> 语法：



```dockerfile
WORKDIR /path/to/workdir
```

> 解释：
>  WORKDIR指令用于设置Dockerfile中的RUN、CMD和ENTRYPOINT指令执行命令的工作目录(默认为/目录)，该指令在Dockerfile文件中可以出现多次，如果使用相对路径则为相对于WORKDIR上一次的值，例如WORKDIR /data，WORKDIR logs，RUN pwd最终输出的当前目录是/data/logs。

13、ONBUILD

> 语法：



```dockerfile
ONBUILD [INSTRUCTION]
```

> 解释：
>  a、ONBUILD指令可以为镜像添加触发器。其参数是任意一个Dockerfile 指令。
>  当我们在一个Dockerfile文件中加上ONBUILD指令，该指令对利用该Dockerfile构建镜像（比如为A镜像）不会产生实质性影响。
>  b、但是当我们编写一个新的Dockerfile文件来基于A镜像构建一个镜像（比如为B镜像）时，这时构造A镜像的Dockerfile文件中的ONBUILD指令就生效了，在构建B镜像的过程中，首先会执行ONBUILD指令指定的指令，然后才会执行其它指令。
>  c、需要注意的是，如果是再利用B镜像构造新的镜像时，那个ONBUILD指令就无效了，也就是说只能再构建子镜像中执行，对孙子镜像构建无效。其实想想是合理的，因为在构建子镜像中已经执行了，如果孙子镜像构建还要执行，相当于重复执行，这就有问题了。
>  d、利用ONBUILD指令,实际上就是相当于创建一个模板镜像，后续可以根据该模板镜像创建特定的子镜像，需要在子镜像构建过程中执行的一些通用操作就可以在模板镜像对应的dockerfile文件中用ONBUILD指令指定。 从而减少dockerfile文件的重复内容编写。

14、ARG

> ARG是Docker1.9 版本才新加入的指令。
>  ARG 定义的变量只在建立 image 时有效，建立完成后变量就失效消失
>  ARG指令定义了一个变量，能让用户可以在构建期间使用[docker](https://link.jianshu.com?t=https://www.centos.bz/tag/docker/) build命令和其参数–build-arg =对这个变量赋值。如果用户指定了一个构建参数没有定义在[Dockerfile](https://link.jianshu.com?t=https://www.centos.bz/tag/dockerfile/)的话，将输出错误。



## jar

```dockerfile
FROM fabric8/java-alpine-openjdk8-jdk:1.8.0
MAINTAINER tg
ENV PARAMS=""
ENV TZ=PRC
COPY ./doc/font/Algerian.ttf /usr/share/fonts/Algerian.ttf
ENV LANG en_US.UTF-8
RUN apk add --update ttf-dejavu fontconfig && rm -rf /var/cache/apk/*
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone
ADD target/com-tg-center-be.jar /app.jar
ENTRYPOINT ["sh","-c","java -jar $PARAMS /app.jar "]
EXPOSE 8080
```

## war

```dockerfile
FROM docker.io/tomcat:8-jdk8-openjdk
MAINTAINER tg(tg@tg.com)
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
RUN echo 'Asia/Shanghai' >/etc/timezone
COPY  target/lottery-core.war   /usr/local/tomcat/webapps
COPY  tomcat/conf/server.xml  /usr/local/tomcat/conf/server.xml
WORKDIR /usr/local/tomcat
CMD ["/usr/local/tomcat/bin/catalina.sh", "run"]
```

## nginx

```dockerfile
FROM nginx:1.18.0-alpine
RUN ln -sf /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
RUN echo 'Asia/Shanghai' >/etc/timezone
COPY dist/ /usr/share/nginx/html/
COPY nginx/nginx.conf /etc/nginx/nginx.conf
COPY nginx/default.conf /etc/nginx/conf.d/default.conf
EXPOSE 8080
```

