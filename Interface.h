#pragma once

#include "Solver.h"

#include <iostream>
#include <fstream>
#include <utility>
using namespace std;


// Класс, предоставляющий интерфейс для решения задачи по шагам.
class Interface
{
	private:

	Solver *solver = nullptr;               // Экземпляр класса, решающего задачу.
	TaskData data;                          // Набор данных для задачи.


	public:

	/*
	 * Считывает с клавиатуры данные для одной задачи.
	 */
	void read_data();

	/*
	 * Запускает решение задачи на данных, введенных с клавиатуры.
	 * В зависимости от переданного параметра описывает решение
	 * подробно или просто выдает конечный ответ.
	 *
	 * Параметры:
	 * bool show_steps - флаг подробного описания решения
	 */
	void solve(bool show_steps = false);
};