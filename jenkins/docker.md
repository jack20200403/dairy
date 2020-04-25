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
sudo yum -y install docker-ce docker-ce-cli containerd.io
yum list docker-ce --showduplicates | sort -r
sudo yum install docker-ce-<VERSION_STRING> docker-ce-cli-<VERSION_STRING> containerd.io
sudo systemctl start docker
sudo systemctl enable docker
docker --version


```

## 修改默认数据目录

```sh
systemctl stop docker
mv /var/lib/docker /data/setup/docker
ln -s /data/setup/docker /var/lib/docker
systemctl start docker
```

## uninstall docker

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
docker run -d -p 30302:8000 -p 30301:9000 --name=portainer --restart=always -v /var/run/docker.sock:/var/run/docker.sock -v portainer_data:/data portainer/portainer
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



## docker私服

### 搭建

```
$ sudo docker pull registry
```

下载完之后我们通过该镜像启动一个容器默认情况下，会将仓库存放于容器的/tmp/registry目录下，这样如果容器被删除，则存放于容器中的镜像也会丢失，所以我们一般情况下会指定本地一个目录挂载到容器的/tmp/registry下，如下：
```
$ sudo docker run -d -p 10007:5000 -v /opt/data/registry:/tmp/registry registry
```

### 提交镜像

pull一个比较小的镜像来测试（此处使用的是busybox）

```
$ sudo docker pull busybox
```

接下来修改一下该镜像的tag

```
$ sudo docker tag busybox 192.168.112.136:5000/busybox
```

接下来把打了tag的镜像上传到私服

```
$ sudo docker push 192.168.112.136:5000/busybox
```

可以看到push失败，具体结果如下：
2015/01/05 11:01:17 Error: Invalid registry endpoint https://192.168.112.136:5000/v1/: Get https://192.168.112.136:5000/v1/_ping: dial tcp 192.168.112.136:5000: connection refused. If this private registry supports only HTTP or HTTPS with an unknown CA certificate, please add `--insecure-registry 192.168.112.136:5000` to the daemon's arguments. In the case of HTTPS, if you have access to the registry's CA certificate, no need for the flag; simply place the CA certificate at /etc/docker/certs.d/192.168.112.136:5000/ca.crt

为了解决这个问题需要在启动docker server时增加启动参数
修改docker启动配置文件（此处是修改132机器的配置）Ubuntu下配置文件地址为：/etc/init/docker.conf
在其中增加--insecure-registry 192.168.112.136:5000如下所示：

$ sudo vi /etc/init/docker.conf

![img](https://img-blog.csdn.net/20150105143252265)

修改完之后，重启Docker服务

```sh
$ sudo restart docker
```

## kubernetes

### 一键安装

#### 服务器之间免密登录

```
ssh-keygen
ssh-copy-id -i /root/.ssh/id_rsa.pub -p 10001 root@45.249.93.194
ssh-copy-id -i /root/.ssh/id_rsa.pub -p 10001 root@202.52.144.50
ssh-copy-id -i /root/.ssh/id_rsa.pub -p 10001 root@103.211.99.235
ssh-copy-id -i /root/.ssh/id_rsa.pub -p 10001 root@47.244.157.40

```

```
# 下载并安装sealos, sealos是个golang的二进制工具，直接下载拷贝到bin目录即可, release页面也可下载
wget -c https://sealyun.oss-cn-beijing.aliyuncs.com/latest/sealos && \
    chmod +x sealos && mv sealos /usr/bin 

# 下载离线资源包
wget -c https://sealyun.oss-cn-beijing.aliyuncs.com/d551b0b9e67e0416d0f9dce870a16665-1.18.0/kube1.18.0.tar.gz 

# 安装一个三master的kubernetes集群
sealos init \
	--master 45.249.93.194:10001  \
	--node 202.52.144.50:10001 \
	--node 103.211.99.235:10001 \
	--node 47.244.157.40:10001 \
	--pkg-url kube1.18.0.tar.gz \
	--user root \
	--pk /root/.ssh/id_rsa \
	--version v1.18.0
```

检查安装是否正常:

```sh
[root@iZj6cdqfqw4o4o9tc0q44rZ ~]# kubectl get node
```

### 安装prometheus

```
grafana http://集群节点IP:30000 初始账户密码 admin/admin
```



### 安装kuboard

```
http://你的master地址:32567
```



```
eyJhbGciOiJSUzI1NiIsImtpZCI6IlUwVXNEdWdTWnp1TzNodlV0Nm5NdmtkOGtNNXBFbUFUTWJ4X3lJa3BSQkEifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlLXN5c3RlbSIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJrdWJvYXJkLXVzZXItdG9rZW4tenQyY2wiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoia3Vib2FyZC11c2VyIiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiYjgwMjFjZjMtZWRjZC00MjZjLTg2MzYtYzkxZjgwMjNlOGYwIiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50Omt1YmUtc3lzdGVtOmt1Ym9hcmQtdXNlciJ9.HGwiKN_DQjB-m5dANWDH2vZLREneY9VM5caZcrpTFmy_-NBD1S7vfefXfsB26BweqoEq7p43CMVflkyPDgfQceMlCJKFNqanIXZ0PBzBVlIBA7hsXjTtfRuq0_Cs7HECT5EryhIJQcCH8FYPDwzj9kxUh_4_-GCO94GCKVmmCERTjzooGpe4x7pamPDQsz6FKw6xpm654245rSEXsPuJPLnRS5Zj_NJ8CkM_bzfnNVHj6itnBt-plUdttdWL8u8-COphPPF-koHZVWIfuVkHy1htK0F9LS8EpsrZk8m4yPOo0ZelGbGrVR1Nk0EWOUko7AbLnrOcrTjo9yMtk_DL6A
```



### 安装dashboard

```
sealos install --pkg-url https://github.com/sealstore/dashboard/releases/download/v2.0.0-bata5/dashboard.tar
```

使用上述命令安装完dashboard后日志中会输出token，登录页面时需要使用.

https://你的master地址:32000 chrome访问不了就用火狐

```
eyJhbGciOiJSUzI1NiIsImtpZCI6IlUwVXNEdWdTWnp1TzNodlV0Nm5NdmtkOGtNNXBFbUFUTWJ4X3lJa3BSQkEifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlcm5ldGVzLWRhc2hib2FyZCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJrdWJlcm5ldGVzLWRhc2hib2FyZC10b2tlbi1nNXoyNiIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50Lm5hbWUiOiJrdWJlcm5ldGVzLWRhc2hib2FyZCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50LnVpZCI6IjNmNzdhYWEwLTEzNzktNGQ2MS04ZDk2LTg1MzUwNmQwYWU1YSIsInN1YiI6InN5c3RlbTpzZXJ2aWNlYWNjb3VudDprdWJlcm5ldGVzLWRhc2hib2FyZDprdWJlcm5ldGVzLWRhc2hib2FyZCJ9.2GClcSfv9XbDV5Rg6bmdZIf9ny-4HQUN4WmCdB06yWkDFxvrDMYNHn0BB3xByGmEggbMSt8-AfREtxFK5bPHNGYzH7ahAs870apNtIG0ndBMKh1YF1WKNmRock5Z-9FGG_-5KENiNI9OItIrXjqZoUtNGuxqqlQ8OtLN_O8MoYjoPdBlJ3n0rWfVJFO3Jkf7-13757sn3jWjgR5ctumkFFH_ka3mxa1cyBQ8qMwYsL-lR06pOpOhYiBmON7w3HKTJBtRE0MuGw-WSk_CjYP1sQtTjywbJJ_uriFYxXee8hEYl1DFHRiysovI0fVEwNvFSkB9-7FuPBs-iYi-SGtwKQ
```

#### 增加node

```shell
sealos join --node 202.52.144.50:10001
sealos join --node 103.211.99.235:10001
sealos join --node 47.244.157.40:10001
```

删除master

```
sealos clean --master 45.249.93.194:10001

sealos clean --master 192.168.0.6-192.168.0.9  # 或者多个连续IP
```

#### 删除node

```
sealos clean --node 202.52.144.50:10001
sealos clean --node 103.211.99.235:10001
sealos clean --node 47.244.157.40:10001

sealos clean --node 192.168.0.6-192.168.0.9  # 或者多个连续IP

kubeadm reset
```

### 安装ingress

```
helm install stable/nginx-ingress --name nginx-ingress -f https://raw.githubusercontent.com/qhh0205/helm-charts/master/nginx-ingress-values.yml
```

```sh
kubectl apply -f https://kuboard.cn/install-script/v1.16.2/nginx-ingress.yaml
```

### 安装nacos

```
git clone https://github.com/nacos-group/nacos-k8s.git
```

#### 部署 NFS

- 创建角色

```shell
kubectl create -f deploy/nfs/rbac.yaml
```

如果的K8S命名空间不是**default**，请在部署RBAC之前执行以下脚本:

```shell
# Set the subject of the RBAC objects to the current namespace where the provisioner is being deployed
$ NS=$(kubectl config get-contexts|grep -e "^\*" |awk '{print $5}')
$ NAMESPACE=${NS:-default}
$ sed -i'' "s/namespace:.*/namespace: $NAMESPACE/g" ./deploy/nfs/rbac.yaml
```

- 创建 `ServiceAccount` 和部署 `NFS-Client Provisioner`

```shell
kubectl create -f deploy/nfs/deployment.yaml
```

error: unable to recognize "deployment.yaml": no matches for kind "Deployment" in version "extensions/v1beta1"

```
As deployment in the extensions/v1beta1 was deprecated from
K8S 1.16, so change the deployment to suit K8S 1.16 version
and later.

Ref: https://kubernetes.io/blog/2019/07/18/api-deprecations-in-1-16/

Please read https://github.com/coreos/etcd-operator/blob/master/CONTRIBUTING.md#contribution-flow
```



- 创建 NFS StorageClass

```shell
kubectl create -f deploy/nfs/class.yaml
```

- 验证NFS部署成功

```shell
kubectl get pod -l app=nfs-client-provisioner
```

#### 部署数据库

- 部署主库

```shell
cd nacos-k8s

kubectl create -f deploy/mysql/mysql-master-nfs.yaml
```

- 部署从库

```shell
cd nacos-k8s 

kubectl create -f deploy/mysql/mysql-slave-nfs.yaml
```

- 验证数据库是否正常工作

```shell
# master
kubectl get pod 
NAME                         READY   STATUS    RESTARTS   AGE
mysql-master-gf2vd                        1/1     Running   0          111m

# slave
kubectl get pod 
mysql-slave-kf9cb                         1/1     Running   0          110m
```

#### 部署Nacos

- 修改  **deploy/nacos/nacos-pvc-nfs.yaml**

```yaml
data:
  mysql.master.db.name: "主库名称"
  mysql.master.port: "主库端口"
  mysql.slave.port: "从库端口"
  mysql.master.user: "主库用户名"
  mysql.master.password: "主库密码"
```

- 创建 Nacos

```shell
kubectl create -f nacos-k8s/deploy/nacos/nacos-pvc-nfs.yaml
```

- 验证Nacos节点启动成功

```shell
kubectl get pod -l app=nacos


NAME      READY   STATUS    RESTARTS   AGE
nacos-0   1/1     Running   0          19h
nacos-1   1/1     Running   0          19h
nacos-2   1/1     Running   0          19h
```

#### 扩容测试

- 在扩容前，使用 [`kubectl exec`](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands/#exec)获取在pod中的Nacos集群配置文件信息

```powershell
for i in 0 1; do echo nacos-$i; kubectl exec nacos-$i cat conf/cluster.conf; done
```

StatefulSet控制器根据其序数索引为每个Pod提供唯一的主机名。 主机名采用  -  的形式。 因为nacos StatefulSet的副本字段设置为2，所以当前集群文件中只有两个Nacos节点地址

![k8s](https://cdn.nlark.com/yuque/0/2019/gif/338441/1562846123635-e361d2b5-4bbe-4347-acad-8f11f75e6d38.gif)

- 使用kubectl scale 对Nacos动态扩容

```bash
kubectl scale sts nacos --replicas=3
```

![scale](https://cdn.nlark.com/yuque/0/2019/gif/338441/1562846139093-7a79b709-9afa-448a-b7d6-f57571d3a902.gif)

- 在扩容后，使用 [`kubectl exec`](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands/#exec)获取在pod中的Nacos集群配置文件信息

```bash
for i in 0 1 2; do echo nacos-$i; kubectl exec nacos-$i cat conf/cluster.conf; done
```

![get_cluster_after](https://cdn.nlark.com/yuque/0/2019/gif/338441/1562846177553-c1c7f379-1b41-4026-9f0b-23e15dde02a8.gif)

- 使用 [`kubectl exec`](https://kubernetes.io/docs/reference/generated/kubectl/kubectl-commands/#exec)执行Nacos API 在每台节点上获取当前**Leader**是否一致

```bash
for i in 0 1 2; do echo nacos-$i; kubectl exec nacos-$i curl -X GET "http://localhost:8848/nacos/v1/ns/raft/state"; done
```

到这里你可以发现新节点已经正常加入Nacos集群当中

## 搭建NFS Server

### 配置NFS服务器

服务器端防火墙开放111、662、875、892、2049的 tcp / udp 允许，否则远端客户无法连接。

- 执行以下命令安装 nfs 服务器所需的软件包

  ```sh
  yum install -y nfs-utils
  ```

- 执行命令

  ```
  vim /etc/exports
  ```

  ，创建 exports 文件，文件内容如下：

  ```text
  /data/nfs_root/ *(insecure,rw,sync,no_root_squash)
  
  /home/nfs_root/ *(insecure,rw,sync,no_root_squash)
  ```

- 执行以下命令，启动 nfs 服务

  ```sh
  # 创建共享目录，如果要使用自己的目录，请替换本文档中所有的 /root/nfs_root/
  mkdir /data/nfs_root
  
  systemctl enable rpcbind
  systemctl enable nfs-server
  
  systemctl start rpcbind
  systemctl start nfs-server
  exportfs -r
  ```

- 检查配置是否生效

  ```sh
  exportfs
  # 输出结果如下所示
  /root/nfs_root /root/nfs_root
   
  ```

### 在客户端测试nfs

- 服务器端防火墙开放111、662、875、892、2049的 tcp / udp 允许，否则远端客户无法连接。

- 执行以下命令安装 nfs 客户端所需的软件包

  ```sh
  yum install -y nfs-utils
  ```

- 执行以下命令检查 nfs 服务器端是否有设置共享目录

  ```sh
  # showmount -e $(nfs服务器的IP)
  showmount -e 202.52.144.50
  # 输出结果如下所示
  Export list for 172.17.216.82:
  /root/nfs_root *
      
  ```

- 执行以下命令挂载 nfs 服务器上的共享目录到本机路径 `/root/nfsmount`

  ```sh
  mkdir /root/nfsmount
  # mount -t nfs $(nfs服务器的IP):/root/nfs_root /root/nfsmount
  mount -t nfs 172.17.216.82:/root/nfs_root /root/nfsmount
  # 写入一个测试文件
  echo "hello nfs server" > /root/nfsmount/test.txt
      
  ```

- 在 nfs 服务器上执行以下命令，验证文件写入成功

  ```sh
  cat /root/nfs_root/test.txt
  ```

### 在Kuboard中创建 NFS 存储类

- 打开 Kuboard 的集群概览页面，点击 **创建存储类** 按钮，如下图所示

  填写表单输入表单

  | 字段名称   | 填入内容       | 备注                              |
  | ---------- | -------------- | --------------------------------- |
  | 名称       | nfs-storage    | 请自定义名称                      |
  | NFS Server | 172.17.216.82  | 请使用您自己的NFS服务的IP地址     |
  | NFS Path   | /root/nfs_root | 请使用您自己的NFS服务所共享的路径 |

  ![Kubernetes教程_在Kuboard中创建NFS_StorageClass存储类](https://kuboard.cn/assets/img/image-20191003183534076.2b3118cc.png)

- 在场景中使用存储类

  此时您可以在自己的场景中使用刚创建的存储类。Kuboard官网上，有以下几个地方可以用到NFS存储类：

  - [导入 example 微服务](https://kuboard.cn/guide/example/import.html)
  - [安装监控套件](https://kuboard.cn/guide/example/monitor.html#安装监控套件)

## bug

pod stuck on terminate

```
kubectl delete pod xxx --now
```



### 0/1 nodes are available: 1 node(s) had taint {node.kubernetes.io/not-ready: }, that the pod didn't tolerate.

```

```



### calicoUp

```
179
4789
5473
443
6443*
2379
Network requirements
Ensure that your hosts and firewalls allow the necessary traffic based on your configuration.

Configuration	Host(s)	Connection type	Port/protocol
Calico networking (BGP)	All	Bidirectional	TCP 179
Calico networking with IP-in-IP enabled (default)	All	Bidirectional	IP-in-IP, often represented by its protocol number 4
Calico networking with VXLAN enabled	All	Bidirectional	UDP 4789
Calico networking with Typha enabled	Typha agent hosts	Incoming	TCP 5473 (default)
flannel networking (VXLAN)	All	Bidirectional	UDP 4789
All	kube-apiserver host	Incoming	Often TCP 443 or 6443*
etcd datastore	etcd hosts	Incoming	Officially TCP 2379 but can vary
```

unknown

```
多部署几台
kube-system / monitor-kube-state-metrics
```

