
#include <stdlib.h>
#include <windows.h>

#include <thread>
#include <iostream>

using namespace std;

void myFunc() {
	cout << "hello world1 ..." << endl;
	cout << "hello world2 ..." << endl;
	cout << "hello world3 ..." << endl;
	cout << "hello world4 ..." << endl;
	cout << "hello world5 ..." << endl;
	cout << "hello world6 ..." << endl;
	cout << "hello world7 ..." << endl;
}

int main() {

	thread myThread(myFunc);

	cout << "i am main func1 ..." << endl;
	cout << "i am main func2 ..." << endl;
	cout << "i am main func3 ..." << endl;
	cout << "i am main func4 ..." << endl;
	cout << "i am main func5 ..." << endl;
	cout << "i am main func6 ..." << endl;
	cout << "i am main func7 ..." << endl;
	cout << "i am main func8 ..." << endl;



	myThread.join();

	system("pause");

	Sleep(2000);
	return 0;
}