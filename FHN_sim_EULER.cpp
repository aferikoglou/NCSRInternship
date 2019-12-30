#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <omp.h>
#include <sys/stat.h> //#include <io.h> for WINDOWS

#define PI 3.14159265359

using namespace std;

/***** Parameter Declarations *****/
double dt = 0.001; //Time step
long it = 0;       //Current iteration

double sigma = 0.1;    //Coupling strength
double a = 0.5;        //Threshold parameter
double epsilon = 0.05; //Time scale separation parameter

string simulation; //Simulation name
int N;             //Grid dimension
int r;             //Coupling radius
double phi;        //Coupling phase
int total_time;    //Total simulation time
int seed;          //Random number generator seed

long total_iter;  //Total iterations
long N_r;         //Number of neighbours
double **B;       //Coupling matrix
double sum_coeff; //Summary coefficient

double **x;      //Activator variable at current iteration
double **x_next; //Activator variable at next iteration
double **y;      //Inhibitor variable at current iteration
double **y_next; //Inhibitor variable at next iteration

long **cycle_counter; //Cycle counter

string to_format(const int num)
{
    stringstream ss;
    ss << setw(6) << setfill('0') << num;
    return ss.str();
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

int shortest_dist(int i, int j)
{
    return min(abs(i - j), N - abs(i - j));
}

void init()
{
    /***** Create output directory *****/
    string simulation_path = "resources//" + simulation;
    mkdir(simulation_path.c_str(), 0777); // mkdir(simulation_path.c_str()); for WINDOWS

    /***** Calculation of total iterations, number of neighbours, coupling matrix and summary coefficient *****/
    total_iter = (total_time / dt);

    N_r = 0;

    int iLeftCorner = N + (N / 2 - 1) - r;
    int jLeftCorner = N + (N / 2 - 1) - r;

    for (int m = iLeftCorner; m < iLeftCorner + 2 * r + 1; m++)
    {
        for (int n = jLeftCorner; n < jLeftCorner + 2 * r + 1; n++)
        {
            int x_dist = shortest_dist(N / 2 - 1, m % N);
            int y_dist = shortest_dist(N / 2 - 1, n % N);
            if (x_dist * x_dist + y_dist * y_dist <= r * r)
            {
                N_r++;
            }
        }
    }

    B = new double *[2];
    for (int i = 0; i < 2; i++)
        B[i] = new double[2];

    B[0][0] = cos(phi);
    B[0][1] = sin(phi);
    B[1][0] = (-1) * sin(phi);
    B[1][1] = cos(phi);

    sum_coeff = sigma / (N_r - 1);

    /***** Array creation and initialization *****/
    x = new double *[N];
    x_next = new double *[N];
    y = new double *[N];
    y_next = new double *[N];

    cycle_counter = new long *[N];

    for (int i = 0; i < N; i++)
    {
        x[i] = new double[N];
        x_next[i] = new double[N];
        y[i] = new double[N];
        y_next[i] = new double[N];

        cycle_counter[i] = new long[N];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            x_next[i][j] = 0.0;
            y_next[i][j] = 0.0;

            cycle_counter[i][j] = 0;
        }
    }

    /***** Create initial conditions for activator and inhibitor variables *****/
    srand(seed);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            x[i][j] = fRand(-2, 2);
            y[i][j] = fRand(-2, 2);
        }
    }
}

int main(int argc, char *argv[])
{
    /***** Get simulation name, grid dimension, coupling radius, coupling phase, total simulation time and seed *****/
    if (argc != 7)
    {
        cout << "Invalid input" << endl;
        cout << "Usage : .\\FHN_sim_EULER.exe simulation_name grid_dimension coupling_radius coupling_phase total_simulation_time seed" << endl;
        exit(EXIT_FAILURE);
    }

    simulation = argv[1];
    N = stoi(argv[2]);
    r = stoi(argv[3]);
    phi = stod(argv[4]);
    total_time = stoi(argv[5]);
    seed = stoi(argv[6]);

    /***** Initialization *****/
    init();

    /***** Simulation *****/
    auto begin_time = chrono::high_resolution_clock::now();

    for (it = 0; it <= total_iter; it++)
    {
        /***** Iteration Start *****/
        /***** Save results about current activator potential *****/
        if (it % 10000 == 0 || it == total_iter)
        {
            cout << "Iteration " << it << " of " << total_iter << endl;

            ofstream output_file;

            output_file.open("resources//" + simulation + "//POT_IT_" + to_format(it) + ".dat");

            for (int i = 0; i < N; i++)
            {
                for (int j = 0; j < N; j++)
                {
                    output_file << i << '\t' << j << '\t' << x[i][j] << endl;
                }
            }

            output_file.close();
        }

        /***** Activator and inhibitor potential and mean phase velocity calculation *****/
        #pragma omp parallel for schedule(dynamic) collapse(2)
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                double deri1, deri2, sum_1 = 0.0, sum_2 = 0.0;
                deri1 = x[i][j] - 0.3333333 * x[i][j] * x[i][j] * x[i][j] - y[i][j];
                deri2 = x[i][j] + a;

                int iLeftCorner = N + i - r;
                int jLeftCorner = N + j - r;

                for (int m = iLeftCorner; m < iLeftCorner + 2 * r + 1; m++)
                {
                    for (int n = jLeftCorner; n < jLeftCorner + 2 * r + 1; n++)
                    {
                        int x_dist = shortest_dist(i, m % N);
                        int y_dist = shortest_dist(j, n % N);
                        if (x_dist * x_dist + y_dist * y_dist <= r * r && (m % N != i || n % N != j))
                        {
                            sum_1 += B[0][0] * (x[i][j] - x[m % N][n % N]) + B[0][1] * (y[i][j] - y[m % N][n % N]);
                            sum_2 += B[1][0] * (x[i][j] - x[m % N][n % N]) + B[1][1] * (y[i][j] - y[m % N][n % N]);
                        }
                    }
                }

                x_next[i][j] = x[i][j] + dt * (deri1 - sum_coeff * sum_1) / epsilon;
                y_next[i][j] = y[i][j] + dt * (deri2 - sum_coeff * sum_2);

                /***** Change cycle counter *****/
                if (x[i][j] < 0 && x_next[i][j] > 0 && it > (int)(1000 / dt))
                    cycle_counter[i][j]++;
            }
        }

        /***** Prepare data for next iteration *****/
        #pragma omp parallel for schedule(dynamic) collapse(2)
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                x[i][j] = x_next[i][j];
                y[i][j] = y_next[i][j];
            }
        }
        /***** Iteration End *****/
    }

    /***** Save results about mean phase velocity *****/
    ofstream output_file;

    output_file.open("resources//" + simulation + "//MPV.dat");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            output_file << i << '\t' << j << '\t' << 2.0 * PI * ((cycle_counter[i][j] + 0.0) / (total_time - 1000)) << endl;
        }
    }

    output_file.close();

    output_file.open("resources//" + simulation + "//MPV_HORCUT.dat");

    for (int i = 0; i < N; i++)
    {
        output_file << i << '\t' << 2.0 * PI * ((cycle_counter[i][N / 2] + 0.0) / (total_time - 1000)) << endl;
    }

    output_file.close();

    /***** Save results about simulation duration *****/
    auto end_time = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::seconds>(end_time - begin_time).count();

    output_file.open("resources//" + simulation + "//SIM_DURATION.dat");

    output_file << "Simulation Duration = " << duration << " seconds" << endl;

    output_file.close();

    return 0;
}