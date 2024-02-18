# Examples:
<img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExbWx3ODZ4dmlzYXZiNzc5aGgyc29heDlsemkzMW8xNmM1eTc3aXllNSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Qutj08QBhGEU77iz1P/source.gif" width="250" height="250">

# How to run this:

## Windows:
REQUIRED:
- Visual Studio 2017+, including the "Desktop development with C++" workload
- Python 3.8+

1. In PowerShell, clone the repo with `git clone https://github.com/msharipov/simulated-annealing`.
2. Create required folders with `python setup.py`.
3. Configure the `potential()` and `accept()` functions in `parameters.cpp`.
4. Set the `HEIGHT` and `WIDTH` of the matrix in `parameters.h`. `MAX_STEPS` controls how many steps the computation will run for.
5. Compile in the VS Developer PowerShell with `cl /EHsc /O2 /Fe: annealing.exe parameters.cpp annealing.cpp`.
6. Run the computation with `.\annealing.exe`.
7. Run `python plot.py` to plot the data.

When run without command line arguments, the initial condition will have all
particles surrounded by empty space. Generated .dat files are stored in the
`output/` folder. Plots of the data are stored in `plots/`.

You can load one of the generated .dat files as an initial condition. To do this,
run `.\annealing [PATH TO .DAT FILE] [INITIAL STEP]` instead.
