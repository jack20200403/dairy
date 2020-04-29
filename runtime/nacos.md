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