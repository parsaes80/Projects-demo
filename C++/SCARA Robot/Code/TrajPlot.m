clc;
close all; 
clear;

fileActual = 'real_path.csv';
fileTheory = 'calulated_path.csv';

matActual = readtable(fileActual);
matTheory = readtable(fileTheory);


j1A = table2array(matActual(:,1)); %extract column 1 from matrix Actual
j1T = table2array(matTheory(:,1));
j1len = length(j1A);
j2A = table2array(matActual(:,2)); %extract column 2 from matrix Actual
j2T = table2array(matTheory(:,2));

j3A = table2array(matActual(:,3)); %extract column 3 from matrix Actual
j3T = table2array(matTheory(:,3));

j4A = table2array(matActual(:,4)); %extract column 4 from matrix Actual
j4T = table2array(matTheory(:,4));


j5T = table2array(matTheory(:,5)); %extract column 5 from matrix theory

figure(1)
subplot(2, 1, 1);

x=j5T;

hold on
title('Joint coordinates (Actual)')
xlabel('Sample Number');
ylabel('Angle(theta)');
plot(x, j1A);
hold off;

subplot(2, 1, 2);
hold on
title('Joint coordinates (Theoretical)')
xlabel('Sample Number');
ylabel('Angle(theta)');
plot(x, j1T); 


subplot(2, 1, 1);
hold on
xlabel('Sample Number');
ylabel('Angle(theta)');
plot(x, j2A);
hold off;

subplot(2, 1, 2);
hold on
xlabel('Sample Number');
ylabel('Angle(theta)');
plot(x, j2T);

subplot(2, 1, 1);
hold on
xlabel('Sample Number');
ylabel('Angle(theta)');
plot(x, j4A);
hold off;
legend('Joint 1', 'Joint 2', 'Joint 4'); 

subplot(2, 1, 2);
hold on
xlabel('Sample Number');
ylabel('Angle(theta)')
plot(x, j4T);
hold off;
legend('Joint 1', 'Joint 2', 'Joint 4'); 

figure(2)
subplot(2, 1, 1);

hold on
title('Joint coordinates (Actual)')
xlabel('Sample Number');
ylabel('Distance (mm)');
plot(x, j3A);
hold off;

subplot(2, 1, 2);
hold on
title('Joint coordinates (Theoretical)')
xlabel('Sample Number');
ylabel('Distance (mm)');
plot(x, j3T);
hold off;


%end effector position
j1TR = deg2rad(j1T);
j2TR = deg2rad(j2T);


j2x = 195*cos(j1TR) + 142*cos(j1TR + j2TR);
j2y = 195*sin(j1TR) + 142*sin(j1TR + j2TR);

figure(3)
xlim([-350 350])    % Axis limits
ylim([-350 350])
hold on
title('Position of The End-Effector')
xlabel('X');
ylabel('Y');

plot(j2x,j2y);
hold off;