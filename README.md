# Chimera patterns in 2D networks of coupled FitzHugh-Nagumo neurons

In this project we recreated part of the results of the paper entitled __Chimera patterns in two-dimensional networks of coupled neurons__ in docs folder. We created a simulation of a network of FitzHugh-Nagumo oscillators coupled in a two-dimensional toroidal geometry in order to observe the __Chimera States__ that arise. For the simulation algorithm we used __Euler__ method and __Runge-Kutta__ method with two and four stages. In order to accelarate the simulation we used __OpenMP__ API.

The simulation program gets as command line arguments the name of the output folder and a set of simulation parameters. The simulation creates __.dat__ files that contain the potential value for each neuron in the grid every 20 time units, the mean phase velocity for each neuron in the grid, the mean phase velocity horizontal cut and the total simulation time. After it is finished a python script creates __.png__ files for each potential .dat file, mean phase velocity .dat file and mean phase velocity horizontal cut .dat file. A __.gif__ file is also created to demonstrate the potential evolution through time. 

## Getting Started

These instructions will get you a copy of the project on your local machine for development and testing purposes.

### Prerequisites

* C++ compiler
* Python 3
    - [PIL package](https://pypi.org/project/Pillow/)
* Gnuplot

### Simulation Setup

After downloading the software in the Prerequisites section you can clone this repository on your local machine.

Before you start create a folder with the name __resources__. This will be the folder in which the output folders will be created.

Compile simulation file

```cpp
g++ -Wall -O3 -fopenmp -o .\FHN_sim_RK2.exe .\FHN_sim_RK2.cpp
```

Run simulation

```cpp
.\FHN_sim_RK2.exe simulation_N_100_R_33 100 33 1.370796 2000 15885 
```

Run python plotting script

```
python .\out_plotting_script.py resources simulation_N_100_R_33
```

## Sample Output

Here we demonstrate output .png files for the parameters in Run simulation section.

1) Initial conditions
![](images/POT_IT_000000.png=250x250)
2) Potential value for each neuron in the grid after 2000 time units
![](images/POT_IT_200000.png=250x250)
3) Mean phase velocity for each neuron in the grid
![](images/MPV.png=250x250)
4) Mean phase velocity horizontal cut
![](images/MPV_HORCUT.png=250x250)