# jenkins

##  安装jenkins

[https://jenkins.io/zh/doc/book/installing/#%E5%AE%89%E8%A3%85docker](https://jenkins.io/zh/doc/book/installing/#安装docker)

```sh
docker run \
-u root \
--name=tg_jenkins \
--restart=always \
-d \
-p 10005:8080 \
-p 10006:50000 \
-v /data/setup/jenkins_home:/var/jenkins_home \
-e JAVA_OPTS=-Duser.timezone=Asia/Shanghai \
-v /var/run/docker.sock:/var/run/docker.sock \
jenkins/jenkins:lts
```

安装插件

```sh
nodejs
npm
jdk8
maven
gitlab
Gitlab Authentication
GitLab Branch Source
Gitlab Merge Request Builder
Violation Comments to GitLab
Gitlab API
Git Parameter
Maven Integration plugin
Maven Artifact ChoiceListProvider (Nexus)
Maven Repository Scheduled Cleanup
Maven Deployment Linker
Publish Over SSH

Docker API
Docker	
docker-build-step	
Image Tag Parameter	
Docker API
```

### [Jenkins installation on tomcat giving hudson.util.NoTempDir: java.io.IOException: No such file or directory](https://stackoverflow.com/questions/41679543/jenkins-installation-on-tomcat-giving-hudson-util-notempdir-java-io-ioexception)

```sh

```

### [Maven fails to parse POMs at jenkins](https://stackoverflow.com/questions/22449689/maven-fails-to-parse-poms-at-jenkins)

```

```

配置maven

```sh
wget http://mirror.rise.ph/apache/maven/maven-3/3.6.3/binaries/apache-maven-3.6.3-bin.tar.gz
```

配置远程部署

```
登录jenkins-系统管理-系统设置-Publish Over SSH,配置远程服务器;
说明:
Source files的目录是基于当前job的目录(可以从jenkins的安装目录下找到)：例如当前job名称为people-info-server，则对于root用户，Source files中的目录是相对于/var/jenkins_home/workspace/people-info-server目录下的，因此，如果我们要发送people-info-server下的xx项目的jar包，这里需要填写：xx/target/xx-0.0.1.SNAPSHOT.jar
Remove prefix：表示需要移除的目录，比如这里填写xx/target，则表示发布时，只把xx-0.0.1.SNAPSHOT.jar发布到远程linux，而不包含xx/target目录结构
Remote directory：表示需要把编译好的war包发布到远程linux的哪个目录下
Exec command：需要执行的shell命令，shell命令在远程linux服务器上.
```

```sh
source /etc/profile
echo "hello xx-0.0.1.SNAPSHOT.jar"
DAY=`date +%Y-%m-%d`
pid=`ps -ef|xx|grep -v grep|awk '{print $2}'`
if [ -n "$pid" ]
then
echo 'The pid: server' $pid ' will be killed....'
kill -9 $pid
echo 'The pid: server' $pid ' will be start'
nohup java -jar /data/jekins/xx/xx-0.0.1.SNAPSHOT.jar >  /dev/null & 
else
echo 'The pid: server' $pid ' not exist , will be start'
nohup java -jar /data/jekins/xx/xx-0.0.1.SNAPSHOT.jar >  /dev/null &
fi
echo 'The pid: server' $pid ' started'
```



## pipeline

Java

Jenkinsfile (Declarative Pipeline)

```groovy
pipeline {
    agent { docker 'maven:3.3.3' }
    stages {
        stage('build') {
            steps {
                sh 'mvn --version'
            }
        }
    }
}
```

[Toggle Scripted Pipeline](https://www.jenkins.io/zh/doc/pipeline/tour/hello-world/#) *(Advanced)*

Node.js / JavaScript

Jenkinsfile (Declarative Pipeline)

```groovy
pipeline {
    agent { docker 'node:6.3' }
    stages {
        stage('build') {
            steps {
                sh 'npm --version'
            }
        }
    }
}
```

[Toggle Scripted Pipeline](https://www.jenkins.io/zh/doc/pipeline/tour/hello-world/#) *(Advanced)*

Ruby

Jenkinsfile (Declarative Pipeline)

```groovy
pipeline {
    agent { docker 'ruby' }
    stages {
        stage('build') {
            steps {
                sh 'ruby --version'
            }
        }
    }
}
```

[Toggle Scripted Pipeline](https://www.jenkins.io/zh/doc/pipeline/tour/hello-world/#) *(Advanced)*

Python

Jenkinsfile (Declarative Pipeline)

```groovy
pipeline {
    agent { docker 'python:3.5.1' }
    stages {
        stage('build') {
            steps {
                sh 'python --version'
            }
        }
    }
}
```

[Toggle Scripted Pipeline](https://www.jenkins.io/zh/doc/pipeline/tour/hello-world/#) *(Advanced)*

PHP

Jenkinsfile (Declarative Pipeline)

```groovy
pipeline {
    agent { docker 'php' }
    stages {
        stage('build') {
            steps {
                sh 'php --version'
            }
        }
    }
}
```

## bug

docker not found

```
https://www.qikqiak.com/k8s-book/docs/36.Jenkins%20Slave.html
```

## docker

```
mvn clean package docker:build  -DpushImage
```

