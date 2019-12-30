# Chimera patterns in 2D networks of coupled FitzHugh-Nagumo neurons

In this project we recreated part of the results of the paper entitled __Chimera patterns in two-dimensional networks of coupled neurons__ in docs folder. We created a simulation of a network of FitzHugh-Nagumo oscillators coupled in a two-dimensional toroidal geometry in order to observe the __Chimera States__ that arise. For the simulation algorithm we used __Euler__ method and __Runge-Kutta__ method with two and four stages. In order to accelarate the simulation we used __OpenMP__ API.

The simulation program gets as command line arguments the name of the output folder and a set of simulation parameters. The simulation creates __.dat__ files that contain the potential value for each neuron in the grid every 20 time units, the mean phase velocity for each neuron in the grid, the mean phase velocity horizontal cut and the total simulation time. After it is finished a python script creates __.png__ files for each potential __.dat__ file, mean phase velocity __.dat__ file and mean phase velocity horizontal cut __.dat__ file. A __.gif__ file is also created to demonstrate the potential evolution through time. 

## Getting Started

These instructions will get you a copy of the project on your local machine for development and testing purposes.

### Prerequisites

* C++ compiler
* Python 3
* Gnuplot

What things you need to install the software and how to install them

```
Give examples
```

### Installing

A step by step series of examples that tell you how to get a development env running

Say what the step will be

```
Give the example
```

And repeat

```
until finished
```

End with an example of getting some data out of the system or using it for a little demo

## Running the tests

Explain how to run the automated tests for this system

### Break down into end to end tests

Explain what these tests test and why

```
Give an example
```

### And coding style tests

Explain what these tests test and why

```
Give an example
```