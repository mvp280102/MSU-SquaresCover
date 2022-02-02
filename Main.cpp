#define CURRENT
//#define RANGE

#ifdef CURRENT
#include "Tester.h"
#endif

#ifdef RANGE
#include "Tester.h"
#endif

int main()
{
	Tester tester(TestData{10, 100, 10, 100000});

	#ifdef CURRENT

	tester.test_current_data(true);
	tester.results_current_data();
	//tester.details_current_data("details.txt");

	#endif

	#ifdef RANGE

	tester.test_range_data(1000000, 50000, true);
	tester.csv_range_data("diagram.csv");

	#endif

	return 0;
}

#undef CURRENT
#undef RANGE

/*
 * Сделать разбиение на клетки для второго алгоритма.
 * Формирование клеток учитывать при подсчете времени его работы.
 */