#pragma once

#include "Solver.h"

#include <iostream>
#include <fstream>
using namespace std;


// Класс, предоставляющий интерфейс для решения задачи по шагам.
class Interface
{
	private:

	Solver *solver = nullptr;               // Экземпляр класса, решающего задачу.


	public:

	/*
	 * Считывает с клавиатуры данные для одной задачи и
	 * инициализирует ими экземпляр класса, решающего ее.
	 */
	void read_data();
};