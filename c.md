# 

进度

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

# C语言

## 指针

指针是地址

定义指针

```c
int intA;
int * pointerA;
pointerA = &intA;
```



使用指针

```c
*pointerA
```



定义多个指针

```c
int *p,q; //p是指针，q是变量
int* p,q; //p是指针，q是变量

```

取址符

取址运算符 &

```c
int intA;
&intA
```

取值符

取值运算符*

```c
*pointerA;
```

空指针

```c
int * pointerIntA = NULL; 
```

指针的运算

自增

自减

```c
int intA;
int * pointerIntA = &intA;
pointerIntA++;
pointerIntA--;
```

比较

```c
int intA,intB;
int * pointerIntA = &intA;
int * pointerIntB = &intB;
if(pointerIntA > pointerIntB)
{
    //code
}
```

使用场景，多个返回值 

swap

```c
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
```

## 位运算

```
&	按位与
|	按位或
^	按位异或 XOR
~	按位取反
>>	右移
<<	左移
```

## 预处理

```
#include <stdio>
#define PI 3.1415926;
```

# c++

# STL

## 容器

### vector

定义

```c++
#include <vector>
using std::vector;
vector<int> vInts;
std::vector<int> vInts;
```

增

```c++
c.push_back(elem);
c.insert(pos,elem);
c.insert(pos,num,elem);
c.insert(pos,num,beg,end);
```

删

```c++
c.clear();
c.pop_back();
c.erase(pos);
c.erase(beg,end);
```

改

```
c.assign(beg,end);
c.assign(n,elem);
```

查

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



### list

### deque

### set

### map

## 模板

## 迭代器

# QT

LNK1158

```
pleasemake sure, that the WindowsKit bin folder is part of your Build Environment
```

![0_1526642474311_2650c212-8bf8-4133-8c63-8e24436325f6-image.png](https://ddgobkiprc33d.cloudfront.net/3f7cdac6-e900-47e8-be4e-a9a1338d0d4c.png)