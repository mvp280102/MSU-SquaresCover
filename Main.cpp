#define CURRENT
#define RANGE

#include "Tester.h"


int main()
{
	Tester tester(TestData{10, 100, 10, 100000});

	#ifdef CURRENT

	tester.test_current_data(true);
	tester.results_current_data();

	#endif

	#ifdef RANGE

	tester.test_range_data(1000000, 50000, true);
	tester.csv_range_data("diagram.csv");

	#endif

	return 0;
}

#undef CURRENT
#undef RANGE
