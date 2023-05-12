# Projects-demo
hello!


Welcome to my repository. I'm currently studying systems engineering at SFU.


In this repository, there are List of projects I have developed in SFU. I have Categorized them by coding language. Enjoy the code :)

More information on the projects is below:

ARM assembly:
1. fibonnaci calculator:
        The first main file is bigAdd.S which adds two large numbers that are stored in memory in little-endian format.
        The second main file is BigFib.c which uses the adder to calculate the next number in our Fibonacci sequence.

C++:
1. Queue and Deque using Linked Lists:
        The implementation of deque is done by using a two-way linked list to store and modify the data.
        The Queue class is created by hand-picking the methods from the Deque object.
   
2. Customizable admission system:
        This program consists of a student class that has two subclasses to store "domestic" and "international" students.
        Also, there are classes to store the different student data types in a Linked List Data structure.
        The main function handles the interaction with the user and what the program should do next.

3. Heap template data structure:
        The heap class contains a vector that stores the data and the data is manipulated so that the vector preserves the properties of the heap.
   
4. Red Black Tree:
        Am implementation of a binary tree that will balance itself across all branches so the search time remains low.
   
5. Strings lists:
        This class stores an array of strings and the array size increase if the number of strings gets higher, this is done preserve memory.

6. sorting algorithms:
        The algorithms in this class can sort any type of input because they are implemented using template.

Matlab:
1. Spline approximation:
       The best-fit line through a set of data using the spline interpolation method. Both not-a-knot and clamped methods are available in the file.
   
2. Modeling electric force:
       Given the amount, number, and location of the charges, this script gives a 3D view of the electric and the magnetic field.

3. Lagrange polynomial:
        The best-fit line through a set of data using the Lagrange polynomials, and comparing the error for lower and higher degree polynomials.
   
4. Gauess-sidel method for matrix equations:
        An iterative method for solving matrix equations.
   
5. Free Fall modeling with ode45:
        This script is a simulation of Felix Baumgartner falling from space using ode45. This simulation is then compared to the real-world data.

6. Finding polynomial roots using Newton's method:
       Using Newton's method, this script finds the answer for (f = x^4  -x^3). After that, the rate of convergence (α) and the error constant(λ) are calculated.


VHDL:
1. Divider FSM:
        A finite state machine that divides two 4-bit numbers, and outputs the quotient and the remainder. The testbench is also available for running the simulation.
   
2. Roulette:
        This project contains the system needed to play a game of roulette. The spinwheel generates a random number.
        Based on the inputs and the spinwheel number win.vhd calculates which bets are won dn lost and new_balance.vhd calculated the new money balance.
        Also, there are register and a 7seg display for I/O. After this, you won't have to go to Vegas anymore.  

4. UART receiver and transmitter:
       Using the UART transmission protocol, The transmitter sends an 8-bit data to the receiver via one signal.
       Another signal is needed for the handshaking and the error checking. The error checking is done through parity and stop bits.
       If the parity and the stops bits are wrong the receiver will send a request for another data transfer. The testbench is available for simulation.