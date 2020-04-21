# docker

------

[TOC]

------

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
sudo yum install docker-ce docker-ce-cli containerd.io
yum list docker-ce --showduplicates | sort -r
sudo yum install docker-ce-<VERSION_STRING> docker-ce-cli-<VERSION_STRING> containerd.io
sudo systemctl start docker
sudo systemctl enable docker
docker --version


```

## docker-compose

```sh
sudo curl -L "https://github.com/docker/compose/releases/download/1.25.4/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
docker-compose --version
```

## portainer

```sh
docker volume create portainer_data
docker run -d -p 30302:8000 -p 30301:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
```

```
swarm
docker service create \
    --name portainer \
    --publish 9000:9000 \
    --publish 8000:8000 \
    --replicas=1 \
    --constraint 'node.role == manager' \
    --mount type=bind,src=//path/on/host/data,dst=/data \
    portainer/portainer
$ curl -L https://downloads.portainer.io/portainer-agent-stack.yml -o portainer-agent-stack.yml
$ docker stack deploy --compose-file=portainer-agent-stack.yml portainer
```

java8111

```
docker pull java:8u111
```

### jar 启动

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



### create network

```sh
docker network create --subnet=172.19.0.0/16 net_tg
```

### docker run -d自动停止

```sh
选项只是在deamon模式下运行一个容器。
所以让你的容器连续运行的技巧是指向Docker中的shell文件，它将保持你的应用程序运行。你可以尝试一个start.sh文件
 Eg: docker run -d centos sh /yourlocation/start.sh 
这start.sh应该指向一个永无止境的应用程序。
```

### docker swarm

```
docker swarm init --advertise-addr <MANAGER-IP>
docker swarm init --advertise-addr 47.244.157.40
```

join

```
hostname tg03
docker swarm join --token SWMTKN-1-4txqpt9kdsbk4whavh18c6ridgrvavto5mn0nn9n1efwr3wva3-e704tes4xv8j01xgcnbah0fs1 47.244.157.40:2377
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
docker network create --driver=overlay --attachable test-net    //manager节点
docker run -it --name alpine1 --network test-net alpine   //manager节点
docker run -dit --name alpine2 --network test-net alpine   //worker节点
ping -c 2 alpine2   //manager节点
```

