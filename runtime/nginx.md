# nginx

## upstream

```
upstream backend {
    server backend1.example.com       weight=5;
    server backend2.example.com:8080;
    server unix:/tmp/backend3;

    server backup1.example.com:8080   backup;
    server backup2.example.com:8080   backup;
}

server {
    location / {
        proxy_pass http://backend;
    }
    
        
    location  ^~ /wmxiangmumingcinge/ {
        proxy_pass    http://xcx.xxxxxxxxx.cn/:18120/;
        add_header 'Access-Control-Allow-Origin' '*';
        add_header 'Access-Control-Allow-Credentials' 'true';
        proxy_set_header   Host    $host;  
        proxy_set_header   X-Real-IP   $remote_addr;   
        proxy_set_header   X-Forwarded-For $proxy_add_x_forwarded_for;
        proxy_connect_timeout      300; #nginx跟后端服务器连接超时时间(代理连接超时)
        proxy_send_timeout         300; #后端服务器数据回传时间(代理发送超时)
        proxy_read_timeout         300; #连接成功后，后端服务器响应时间(代理接收超时)
    }
    
}
```

403

```nginx.conf
user  root;
```

## nginx windows

http://nginx.org/en/docs/windows.html

```
cd c:\
unzip nginx-1.17.10.zip
cd nginx-1.17.10
start nginx
```

```
tasklist /fi "imagename eq nginx.exe"
```

```
nginx -s stop	fast shutdown
nginx -s quit	graceful shutdown
nginx -s reload	changing configuration, starting new worker processes with a new configuration, graceful shutdown of old worker processes
nginx -s reopen	re-opening log files
```

## 反向代理域名

```
使用域名代理的时候，在最后面记得需要加上''/'',否则会出现404的问题
使用域名代理的时候，必须携带上对的端口号，并且不能使用80端口
```

