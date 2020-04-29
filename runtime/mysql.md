# mysql

## export

```sh
mysqldump -u root -p lottery > cp.sql 
```

## import

```sh
scp -v root@47.244.134.253:/data/backup/database/cp.sql.tar.gz /home/www/backup/database/cp.sql.tar.gz

source /data/www/backup/database/20200429-0457-lottery.sql;
```

## 表名忽略大小写

```my.cnf
lower_case_table_names=1 #忽略大小写
```

## 查看表大小

```sql
SELECT table_name,table_rows FROM information_schema.tables  WHERE table_schema='lottery' ORDER BY table_rows DESC;
```

## 远程权限

```
create user `tom`@`%` identified by 'f27b08ce1d7f34cf';
ALTER USER `root`@`%` IDENTIFIED BY 'f27b08ce1d7f34cf';
// 修改权限 (注意这里用户名和密码替换成自己的)
 GRANT ALL PRIVILEGES ON *.* TO 'root'@'%' IDENTIFIED BY 'f27b08ce1d7f34cf' WITH GRANT OPTION;
 //更新缓存
 FLUSH PRIVILEGES;
```

