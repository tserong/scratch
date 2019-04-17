/*

Experiment to run python code in subinterpreters.  All it does is take
a list of python files as arguments, then for each of these it creates
a new subinterpreter, then executes that file.  This all happens in
series.

*/

#include <Python.h>
#include <iostream>

int main(int argc, char ** argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " file.py [...]" << std::endl;
    }

    Py_SetProgramName(L"/usr/bin/python3");
    Py_Initialize();

    for (int i = 1; i < argc; ++i) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            std::cerr << "Can't open " << argv[i] << std::endl;
            continue;
        }

        PyThreadState * ts = Py_NewInterpreter();
        if (ts) {
            std::cout << "Running " << argv[i] << " in subinterpreter " << ts << std::endl;
            PyRun_SimpleFile(fp, argv[1]);
        } else {
            std::cerr << "Can't create subinterpreter for " << argv[i] << std::endl;
        }

        fclose(fp);
    }

    Py_Finalize();
    return 0;
}
