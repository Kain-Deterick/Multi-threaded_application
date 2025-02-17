#include "../headers/working_with_buffer.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	working_with_buffer ob;

	std::thread t1(&working_with_buffer::processString, &ob);
	std::thread t2(&working_with_buffer::processData, &ob);

	t1.join();
	t2.join();

	return 0;
}