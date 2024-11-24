
// 声明全局变量c
extern int c;

// static 限制作用于，仅在本文件中调用
/*static*/ int add(int a, int b)
{
	return (a + b) * c;
}

