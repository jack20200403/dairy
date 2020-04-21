# nodejs

------

[TOC]

------

## 安装nodjs

```sh
yum install epel-release
yum install nodejs
yum install npm
```



## bug

### FATAL ERROR: CALL_AND_RETRY_LAST Allocation failed - JavaScript heap out of memory

```sh
set NODE_OPTIONS=--max_old_space_size=1000000
export NODE_OPTIONS=--max_old_space_size=1000000
# 升级nodejs
npm install -g n
n stable
```

升级nodejs到12

```sh
npm install -g n
n stable
```

### 切换版本失败

卸载重装

```sh
which node
/usr/local/bin/node
```

```sh
vim ~/.bash_profile
export N_PREFIX=/usr/local #node实际安装位置
export PATH=$N_PREFIX/bin:$PATH
```

```sh
source ~/.bash_profile
```



### Invalid Host header

在 `webpack-dev-server` 的配置中添加

```webpack.config.js
 devServer: {
    disableHostCheck: true,
  },
```

`webpack-dev-server` 的配置是在 `webpack.config.js` 中的 `devServer` 字段。

## 卸载

```sh
 sudo npm uninstall npm -g
 yum remove nodejs npm -y
```





