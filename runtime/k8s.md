# k8s

## 一键安装

清除已有iptables规则

```
iptables -F
iptables -X
iptables -Z
```

关闭防火墙

```
查看当前防火墙状态：systemctl status firewalld.service
禁止开机启动：systemctl disable firewalld.service
关闭防火墙：systemctl stop firewalld.service
```

关闭SELinux

```
打开文件/etc/selinux/config，找到SELINUX=xxxxx这行，改为SELINUX=disabled；
修改后需要重启机器；
```

开启IPV4转发

```
打开文件/etc/sysctl.conf，检查是否有net.ipv4.ip_forward = x这样的配置；
如果有就保证x等于1，如果没有就加一行：net.ipv4.ip_forward = 1
修改并保存后，执行命令sysctl -p使配置生效；
执行命令sysctl -a|grep “ip_forward”，查看最新的配置，应该有如下内容：
net.ipv4.ip_forward = 1
net.ipv4.ip_forward_use_pmtu = 0
```

服务器之间免密登录

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

# 安装一个三master的kubernetes集群 至少3个master
sealos init \
--master 202.52.144.50:10001 \
--node 45.249.93.194:10001 \
--node 103.211.99.235:10001 \
--pkg-url kube1.18.0.tar.gz \
--user root \
--pk /root/.ssh/id_rsa \
--version v1.18.0

```

检查安装是否正常:

```sh
[root@iZj6cdqfqw4o4o9tc0q44rZ ~]# kubectl get node
```

## 管理node

增加node

```shell
sealos join --master 45.249.93.194:10001
sealos join --master 202.52.144.50:10001
sealos join --master 103.211.99.235:10001
sealos join --node 47.244.157.40:10001
```

删除master

```
sealos clean --master 45.249.93.194:10001
sealos clean --master 192.168.0.6-192.168.0.9  # 或者多个连续IP
```

删除node

```
sealos clean --node 202.52.144.50:10001
sealos clean --node 103.211.99.235:10001
sealos clean --node 47.244.157.40:10001
sealos clean --node 192.168.0.6-192.168.0.9  # 或者多个连续IP
kubeadm reset
sealos clean
```

```
rm -rf contour/
rm -rf dashboard/
rm -rf kuboard/
rm -rf prometheus/
rm -rf kubeadm-config.yaml
rm -rf /usr/bin/sealos
```



## 服务类型

```
Deployment
StatefulSet
DaemenSet
```

## 安装jenkins

## 使用阿里云私有仓库

访问 阿里云容器镜像服务

链接：https://cr.console.aliyun.com/cn-hongkong/instances/repositories

首先要设置一个叫做Registry密码，这个密码用来推送/拉取Docker镜像使用

创建私有镜像仓库

默认实例 —> 镜像仓库 —> 创建镜像仓库

可以选择镜像仓库的地域，这里开通的是香港节点的私有仓库

推送本地Docker镜像到阿里云私有仓库

```
#登录阿里云Docker Registry[按照提示输入Registry密码]
docker login --username=xxxxxx@1009xxx8864439 registry.cn-hongkong.aliyuncs.com

#设置镜像Tag
sudo docker tag [Image Id] registry.cn-hongkong.aliyuncs.com/qst_images/qst_store:[镜像名_版本号]

#推送镜像
docker push registry.cn-hongkong.aliyuncs.com/qst_images/qst_store:[镜像名_版本号]
```

拉取阿里云私有仓库镜像

```
#登录阿里云Docker Registry
docker login --username=--username=xxxxxx@1009xxx8864439 registry.cn-hongkong.aliyuncs.com

#拉取镜像
docker pull registry.cn-hongkong.aliyuncs.com/qst_images/qst_store:[镜像名_版本号]
```

## 安装kuboard

```
sealos install --pkg-url https://github.com/sealstore/dashboard/releases/download/v1.0-1/kuboard.tar
```

```
eyJhbGciOiJSUzI1NiIsImtpZCI6IlUwVXNEdWdTWnp1TzNodlV0Nm5NdmtkOGtNNXBFbUFUTWJ4X3lJa3BSQkEifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlLXN5c3RlbSIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJrdWJvYXJkLXVzZXItdG9rZW4tZGp2NXEiLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoia3Vib2FyZC11c2VyIiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiZmNmNDc3MjMtZjdmYi00ZmRmLTkyNmQtMzI4ZTA2YTlhZGNkIiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50Omt1YmUtc3lzdGVtOmt1Ym9hcmQtdXNlciJ9.3CxPZunggRGha5wjJWAqFn42APauNoSr7qWfsWnI-RMkJ8zzHsoLzfyOk_CxpvaMQB2trw6waNH95Surabul8UuploGOCbUp1PCjKSFPztMCiGVq2zUEv_j7S4Xuoj3yhYysy7_Er7FLblzLMD5SieejmuLznsFnV_wpVnnTbYf0nDmXLxL14B9QPZZiC1j3HfAjs8pmtZL5sXf1gWUUegpP-G1WQY1WJNdEHqeW4nLJkWHwCd8H5Xg-SSgOy3QHvzoFEvcPCcf4_3rA15ozZ-VfsPHbN6cvapeCKTY_ngK9Jbmdt2CWdSK1UWpFGV8jsvZBqiI6oiDQJJWfJiaOrg
```

```
http://你的master地址:32567
```

```
kubectl apply -f https://kuboard.cn/install-script/kuboard.yaml
kubectl apply -f https://addons.kuboard.cn/metrics-server/0.3.6/metrics-server.yaml
```

查看 Kuboard 运行状态：

```sh
kubectl get pods -l k8s.eip.work/name=kuboard -n kube-system
```

卸载

```
kubectl delete -f https://kuboard.cn/install-script/kuboard.yaml
kubectl delete -f https://addons.kuboard.cn/metrics-server/0.3.6/metrics-server.yaml
```

**拥有的权限**

- 此Token拥有 ClusterAdmin 的权限，可以执行所有操作

**执行命令**

```bash
# 如果您参考 www.kuboard.cn 提供的文档安装 Kuberenetes，可在第一个 Master 节点上执行此命令
echo $(kubectl -n kube-system get secret $(kubectl -n kube-system get secret | grep kuboard-user | awk '{print $1}') -o go-template='{{.data.token}}' | base64 -d)
```

```
eyJhbGciOiJSUzI1NiIsImtpZCI6IkNtRUp4dVdHbjJiSmVvMUZjV0RUQUtORDlncExHS0tKaFl4U2FJeEV0TDAifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlLXN5c3RlbSIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJrdWJvYXJkLXVzZXItdG9rZW4tcW5reHciLCJrdWJlcm5ldGVzLmlvL3NlcnZpY2VhY2NvdW50L3NlcnZpY2UtYWNjb3VudC5uYW1lIjoia3Vib2FyZC11c2VyIiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9zZXJ2aWNlLWFjY291bnQudWlkIjoiZDZiYjEwZmYtOGI2Yy00MDIwLTk1MDAtZWRjYjg5M2M1ZmU5Iiwic3ViIjoic3lzdGVtOnNlcnZpY2VhY2NvdW50Omt1YmUtc3lzdGVtOmt1Ym9hcmQtdXNlciJ9.SpbZIpzDNEDza8dVH7TWMrGoRZFC0hOeIZMufQ1UkL0UkjcU-5EOUu1WWXwi8jF5-GvssHwThE3mgI3PgmWCr_gtCX1aa9P6ID2Fwo0WtH7gkYyHWqDPoU-o3DUtz6ntNqH6rmN20X0v2_Ae5hQpPWH9PIJ9w0CyTRgFu5FU9aiRAc5ReTWk2stkAWL9W-9A_wqNJPxaHeHRm3YZwRv2NLRHuh6o3Z6xeESsLD-edoXjxUbN3As9ZZ9oeJexxh4T0OlCRK1gYdb53sKNH8hjo4KmRnynvZXSgoPsxbVniJskuNw_fA8zBrBS9wqAFU28I_lNUnOGb92DmkDNJ3ugIQ
```

## dashborad

使用上述命令安装完dashboard后日志中会输出token，登录页面时需要使用.

https://你的master地址:32000 chrome访问不了就用火狐

或者使用此命令获取token

```sh
kubectl get secret -nkubernetes-dashboard \
    $(kubectl get secret -n kubernetes-dashboard|grep dashboard-token |awk '{print $1}') \
    -o jsonpath='{.data.token}'  | base64 --decode
```

安装

```
sealos install --pkg-url https://github.com/sealstore/dashboard/releases/download/v2.0.0-bata5/dashboard.tar
```

```
eyJhbGciOiJSUzI1NiIsImtpZCI6IkNtRUp4dVdHbjJiSmVvMUZjV0RUQUtORDlncExHS0tKaFl4U2FJeEV0TDAifQ.eyJpc3MiOiJrdWJlcm5ldGVzL3NlcnZpY2VhY2NvdW50Iiwia3ViZXJuZXRlcy5pby9zZXJ2aWNlYWNjb3VudC9uYW1lc3BhY2UiOiJrdWJlcm5ldGVzLWRhc2hib2FyZCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VjcmV0Lm5hbWUiOiJrdWJlcm5ldGVzLWRhc2hib2FyZC10b2tlbi1xcWsybCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50Lm5hbWUiOiJrdWJlcm5ldGVzLWRhc2hib2FyZCIsImt1YmVybmV0ZXMuaW8vc2VydmljZWFjY291bnQvc2VydmljZS1hY2NvdW50LnVpZCI6Ijc2NDc5ZjI1LTI0MTktNDhmMC1iMTk2LTk5ZGViMWY4OGU5NyIsInN1YiI6InN5c3RlbTpzZXJ2aWNlYWNjb3VudDprdWJlcm5ldGVzLWRhc2hib2FyZDprdWJlcm5ldGVzLWRhc2hib2FyZCJ9.L6xTshBrXeCMD_0eMBJMR-hAHiCdk20G-S9BYYQTKvqq4_7dTpTWdMjz1f0JqfNks_b7l1Tya1smM18ws-zN0OO6yEVw24HS5BTTz2-9NEg_qJp62HalCSOysJWz5my2OHMKnwg0qBWeigcpnCj89r9DeWlxtillCXtmZ74SBT5kvu_TPZvTVeITDCHJnE8Ki9IQ7dwhiQ67LxDnyt3sc-uSUp3dWOj4_jt0rZBah67_bdGVfEqB8BcNGfRxghN1o_yon7lRp2UYp-UmQI7Hxyiq7aQQPCtpcAnJqW-AU0vggR70M3CMz6dE6X_U1gWYY7q_rI7FFqmLOfNSusdFAA
```

## kubectl命令

```
kubectl get pods --all-namespaces
```

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

## Kubernetes 将Pod调度到Master节点

出于安全考虑，默认配置下Kubernetes不会将Pod调度到Master节点。如果希望将k8s-master也当作Node使用，可以执行如下命令：

```
kubectl taint node k8s-master node-role.kubernetes.io/master-
kubectl taint node tg01 node-role.kubernetes.io/master-
kubectl taint node tg02 node-role.kubernetes.io/master-
kubectl taint node tg04 node-role.kubernetes.io/master-

```

其中k8s-master是主机节点hostname如果要恢复Master Only状态，执行如下命令：


```
kubectl taint node k8s-master node-role.kubernetes.io/master=""
```

## 安装nginx-ingress

```

```

## 卸载calico

```
#!/bin/bash
kubectl --namespace=kube-system delete ds calico-node
kubectl --namespace=kube-system delete deploy calico-policy-controller
kubectl --namespace=kube-system delete sa calico-node
kubectl --namespace=kube-system delete sa calico-policy-controller
kubectl --namespace=kube-system delete cm calico-config
kubectl --namespace=kube-system delete secret calico-etcd-secrets
```



## 安装flannel

## Kubernetes集成

使用flannel前需要配置

```
kube-controller-manager --allocate-node-cidrs=true --cluster-cidr=10.244.0.0/16
```

```sh
kubectl apply -f https://raw.githubusercontent.com/coreos/flannel/master/Documentation/kube-flannel.yml
```

这会启动flanneld容器，并配置CNI网络插件：

```sh
$ ps -ef | grep flannel | grep -v grep
root      3625  3610  0 13:57 ?        00:00:00 /opt/bin/flanneld --ip-masq --kube-subnet-mgr
root      9640  9619  0 13:51 ?        00:00:00 /bin/sh -c set -e -x; cp -f /etc/kube-flannel/cni-conf.json /etc/cni/net.d/10-flannel.conf; while true; do sleep 3600; done

$ cat /etc/cni/net.d/10-flannel.conf
{
  "name": "cbr0",
  "type": "flannel",
  "delegate": {
    "isDefaultGateway": true
  }
}
```

## kubeadm,kubelet,kubectl

安装

```
yum install -y kubelet kubeadm kubectl --disableexcludes=kubernetes
systemctl enable kubelet && systemctl start kubelet
```

卸载

```
yum remove kubelet 
yum remove kubeadm 
yum remove kubectl
systemctl enable kubelet && systemctl start kubelet
```

## 关闭管理机swap

```
swapoff -a
```

## kusphere

卸载python

```
强制删除已安装python及其关联
rpm -qa|grep python|xargs rpm -ev --allmatches --nodeps
删除残余文件
whereis python|xargs rm -frv
```

安装python

```
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-2.7.5-88.el7.x86_64.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-libs-2.7.5-88.el7.x86_64.rpm
wget https://rpmfind.net/linux/centos/7.7.1908/os/x86_64/Packages/rpm-4.11.3-40.el7.x86_64.rpm
wget https://rpmfind.net/linux/centos/7.7.1908/os/x86_64/Packages/rpm-python-4.11.3-40.el7.x86_64.rpm
wget http://buildlogs-seed.centos.org/c7.1804.00.x86_64/yum/20180413125614/3.4.3-158.el7.centos.x86_64/yum-3.4.3-158.el7.centos.noarch.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-iniparse-0.4-9.el7.noarch.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-urlgrabber-3.10-10.el7.noarch.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/python-pycurl-7.19.0-19.el7.x86_64.rpm
wget https://buildlogs.centos.org/c7.1804.00.x86_64/rpm/20180411035226/4.11.3-32.el7.x86_64/rpm-4.11.3-32.el7.x86_64.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/rpm-4.11.3-43.el7.x86_64.rpm
wget http://mirror.centos.org/centos/7/os/x86_64/Packages/yum-metadata-parser-1.1.4-10.el7.x86_64.rpm

rpm -Uvh --nodeps --replacepkgs --force yum-metadata-parser-1.1.4-10.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force rpm-4.11.3-43.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force rpm-4.11.3-32.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force python-2.7.5-88.el7.x86_64.rpm 
rpm -Uvh --nodeps --replacepkgs --force python-libs-2.7.5-88.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force python-iniparse-0.4-9.el7.noarch.rpm
rpm -Uvh --nodeps --replacepkgs --force python-urlgrabber-3.10-10.el7.noarch.rpm
rpm -Uvh --nodeps --replacepkgs --force python-pycurl-7.19.0-19.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force rpm-4.11.3-40.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force rpm-python-4.11.3-40.el7.x86_64.rpm
rpm -Uvh --nodeps --replacepkgs --force yum-3.4.3-158.el7.centos.noarch.rpm
```

如果新系统尚未安装工具pip，可通过以下三步来快速完成pip的安装

```
yum -y install epel-release
yum install python-pip
pip install --upgrade pip
```

 

安装ansible

```
yum -y install epel-release
yum -y install ansible
```

卸载docker

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

安装docker

```
sudo yum install docker-ce-18.09.0-3.el7 docker-ce-cli-18.09.0-3.el7 containerd.io
systemctl start docker
systemctl enable docker
docker -v
```

```
sudo journalctl -r -u docker
```

Helm

Helm is not available

```

```

cd /home/data/setup/

ll

cd kubesphere



cd scripts