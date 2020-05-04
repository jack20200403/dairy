# git

## clone

```
git clone --branch <tag> <repo>
```

```
git clone --branch 2020.5.1.SNAPSHOT http://103.232.84.206:82/tg/com-tg-k8s.git
S2iRJY7mqzQBTuPD
```

## Git fetch commands and options

```
git fetch <remote>
```

Fetch all of the branches from the repository. This also downloads all of the required commits and files from the other repository.

```
git fetch <remote> <branch>
git fetch  http://103.232.84.206:82/tg/com-tg-k8s.git origin/2020.5.1.SNAPSHOT
```

Same as the above command, but only fetch the specified branch.

```
git fetch --all
```

## 更新代码 

```
git pull origin
git reset --hard origin/master
```

## 切换分支

```
git checkout branch -b 2020.5.1.SNAPSHOT orgin/2020.5.1.SNAPSHOT
```

## 回退版本

```
git reset --hard commit_id 
git push origin HEAD --force
```

