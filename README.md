# Chimera patterns in 2D networks of coupled FitzHugh-Nagumo neurons

In this project we recreated part of the results of the paper __Chimera patterns in two-dimensional networks of coupled neurons__ in docs folder. We created a simulation of a network of FitzHugh-Nagumo oscillators coupled in a two-dimensional toroidal geometry in order to observe the *Chimera States* that arise. For the simulation algorithm we used *Euler* method and *Runge-Kutta* method with two and four stages. In order to accelarate the simulation we used *OpenMP* API.

> Equation (2a) and (2b) of the paper __Chimera patterns in two-dimensional networks of coupled neurons__ were printed incorrectly. The term with the summation must be subtracted to the rest of the equation.

The simulation program gets as command line arguments the name of the output folder and a set of simulation parameters (grid size, coupling radius, coupling phase, simulation time and seed for the random initial conditions generator). The simulation creates a *.dat* file every 20 time units that contains the potential value for each neuron in the grid. It also creates a *.dat* file for the mean phase velocity of each neuron in the grid, a *.dat* file for the mean phase velocity horizontal cut (the cut is made for j = 50) and a *.dat* file with the total simulation time. After the simulation is finished a python script creates *.png* files for each potential *.dat* file, for the mean phase velocity *.dat* file and the mean phase velocity horizontal cut *.dat* file. Finally, a *.gif* file is created to demonstrate the potential evolution through time.

This project was created through my *NCSR Internship* supervised by *Dr. Astero Provata*.

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

Here we demonstrate the output .png and .gif files for the parameters in Run simulation section.

* *Initial conditions (random)*
<img src="images/POT_IT_000000.png" width="350" height="350">

* *Potential for each neuron in the grid after 2000 time units*
<img src="images/POT_IT_200000.png" width="350" height="350">

* *Mean phase velocity for each neuron in the grid at the of the simulation*
<img src="images/MPV.png" width="350" height="350">

* *Mean phase velocity horizontal cut at the of the simulation*
<img src="images/MPV_HORCUT.png" width="300" height="320">

* *Potential GIF*
<img src="images/POT_GIF.gif" width="360" height="360">
