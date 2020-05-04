# nacos

## k8s

- **Clone Project**

```shell
git clone https://github.com/nacos-group/nacos-k8s.git
```

- **Simple Start**

> If you want to start Nacos without NFS, but **emptyDirs will possibly result in a loss of data**. as follows:

```shell
cd nacos-k8s
chmod +x quick-startup.sh
./quick-startup.sh
```

- **Testing**

  - **Service registration**

  ```powershell
  curl -X PUT 'http://cluster-ip:8848/nacos/v1/ns/instance?serviceName=nacos.naming.serviceName&ip=20.18.7.10&port=8080'
  ```

  - **Service discovery**

  ```powershell
  curl -X GET 'http://cluster-ip:8848/nacos/v1/ns/instances?serviceName=nacos.naming.serviceName'
  ```

  - **Publish config**

  ```powershell
  curl -X POST "http://cluster-ip:8848/nacos/v1/cs/configs?dataId=nacos.cfg.dataId&group=test&content=helloWorld"
  ```

  - **Get config**

  ```powershell
  curl -X GET "http://cluster-ip:8848/nacos/v1/cs/configs?dataId=nacos.cfg.dataId&group=test"
  ```

## spring boot  转微服务

```
<dependency>
    <groupId>com.alibaba.cloud</groupId>
    <artifactId>spring-cloud-alibaba-dependencies</artifactId>
    <version>2.2.1.RELEASE</version>
    <type>pom</type>
    <scope>import</scope>
</dependency>

```

## ip

Nacos服务注册的IP

Nacos注册中心是: [https://github.com/alibaba/nacos](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Falibaba%2Fnacos)
 各个服务通过Nacos客户端将服务信息注册到Nacos上
 当Nacos服务注册的IP默认选择出问题时，可以通过查阅对应的客户端文档，来选择配置不同的网卡或者IP
 （`参考org.springframework.cloud.alibaba.nacos.NacosDiscoveryProperties的配置`）

解决办法

例如，使用了Spring cloud alibaba（[官方文档](https://links.jianshu.com/go?to=https%3A%2F%2Fgithub.com%2Falibaba%2Fspring-cloud-alibaba)）作为Nacos客户端，
 服务默认获取了内网IP 192.168.1.21,
 可以通过配置spring.cloud.inetutils.preferred-networks=10.34.12，使服务获取内网中前缀为10.34.12的IP

如何配置



```php
# 如果选择固定Ip注册可以配置
spring.cloud.nacos.discovery.ip = 10.2.11.11
spring.cloud.nacos.discovery.port = 9090

# 如果选择固定网卡配置项
spring.cloud.nacos.discovery.networkInterface = eth0

# 如果想更丰富的选择，可以使用spring cloud 的工具 InetUtils进行配置
# 具体说明可以自行检索: https://github.com/spring-cloud/spring-cloud-commons/blob/master/docs/src/main/asciidoc/spring-cloud-commons.adoc
spring.cloud.inetutils.default-hostname
spring.cloud.inetutils.default-ip-address
spring.cloud.inetutils.ignored-interfaces[0]=eth0   # 忽略网卡，eth0
spring.cloud.inetutils.ignored-interfaces=eth.*     # 忽略网卡，eth.*，正则表达式
spring.cloud.inetutils.preferred-networks=10.34.12  # 选择符合前缀的IP作为服务注册IP
spring.cloud.inetutils.timeout-seconds
spring.cloud.inetutils.use-only-site-local-interfaces
```

更多配置



```css
spring.cloud.nacos.discovery.server-addr  #Nacos Server 启动监听的ip地址和端口
spring.cloud.nacos.discovery.service  #给当前的服务命名
spring.cloud.nacos.discovery.weight  #取值范围 1 到 100，数值越大，权重越大
spring.cloud.nacos.discovery.network-interface #当IP未配置时，注册的IP为此网卡所对应的IP地址，如果此项也未配置，则默认取第一块网卡的地址
spring.cloud.nacos.discovery.ip  # 优先级最高
spring.cloud.nacos.discovery.port  # 默认情况下不用配置，会自动探测
spring.cloud.nacos.discovery.namespace # 常用场景之一是不同环境的注册的区分隔离，例如开发测试环境和生产环境的资源（如配置、服务）隔离等。

spring.cloud.nacos.discovery.access-key  # 当要上阿里云时，阿里云上面的一个云账号名
spring.cloud.nacos.discovery.secret-key # 当要上阿里云时，阿里云上面的一个云账号密码
spring.cloud.nacos.discovery.metadata    #使用Map格式配置，用户可以根据自己的需要自定义一些和服务相关的元数据信息
spring.cloud.nacos.discovery.log-name   # 日志文件名
spring.cloud.nacos.discovery.enpoint   # 地域的某个服务的入口域名，通过此域名可以动态地拿到服务端地址
ribbon.nacos.enabled  # 是否集成Ribbon 默认为true
```



作者：刘崎
链接：https://www.jianshu.com/p/64e1f7d50c6e
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。