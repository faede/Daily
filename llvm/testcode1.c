void func(){
    int i;
    char C[2];
    char A[10];
    for(int i = 0; i != 10; i++){
        ((short *)C)[0] = A[i];
        C[1] = A[9-i];
    }
}