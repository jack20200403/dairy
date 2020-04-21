# mysql

------

[TOC]

------

## export

```
mysqldump -u root -p lottery > cp.sql 
```

## import

```
scp -v root@47.244.134.253:/data/backup/database/cp.sql.tar.gz /home/www/backup/database/cp.sql.tar.gz
```

## 表名忽略大小写

```my.cnf
lower_case_table_names=1 #忽略大小写
```

