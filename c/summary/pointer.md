# 指针

指针是地址

------



[TOC]



------



## 定义指针

```c
int intA;
int * pointerA;
pointerA = &intA;
```



## 使用指针

```c
*pointerA
```



## 定义多个指针

```c
int *p,q; //p是指针，q是变量
int* p,q; //p是指针，q是变量

```



## 取地址运算符

取址符 &

```c
int intA;
&intA
```



## 使用场景，带返回值的 

### swap

```c
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
```

