#include "Interface.h"
#include "Tester.h"

int main()
{
	Tester tester(TestData{3, 15, 5, 5});
	//Tester tester(TestData{10, 100, 1000000, 10});

	tester.run_tests();
	tester.show_results();
	tester.write_details("out.txt");

	return 0;
}
