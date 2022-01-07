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
 * Если квадраты пересекаются, возвращает указатель на
 * координаты середины их пересечения, иначе - nullptr.
 */
Point* Solver::middle(unsigned int first, unsigned int second)
{
	Segment x1{}, x2{}, y1{}, y2{};                     // Проекции квадратов на координатные оси.
	Point *req = nullptr;                               // Середина пересечения пары квадратов.

	x1.begin = data.squares.at(first).corner.x;
	x1.end = x1.begin + data.side_length;

	y1.begin = data.squares.at(first).corner.y;
	y1.end = y1.begin + data.side_length;

	x2.begin = data.squares.at(second).corner.x;
	x2.end = x2.begin + data.side_length;

	y2.begin = data.squares.at(second).corner.y;
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
 * TODO: Написать комментарий.
 */
unsigned int Solver::cover(vector<Point> &points)
{
	Segment x_intersection{}, y_intersection{};
	Point point{};

	unsigned long int steps = 0;

	for (int i = 0; i < data.squares.size(); ++i)
		if (!data.squares.at(i).covered)
		{
			x_intersection.begin = data.squares.at(i).corner.x;
			x_intersection.end = x_intersection.begin + data.side_length;

			y_intersection.begin = data.squares.at(i).corner.y;
			y_intersection.end = y_intersection.begin + data.side_length;

			for (int j = i + 1; j < data.squares.size(); ++j)
				if (++steps && !data.squares.at(j).covered)
				{
					if ((x_intersection.end > data.squares.at(j).corner.x) && (x_intersection.begin < data.squares.at(j).corner.x + data.side_length))
						x_intersection.begin = data.squares.at(j).corner.x;
					else if ((x_intersection.begin < data.squares.at(j).corner.x + data.side_length) && (x_intersection.end > data.squares.at(j).corner.x))
						x_intersection.end = data.squares.at(j).corner.x + data.side_length;
					else
						continue;

					if ((y_intersection.end > data.squares.at(j).corner.y) && (y_intersection.begin < data.squares.at(j).corner.y + data.side_length))
						y_intersection.begin = data.squares.at(j).corner.y;
					else if ((y_intersection.begin < data.squares.at(j).corner.y + data.side_length) && (y_intersection.end > data.squares.at(j).corner.y))
						y_intersection.end = data.squares.at(j).corner.y + data.side_length;
					else
						continue;

					data.squares.at(j).covered = true;
				}

			data.squares.at(i).covered = true;

			point.x = (x_intersection.begin + x_intersection.end) / 2.0;
			point.y = (y_intersection.begin + y_intersection.end) / 2.0;

			points.push_back(point);
		}

	return steps;
}


/*
 * Решает задачу покрытия квадратов точками.
 * После выполнения функции в векторе points хранятся координаты точек покрытия.
 * В зависимости от переданного параметра улучшает точность или скорость работы.
 * Возвращает количество шагов, за которое была решена задача.
 */
/*
unsigned int Solver::old_cover(vector<Point> &points, bool accuracy_time)
{
	Point *req;                                         // Середина пересечения пары квадратов.

	unsigned int steps = 0;                             // Количество шагов в решении.
	bool intersected = false;                           // Флаг наличия пересечения.

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

			if (++steps && !data.squares.at(i).covered && !data.squares.at(i).covered && (req != nullptr))
			{
				data.squares.at(i).covered = data.squares.at(j).covered = true;

				//if (points.find(*req) == points.end())
					points.insert(*req);

				if (accuracy_time)
					for (int k = j + 1; k < data.squares.size(); ++k)
						if (++steps && belong(*req, data.squares.at(k), data.side_length))
							data.squares.at(k).covered = true;

				intersected = true;
				break;
			}
		}
	}

	for (int i = 0; i < data.squares.size(); ++i)
		if (!data.squares.at(i).covered)
			points.insert(*middle(i, i));

	return steps;
}*/