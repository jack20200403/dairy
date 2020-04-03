# 指针

指针是地址

------



[TOC]



------

## 编写函数实现，计算字符串的长度。

```
int intStrLength(char * pointerA)
{
	int intStrLength = 0;
	while(*pointerA)
	{
		pointerA++;
		intStrLength++;
	}
	return intStrLength;
}
```

