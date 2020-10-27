struct func; // 定义在清单2.1中
void f()
{
	int some_local_state = 0;
	func my_func(some_local_state);
	std::thread t(my_func);
	try
	{
		do_something_in_current_thread();
	}
	catch (...)
	{
		t.join(); // 1
		throw;
	}
	t.join(); // 2
}