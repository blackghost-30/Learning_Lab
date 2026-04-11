
char heap_buf[1024];
int pos = 0;
int g_cnt = 0;

void *my_malloc(int size)
{
	int old_pos = pos;
	pos += size;
	return &heap_buf[old_pos];
}

void my_free(void *buf)
{
	/* err */
}

int b_func(volatile int a)
{
	a += 2;
	return a;
}

int c_func(volatile int a)
{
	a += 3;
	return a;
}

void a_func(volatile int a)
{
	g_cnt = b_func(a);
	g_cnt = c_func(g_cnt);
}

int main(void)
{
	char ch = 65; // char ch = 'A';
	volatile int i = 99;
	char *buf = my_malloc(100);
	
	unsigned char uch = 200;
	
	for (i = 0; i < 26; i++)
		buf[i] = 'A' + i;
	
	a_func(i);
	
	return 0;
}

