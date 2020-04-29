# java

------

[TOC]

------

## problem

### SLF4J: Failed to load class “org.slf4j.impl.StaticLoggerBinder”

```pom.xml
<dependency>
    <groupId>org.slf4j</groupId>
    <artifactId>slf4j-simple</artifactId>
    <version>1.7.21</version>
</dependency>
```



### 查看端口占用的进程

```sh
lsof -i :端口号
```

### At least one JAR was scanned for TLDs yet contained no TLDs. 

```

```

### More than one fragment with the name [spring_web] was found. This is not legal with relative ordering.

```
add <absolute-ordering /> tag to your web.xml just under the <display-name> tag. should work.
```

jar启动

start.sh

```sh
#!/bin/bash
# 启动脚本，nohup方式后台运行jar包，其中参数需要根据实际情况调整
# 参数说明如下
# -Xms128m    JVM初始分配的堆内存
# -Xmx1024m    JVM最大允许分配的堆内存
# /root/java/api-1.0.0.jar    jar文件全路径
# --spring.profiles.active=prod    运行application-prod.properties
# logs/api.out    实时输出控制台信息到指定文件
nohup java -jar -Xms128m -Xmx1024m /root/java/api-1.0.0.jar --spring.profiles.active=prod > logs/api.out &
```

stop.sh

```sh
#!/bin/bash
# 停止脚本，其中 api-1.0.0.jar 需要替换成实际文件名，而且尽量确保名字唯一性，防止错杀
apiID=$(ps -ef |grep 'api-1.0.0.jar'|grep -v 'grep'| awk '{print $2}')
# run
# 判断进程是否存在
if test $apiID ;then
    # 杀死进程
    kill -9 $apiID
    echo "[SUCCESS] 进程已杀死"
else
    # 提示不进程不存在
    echo "[ERROR] 进程不存在"
fi
```

restart.sh

```sh
#!/bin/bash
# 重启脚本，实际上就是结合了前面2个脚本
# 停止
apiID=$(ps -ef |grep 'api-1.0.0.jar'|grep -v 'grep'| awk '{print $2}')
# run
# 判断进程是否存在
if test $apiID ;then
    # 杀死进程
    kill -9 $apiID
    echo "[SUCCESS] 进程已杀死"
else
    # 提示不进程不存在
    echo "[ERROR] 进程不存在"
fi
# 休眠5秒
sleep 5
# 启动
nohup java -jar -Xms128m -Xmx1024m /root/java/api-1.0.0.jar --spring.profiles.active=prod > logs/api.out &
echo "process is started"
```

