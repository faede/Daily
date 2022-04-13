
int main(){
	int a = 2;
	int b = 1;
	if(a < 3){
		b = 3;
	}else{
		b = 5;
	}
	for(int i = 0; i < 1000; i++){
		b++;
	}
	int c = 2;
	int d = b + c;
	return d;
}
