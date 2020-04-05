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



### 使用指针

```c
*pointerA
```



### 定义多个指针

```c
int *p,q; //p是指针，q是变量
int* p,q; //p是指针，q是变量

```



## 取址符

取址运算符 &

```c
int intA;
&intA
```

## 取值符

取值运算符*

```c
*pointerA;
```

## 空指针

```c
int * pointerIntA = NULL; 
```

## 指针的运算

### 自增

### 自减

```c
int intA;
int * pointerIntA = &intA;
pointerIntA++;
pointerIntA--;
```

### 比较

```c
int intA,intB;
int * pointerIntA = &intA;
int * pointerIntB = &intB;
if(pointerIntA > pointerIntB)
{
    //code
}
```



## 使用场景，多个返回值 

### swap

```c
void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
```

