# vue2

## vue-router的nginx伪静态

```
server {
    // 域名
    server_name www.wddsss.com;
    // 项目入口文件目录地址 保证有权限
    root /www/project/blog/dist;

    index index.php index.html;

    // 配置伪静态
    location / {
  	try_files $uri $uri/ /index.html;
    }
}
```

