#include "Solver.h"

/*
 * Если точка принадлежит квадрату, возвращает true, иначе - false.
 */
bool Solver::belong(Point point, Square square, unsigned int side_length)
{
	return ((point.x > square.corner.x) && (point.x < square.corner.x + side_length)) &&
			((point.y > square.corner.y) && (point.y < square.corner.y + side_length));
}


/*
 * Если квадраты с заданными номерами пересекаются, возвращает
 * координаты середины их пересечения, иначе {-1; -1}.
 */
Point* Solver::middle(unsigned int first, unsigned int second)
{
	Segment x1{}, x2{}, y1{}, y2{};                     // Проекции квадратов на координатные оси
	Point *req = nullptr;                               // Середина пересечения пары квадратов

	x1.begin = data.squares[first].corner.x;
	x1.end = x1.begin + data.side_length;

	y1.begin = data.squares[first].corner.y;
	y1.end = y1.begin + data.side_length;

	x2.begin = data.squares[second].corner.x;
	x2.end = x2.begin + data.side_length;

	y2.begin = data.squares[second].corner.y;
	y2.end = y2.begin + data.side_length;

	if  (((x1.end > x2.begin) || (x2.end > x1.begin)) && ((y1.end > y2.begin) || (y2.end > y1.begin)))
	{
		req = new Point;

		req->x = (x1.end + x2.begin) / 2.0;
		req->y = (y1.end + y2.begin) / 2.0;
	}

	return req;
}


/*
 * Решает задачу покрытия квадратов точками.
 * После выполнения функции в векторе points хранятся координаты точек покрытия.
 * В зависимости от переданного параметра улучшает точность или скорость работы.
 * Возвращает количество шагов, за которое была решена задача.
 */
unsigned int Solver::cover(vector<Point> &points, bool accuracy_time)
{
	Point *req;                                         // Середина пересечения пары квадратов

	unsigned int steps = 0;                             // Количество шагов в решении
	bool intersected = false;                           // Флаг наличия пересечения

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

			if (++steps && !data.squares[i].covered && !data.squares[j].covered && (req != nullptr))
			{
				data.squares[i].covered = data.squares[j].covered = true;
				points.push_back(*req);

				if (accuracy_time)
					for (int k = 0; k < data.squares.size(); ++k)
						if ((k != i) && (k != j) && belong(*req, data.squares[k], data.side_length))
							data.squares[k].covered = true;

				intersected = true;
				break;
			}
		}
	}

	for (int i = 0; i < data.squares.size(); ++i)
		if (!data.squares[i].covered)
			points.push_back(*middle(i, i));

	return steps;
}