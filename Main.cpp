#include "Interface.h"
#include "Tester.h"

int main()
{
	Tester tester(TestData{10, 100, 10000000, 5});

	tester.run_tests();
	tester.show_results();

	return 0;
}
