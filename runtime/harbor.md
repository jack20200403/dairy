# harbor

## https

若推送镜像报以下错误:

Error response from daemon: Get https://192.168.100.xxx/v1/users/: http: server gave HTTP response to HTTPS client

原因为,docker默认使用的是https协议，而搭建的Harbor是http提供服务的，所以要配置可信任。PS：如果Harbor是https的就不会报该错误,https配置见最后。

方法1、修改docker配置文件：

```
# vim /usr/lib/systemd/system/docker.service

ExecStart=/usr/bin/dockerd --insecure-registry=192.168.100.127:8070
```

修改完毕后按安装步骤走一遍即可。

方法2、

```
# vim /etc/docker/daemon.json

{
 "registry-mirrors": ["http://xxx0.m.daocloud.io"]
 "insecure-registries":["192.168.100.127:8070"]
}    
```

配置完以后重启一下docker