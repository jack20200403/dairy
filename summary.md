# 技能点

------

[TOC]

------

## 进度

- [ ] c语言
  - [ ] 开发工具
    - [ ] clion
    - [ ] devC++
    - [ ] visual studio
    - [ ] visual studio code
    - [ ] mingw
    - [ ] cgwin
    - [ ] gdb
  - [ ] 语法
    - [x] 数据类型
    - [x] 运算符
    - [x] 表达式
    - [x] 顺序结构，分支结构，循环结构
    - [ ] 数组
    - [ ] 函数
    - [ ] 指针
    - [ ] 预处理
    - [ ] 结构体，共用体
    - [ ] 文件操作
    - [ ] 位运算
- [ ] c++
  - [ ] 语法
    - [ ] 类，对象
    - [ ] 继承
    - [ ] 重载
    - [ ] 多态
    - [ ] 封装
    - [ ] 接口
    - [ ] 抽象
  - [ ] STL
    - [ ] 容器
      - [ ] vector
      - [ ] deque
      - [ ] list

      - [ ] set
      - [ ] map
    - [ ] 算法
    - [ ] 迭代器
- [ ] linux
- [ ] ace
- [ ] boost
- [ ] qt
- [ ] mfc

------

## c

## c++

### STL

#### 容器

##### vector

###### 定义

```c++
#include <vector>
using std::vector;
vector<int> vInts;
std::vector<int> vInts;
```

###### 增

```c++
c.push_back(elem);
c.insert(pos,elem);
c.insert(pos,num,elem);
c.insert(pos,num,beg,end);
```

###### 删

```c++
c.clear();
c.pop_back();
c.erase(pos);
c.erase(beg,end);
```

###### 改

```
c.assign(beg,end);
c.assign(n,elem);
```

###### 查

```c++
c.at(idx);
c.begin();
c.end();
c.front();
c.back();
c.size();
c.capacity();
c.empty();
```

遍历

```c++
for(auto iterator:c)
{
    cout<< *iterator << endl;
}
for(int intPointA = c.begin() ; intPointA!=c.end();intPointA++ )
{
    cout<< *intPointA << endl;
}
```



##### list

##### deque

##### set

##### map

#### 模板

#### 迭代器