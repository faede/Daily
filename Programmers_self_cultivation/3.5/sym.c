extern int ext;

int weak;
int strong = 1;
int test = 0;
__attribute__((weak)) weak2 = 2;

int main(){
	//int a = 1;//no vis
	return 0;
}
