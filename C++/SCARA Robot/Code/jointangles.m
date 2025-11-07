filenametheta1 = 'Theta1.txt';
filenametheta2 = 'Theta2.txt';
filenamed3 = 'd3.txt';
filenametheta4 = 'Theta4.txt';

T1 = readtable(filenametheta1);
T2 = readtable(filenametheta2);
T3 = readtable(filenamed3);
T4 = readtable(filenametheta4);

T1array = T1{:,1};
T2array = T2{:,1};
T3array = T3{:,1};
T4array = T4{:,1};

figure
Title('Joint angle theta 1 from start to final state')
plot(T1array)

figure 
Title('Joint angle theta 2 from start to final state')
plot(T2array)

figure 
Title('Joint d3 from start to final state')
plot(T3array)

figure 
Title('Joint angle theta 4 from start to final state')
plot(T4array)