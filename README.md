# Examples:
![Alt Text](https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExbWx3ODZ4dmlzYXZiNzc5aGgyc29heDlsemkzMW8xNmM1eTc3aXllNSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Qutj08QBhGEU77iz1P/source.gif)

# How to run this:

1. `git clone https://github.com/msharipov/simulated-annealing`
2. Create required folders with `python setup.py`
3. Configure the `potential()` and `accept()` functions in `annealing.cpp`
4. Compile in the VS Developer PowerShell with `cl /EHsc /O2 annealing.cpp`
5. Run the computation with `.\annealing.exe`
6. Run `python plot.py` to plot the data

When run without command line arguments, the initial condition will have all
particles surrounded by empty space. Generated .dat files are stored in the
`output/` folder. Plots of the data are stored in `plots/`.

You can load one of the generated .dat files as an initial condition. To do this,
run `.\annealing [PATH TO .DAT FILE] [INITIAL STEP]` instead.