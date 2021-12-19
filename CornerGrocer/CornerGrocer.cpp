#include <Python.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Declare function to keep main() near the top (for readability)
int MenuSelect(PyObject* py_module);

int main() {
	// Initialize the Python Interpreter
	Py_Initialize();

	PyObject* py_module = PyImport_ImportModule("PyCornerGrocer");
	PyErr_Print(); // Prints error from Python

	// Imports the file and does processing and sorting for Python functions
	PyObject_CallObject(PyObject_GetAttrString(py_module, "ImportAndSort"), NULL);
	PyErr_Print();
	
	MenuSelect(py_module);
	// Finish the Python Interpreter
	Py_Finalize();
	return 0;
}

int MenuSelect(PyObject* py_module) {
	int userSelect;
	string userGrocery;
	ifstream histFile;	// Input file stream
	string groceryItem;
	int groceryQty;

	while (true) {
		cout << "Please choose one of the following . . .\n";
		cout << "1: Purchased items and quantities\n";
		cout << "2: Quantity of specific purchased item\n";
		cout << "3: Purchased items histogram\n";
		cout << "4: Exit\n" << endl;

		// Ensure input is 1, 2, 3, or 4 only
		while (!(cin >> userSelect) || userSelect < 1 || userSelect > 4) {
			cout << "Invalid input. Please enter 1, 2, 3, or 4." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}

		// Clears rest of buffer in case characters were entered after integer
		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		switch (userSelect) {
		case 1:
			cout << "Purchased items and quantities, sorted from most to least:" << endl;
			// Calls "ItemsAndQuantities" function from PyCornerGrocer.py
			PyObject_CallObject(PyObject_GetAttrString(py_module, "ItemsAndQuantities"), NULL);
			break;

		case 2:
			cout << "Type one of the following items for its quantity:" << endl;
			// Calls "JustItems" function from PyCornerGrocer.py to list purchased items
			PyObject_CallObject(PyObject_GetAttrString(py_module, "JustItems"), NULL);
			cin >> userGrocery;
			// Calls "SpecificItemQty" function from PyCornerGrocer.py and passes string from user input
			cout << _PyLong_AsInt(PyObject_CallObject(PyObject_GetAttrString(py_module, "SpecificItemQty"), Py_BuildValue("(z)", userGrocery.c_str())));
			break;

		case 3:
			cout << "Purchased items histogram:" << endl;
			// Calls "DoubleValue" function from PyMult.py and passes integer from GetUserInteger function
			PyObject_CallObject(PyObject_GetAttrString(py_module, "HistogramFile"), NULL);

			// Saved in solution main directory
			histFile.open("frequency.dat");

			if (!histFile.is_open()) {
				cout << "Could not open file frequency.dat" << endl;
				exit(EXIT_FAILURE);
			}

			do {
				histFile.clear();

				histFile >> groceryItem;
				histFile >> groceryQty;

				if (!histFile.fail()) {
					cout << setfill(' ') << setw(15) << groceryItem << " ";
					for (int i = 0; i < groceryQty; i++) {
						cout << '*';
					}
					cout << endl;
				}
			} while (!histFile.eof());

			histFile.close();
			break;

		case 4:
		default:
			cout << "Program finished." << endl;
			return 0;
			break;
		}

		PyErr_Print(); // Prints error from Python
		cout << endl;
		system("pause");
		system("cls");  // Clear console window
	}
}