#include "Solver.h"


/*
 * Если точка принадлежит квадрату, возвращает true, иначе - false.
 */
bool Solver::belong(const Point &point, const Square &square)
{
	return ((point.x > square.corner.x) && (point.x < square.corner.x + data.side_length)) &&
			((point.y > square.corner.y) && (point.y < square.corner.y + data.side_length));
}


/*
 * Если квадраты пересекаются, возвращает указатель на
 * координаты середины их пересечения, иначе - nullptr.
 */
Point* Solver::middle(unsigned int first, unsigned int second)
{
	Segment x1{}, x2{}, y1{}, y2{};
	Point *req = nullptr;

	x1.begin = data.squares.at(first).corner.x;
	x1.end = x1.begin + data.side_length;

	y1.begin = data.squares.at(first).corner.y;
	y1.end = y1.begin + data.side_length;

	x2.begin = data.squares.at(second).corner.x;
	x2.end = x2.begin + data.side_length;

	y2.begin = data.squares.at(second).corner.y;
	y2.end = y2.begin + data.side_length;

	if (((x1.end > x2.begin) || (x2.end > x1.begin)) && ((y1.end > y2.begin) || (y2.end > y1.begin)))
	{
		req = new Point;

		req->x = (x1.end + x2.begin) / 2.0;
		req->y = (y1.end + y2.begin) / 2.0;
	}

	return req;
}


/*
 * Определяет, пересекаются ли отрезки и возвращает соответствующее значение.
 */
int Solver::intersection(const Segment &first, const Segment &second)
{
	if ((first.begin < second.begin) && (first.end > second.begin))
		return -1;
	else if ((first.begin < second.end) && (first.end > second.end))
		return 1;
	else if ((first.begin >= second.begin) && (first.end <= second.end))
		return 2;
	else
		return 0;
}


/*
 * Вычисляет суммарную ошибку для решения текущей задачи.
 */
unsigned long int Solver::error()
{
	unsigned long int result = 0;

	for (auto & square : data.squares)
	{
		unsigned long int current = 0;

		for (auto &point: results.points)
			if (belong(point, square))
				++current;

		if (current > 1)
			result += (current - 1);
	}

	return result;
}


/*
 * Решает задачу покрытия квадратов точками простым алгоритмом.
 * Возвращает указатель на структуру с результатами решения задачи.
 */
TaskResults& Solver::cover_simple()
{
	Point *req;

	clock_t start, stop;
	bool intersected = false;

	for (auto & square : data.squares)
		square.covered = false;

	results.steps = 0;
	results.points.clear();

	start = clock();

	for (int i = 0; i < data.squares.size(); ++i)
	{
		if (intersected)
		{
			intersected = false;
			continue;
		}

		for (int j = i + 1; j < data.squares.size(); ++j)
		{
			req = middle(i, j);

			if (++results.steps && !data.squares.at(i).covered && !data.squares.at(i).covered && (req != nullptr))
			{
				data.squares.at(i).covered = data.squares.at(j).covered = true;
				results.points.push_back(*req);

				intersected = true;
				break;
			}
		}
	}

	for (int i = 0; i < data.squares.size(); ++i)
		if (++results.steps && !data.squares.at(i).covered)
			results.points.push_back(*middle(i, i));

	stop = clock();

	results.total_time = (double)(stop - start) / CLOCKS_PER_SEC;
	results.step_time = results.total_time / (double)results.steps;
	results.error = data.error_conclude ? error() : 0;

	return results;
}


/*
 * Решает задачу покрытия квадратов точками жадным алгоритмом.
 * Возвращает указатель на структуру с результатами решения задачи.
 */
TaskResults& Solver::cover_greedy()
{
	Segment x_intersection{}, y_intersection{}, x_current{}, y_current{};
	Point point{};

	clock_t start, stop;
	int x_flag, y_flag;

	for (auto & square : data.squares)
		square.covered = false;

	results.steps = 0;
	results.points.clear();

	start = clock();

	for (int i = 0; i < data.squares.size(); ++i)
		if (!data.squares.at(i).covered)
		{
			x_intersection.begin = data.squares.at(i).corner.x;
			x_intersection.end = x_intersection.begin + data.side_length;

			y_intersection.begin = data.squares.at(i).corner.y;
			y_intersection.end = y_intersection.begin + data.side_length;

			for (int j = i + 1; j < data.squares.size(); ++j)
				if (++results.steps && !data.squares.at(j).covered)
				{
					x_current.begin = data.squares.at(j).corner.x;
					x_current.end = x_current.begin + data.side_length;

					y_current.begin = data.squares.at(j).corner.y;
					y_current.end = y_current.begin + data.side_length;

					x_flag = intersection(x_intersection, x_current);
					y_flag = intersection(y_intersection, y_current);

					if (x_flag && y_flag)
					{
						if (x_flag == -1) x_intersection.begin = x_current.begin;
						else if (x_flag == 1) x_intersection.end = x_current.end;

						if (y_flag == -1) y_intersection.begin = y_current.begin;
						else if (y_flag == 1) y_intersection.end = y_current.end;

						data.squares.at(j).covered = true;
					}
					else
						continue;
				}

			data.squares.at(i).covered = true;

			point.x = (x_intersection.begin + x_intersection.end) / 2.0;
			point.y = (y_intersection.begin + y_intersection.end) / 2.0;

			results.points.push_back(point);
		}

	stop = clock();

	results.total_time = (double)(stop - start) / CLOCKS_PER_SEC;
	results.step_time = results.total_time / (double)results.steps;
	results.error = data.error_conclude ? error() : 0;

	return results;
}
