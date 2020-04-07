# binlog



```shell
mysqlbinlog 选项 /path/二进制日志.log文件
--start-datetime=根据开始时间查看二进制日志，时间格式YYYY-MM-DD hh:mm:ss
--stop-datetime=根据结束时间

-j, --start-position=#  根据开始位置
-stop-position=#  根据结束位置

--no-defaults  #用此参数解决客户端字符集错误
-v  #详细的查看日志，选项要放在文件的前面
--base64-output=decode-rows  #用base64查看，一般和-v搭配一起使用

提示 mysqlbinlog: unknown variable 'character-set-server=utf8'怎么解决
用mysqlbinlog --no-defaults mysql-bin.000004 命令打开

[root@centos7 ~]# mysqlbinlog -j 313 --stop-position 437 /data/mysql/log/mysql-bin.000006  #查看二进制文件从哪个位置开始从哪个位置结束
[root@centos7 ~]# mysqlbinlog --start-datetime="2017-11-10 21:04:14" /data/mysql/log/mysql-bin.000006  #查看二进制文件从哪个时间开始
```





