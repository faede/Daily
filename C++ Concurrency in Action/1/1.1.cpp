#include <iostream>
#include <thread> //①
void hello() //②
{
    std::cout << "Hello Concurrent World\n";
}
int main()
{
    std::thread t(hello); //③
    t.join(); //④
}