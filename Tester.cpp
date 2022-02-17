#include "Tester.h"


/*
 * Добавляет результаты решения текущей задачи к результатам тестов.
 */
void Tester::save_results(TestResultsExtended &test_results, TaskResults &task_results)
{
	test_results.average_total_time += task_results.total_time;
	test_results.average_step_time += task_results.step_time;
	test_results.average_points += task_results.points.size();
	test_results.average_steps += task_results.steps;
	test_results.average_error += task_results.error;
	test_results.task_results.push_back(task_results);
}


/*
 * Вычисляет средние значения для результатов тестов.
 */
void Tester::conclude_average(TestResultsExtended &test_results) const
{
	test_results.average_total_time /= test_data.tests_amount;
	test_results.average_step_time /= test_data.tests_amount;
	test_results.average_steps /= test_data.tests_amount;
	test_results.average_error /= test_data.tests_amount;
	test_results.average_points /= test_data.tests_amount;
}


/*
 * Теоретическая оценка вычислительной сложности простого алгоритма - O(N).
 * Возвращает значение указанной функции теоретической оценки на данном количестве квадратов.
 */
inline double Tester::complexity_grade_simple(unsigned int squares_amount)
{
	return (double)(squares_amount);
}


/*
 * Теоретическая оценка вычислительной сложности жадного алгоритма - O(N*log2(N)).
 * Возвращает значение указанной функции теоретической оценки на данном количестве квадратов.
 */
inline double Tester::complexity_grade_greedy(unsigned int squares_amount)
{
	return (double)squares_amount * log2((double)squares_amount);
}


/*
 * Запускает решение задачи простым и обоими жадными алгоритмами на одинаковых
 * случайно сгенерированных по текущему критерию тестовых данных.
 */
void Tester::test_current_data(bool output)
{
	TaskResults res;
	vector<Square> squares;

	random_device rd;
	mt19937 mersenne(rd());

	results.first.squares_amount = results.second.first.squares_amount = results.second.second.squares_amount = test_data.squares_amount;

	for (int i = 0; i < test_data.tests_amount; ++i)
	{
		if (output)
			cout << "Running algorithms on test " << i + 1 << ":\n";

		squares.reserve(test_data.squares_amount);

		for (int j = 0; j < test_data.squares_amount; ++j)
			squares.push_back(Square{false, {static_cast<double>(mersenne() % (test_data.area_range - test_data.side_length)), static_cast<double>(mersenne() % (test_data.area_range - test_data.side_length))}});

		solver = new Solver(TaskData{test_data.error_conclude, test_data.area_range, test_data.side_length, squares});

		if (output)
			cout << "Simple algorithm...\n";

		res = solver->cover_simple();
		save_results(results.first, res);

		if (output)
			cout << "Elementary greedy algorithm...\n";

		res = solver->cover_greedy_elementary();
		save_results(results.second.first, res);

		if (output)
			cout << "Improved greedy algorithm...\n";

		res = solver->cover_greedy_improved();
		save_results(results.second.second, res);

		if (output)
			cout << endl;

		squares.clear();
		delete solver;
	}

	conclude_average(results.first);
	conclude_average(results.second.first);
	conclude_average(results.second.second);
}


/*
 * Выводит на экран сводную таблицу по всем тестам для трех
 * алгоритмов, а также средние значения по полученным данным.
 */
void Tester::results_current_data()
{
	cout.setf(ios::left);

	cout << DIVIDER
	     << "| "
		 << setw(COMMON_TITLE_WIDTH) << "TEST DATA" << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Tests amount: "
	     << setw(CELL_DATA_WIDTH * 3) << test_data.tests_amount << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Area range: "
	     << setw(CELL_DATA_WIDTH * 3) << test_data.area_range << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Squares amount: "
	     << setw(CELL_DATA_WIDTH * 3) << test_data.squares_amount << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Side length: "
	     << setw(CELL_DATA_WIDTH * 3) << test_data.side_length << "|\n";

	cout << DIVIDER
		 << endl;

	cout << DIVIDER
		 << "| "
		 << setw(COMMON_TITLE_WIDTH) << "TEST RESULTS" << "|\n"
	     << "| "
	     << setw(COMMON_LABEL_WIDTH) << "ALGORITHM TYPE:"
	     << setw(CELL_DATA_WIDTH) << "SIMPLE"
	     << setw(CELL_DATA_WIDTH) << "GREEDY ELEM."
		 << setw(CELL_DATA_WIDTH) << "GREEDY IMP."
		 << "|\n";

	for (int i = 0; i < test_data.tests_amount; ++i)
	{
		cout << DIVIDER
			 << "| Test " << setw(2) << right << i + 1 << ":  " << left;

		cout << setw(CELL_TITLE_WIDTH) << "Total time:"
		     << setw(CELL_DATA_WIDTH) << results.first.task_results.at(i).total_time
		     << setw(CELL_DATA_WIDTH) << results.second.first.task_results.at(i).total_time
			 << setw(CELL_DATA_WIDTH) << results.second.second.task_results.at(i).total_time << "|\n";

		cout << "|\t    "
		     << setw(CELL_TITLE_WIDTH) << "Time for step:"
		     << setw(CELL_DATA_WIDTH) << results.first.task_results.at(i).step_time
		     << setw(CELL_DATA_WIDTH) << results.second.first.task_results.at(i).step_time
			 << setw(CELL_DATA_WIDTH) << results.second.second.task_results.at(i).step_time<< "|\n";

		cout << "|\t    "
		     << setw(CELL_TITLE_WIDTH) << "Steps amount:"
		     << setw(CELL_DATA_WIDTH) << results.first.task_results.at(i).steps
		     << setw(CELL_DATA_WIDTH) << results.second.first.task_results.at(i).steps
			 << setw(CELL_DATA_WIDTH) << results.second.second.task_results.at(i).steps << "|\n";

		if (test_data.error_conclude)
			cout << "|\t    "
			     << setw(CELL_TITLE_WIDTH) << "Error:"
			     << setw(CELL_DATA_WIDTH) << results.first.task_results.at(i).error
			     << setw(CELL_DATA_WIDTH) << results.second.first.task_results.at(i).error
				 << setw(CELL_DATA_WIDTH) << results.second.second.task_results.at(i).error << "|\n";

		cout << "|\t    "
		     << setw(CELL_TITLE_WIDTH) << "Points amount: "
		     << setw(CELL_DATA_WIDTH) << results.first.task_results.at(i).points.size()
		     << setw(CELL_DATA_WIDTH) << results.second.first.task_results.at(i).points.size()
			 << setw(CELL_DATA_WIDTH) << results.second.second.task_results.at(i).points.size() << "|\n";
	}

	cout << DIVIDER
		 << endl;

	cout << DIVIDER
	     << "| "
	     << setw(COMMON_TITLE_WIDTH) << "AVERAGE VALUES" << "|\n"
		 << "| "
		 << setw(COMMON_LABEL_WIDTH) << "ALGORITHM TYPE:"
		 << setw(CELL_DATA_WIDTH) << "SIMPLE"
		 << setw(CELL_DATA_WIDTH) << "GREEDY ELEM."
		 << setw(CELL_DATA_WIDTH) << "GREEDY IMP."
		 << "|\n";

	cout << DIVIDER
	     << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average total time:"
	     << setw(CELL_DATA_WIDTH) << results.first.average_total_time
	     << setw(CELL_DATA_WIDTH) << results.second.first.average_total_time
		 << setw(CELL_DATA_WIDTH) << results.second.second.average_total_time << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average time for step:"
	     << setw(CELL_DATA_WIDTH) << results.first.average_step_time
	     << setw(CELL_DATA_WIDTH) << results.second.first.average_step_time
		 << setw(CELL_DATA_WIDTH) << results.second.second.average_step_time << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average steps amount:"
	     << setw(CELL_DATA_WIDTH) << results.first.average_steps
	     << setw(CELL_DATA_WIDTH) << results.second.first.average_steps
		 << setw(CELL_DATA_WIDTH) << results.second.second.average_steps << "|\n";

	if (test_data.error_conclude)
		cout << "| "
		     << setw(COMMON_LABEL_WIDTH) << "Average error:"
		     << setw(CELL_DATA_WIDTH) << results.first.average_error
		     << setw(CELL_DATA_WIDTH) << results.second.first.average_error
			 << setw(CELL_DATA_WIDTH) << results.second.second.average_error << "|\n";

	cout << "| "
	     << setw(COMMON_LABEL_WIDTH) << "Average points amount:"
	     << setw(CELL_DATA_WIDTH) << results.first.average_points
	     << setw(CELL_DATA_WIDTH) << results.second.first.average_points
		 << setw(CELL_DATA_WIDTH) << results.second.second.average_points << "|\n";

	cout << DIVIDER
		 << endl;
}


/*
 * Запускает решение задачи простым и обоими жадными алгоритмами
 * на наборе тестовых данных с возрастающим количеством квадратов.
 */
void Tester::test_range_data(unsigned int high_squares_amount, unsigned int step, bool output)
{
	while (test_data.squares_amount <= high_squares_amount)
	{
		if (output)
			cout << "Running algorithms on " << test_data.tests_amount << " tests with " << test_data.squares_amount << " squares...\n"
				 << endl;

		test_current_data(true);
		results_data.emplace_back(results);

		test_data.squares_amount += step;
	}
}


/*
 * Выводит в csv-файл таблицу со средними значениями по тестам алгоритмов,
 * запущенных в определенном диапазоне критерия тестовых данных.
 */
void Tester::csv_range_data(const char *filename) const
{
	ofstream out(filename);

	if (!out.fail())
	{
		out << "Range, Side length, Squares amount, "
			<< "Total time (SIMPLE), Total time (GREEDY ELEM.), Total time (GREEDY IMP.), "
			<< "Steps amount (SIMPLE), Steps amount (GREEDY ELEM.), Steps amount (GREEDY IMP.), "
			<< "Time/step (SIMPLE), Time/step (GREEDY ELEM.), Time/step (GREEDY IMP.), "
			<< "Complexity (SIMPLE), Complexity (GREEDY ELEM.), Complexity (GREEDY IMP.)"
			<< endl;

		for (const auto & item : results_data)
		{
			out << test_data.area_range << ","
				<< test_data.side_length << ","
			    << item.first.squares_amount << ","
			    << item.first.average_total_time << ","
			    << item.second.first.average_total_time << ","
				<< item.second.second.average_total_time << ","
			    << item.first.average_steps << ","
			    << item.second.first.average_steps << ","
				<< item.second.second.average_steps << ","
			    << item.first.average_step_time << ","
			    << item.second.first.average_step_time << ","
				<< item.second.second.average_step_time << ","
				<< item.first.average_total_time / complexity_grade_simple(item.first.squares_amount) << ","
				<< item.second.first.average_total_time / complexity_grade_greedy(item.second.first.squares_amount) << ","
				<< item.second.second.average_total_time / complexity_grade_greedy(item.second.second.squares_amount)
				<< endl;
		}
	}
	else
	{
		cout << "Output file opening error!\n"
			 << "Aborting application!\n";

		exit(1);
	}
}