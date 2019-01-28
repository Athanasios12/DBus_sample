#include <memory>
#include <vector>

void memWarning()
{
	int *ptr = nullptr;
	{
		auto uptr = std::make_unique<int>(int{10});
		ptr = uptr.get();
	}
	*ptr = 20;	
}

//maybe warning
typedef std::vector<char*> cvec;

char *cStr = "Hello";

int main(void)
{
	memWarning();
	cvec v;
	v.push_back(cStr);
	goto hello;
	hello:
	return 0;
}
