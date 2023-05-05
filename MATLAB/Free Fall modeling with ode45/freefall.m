
%% Discription:

%MATLAB to model Felix Baumgartner%s altitude, velocity, and acceleration for the first minute after
%he jumped from 38,969.4 meters above sea level. Compare by plotting modeled altitude, velocity,
%and acceleration with the data that was measured1 and data derived from those measurements.
%Write a function that takes as parameters at least the end time (in seconds) for a plot (60 seconds
%for Part 1), a title, and the modelled altitude and velocity, and makes plots for the altitude, the
%velocity, and the acceleration for both modeled and measured/calculated data

%% main

function [res] = assignment2 (t , A) % t: Duration time simiulated  A: Data chart measured from the FALL(in the folder data)
res = 0;


% constants -- you can put constants for the program here
% MY_CONST = 123;

% variables -- you can put variables for the program here
% myVar = 456;


% prepare the data
% <place your work here>
% ... = xlsread()/csvread()/readtable()
% ...
% myVector(isnan(myVector))=[];

% <put here any conversions that are necessary>
% km/h *(10/36) = m/s this will be used alot
%%  Part 1
% How accurate is the model for the first portion of the minute? 
% How accurate is the model for the last portion of that first minute? 
%
% Given the data file and comparing it with the first portion of model, We
% can see that the predicted model has a similar curve as the datas real
% model (fot altitude). However, a slight difference is vissible between
% 50-60 seconds time period.
% For the speed graph comparing, two graphs are alike between 0-30 seconds,
% but between 30-60 seconds we can see that the real speed gets closer to
% zero because of air resistance and our predicted model has a linear graph
% going towards negative velocity meaning thaat it's increasing (without air
% resistance)
% Lastly, when we look at the acceleration garphs,
%
% Overall, we can observe that the first portion of the minutes we have more
% accurate graphs which are more similar to the real graph. But for the last
% portion of the minute as the air resistance changes the reall graph. More
% difference and changes show up.
%
% Comment on the acceleration calculated from the measured data. 
% The acceleration is??? distorted osolationg between 0 and  differant
% values.
%
%
% Is there any way to smooth the acceleration calculated from the data?
% The way we calculated mododeled and sapamled accelaration is as follows:
% we used the diff(x) fucntion to calculate the differance between
% each and the one after it. By usinbg this functioin once for speed and
% once for time we achive the arrays diff(v), and diff(t). By the fourmula
% a=dv/dt,we can calculate the acceleration for the time in between each two
% elements of the given time. axl is the data from ode45, and raxl is the
% data from the sample.  the accelaration we get from the sample is didstorted. 
% We can fix this by using every 25 element in data and
% using smoothdata fucntion four times. 

part = 1;


start = [38969.4 10];
tspan =[0 60]; %analysing for the first miniute
  
[T,M] = ode45(@fall, tspan,  start );





A = table2array(A);


% <call here your function to create your plots>
% y vs t

figure(1);
plot (T,M(:,1)); 

hold on;
 plot( A(1:1631,1), A(1:1631,2)); 
 
grid on;
xlabel ('time(s)');
ylabel ('altitude(m)');
title ('part1 freefall(altitude)');
hold off;
legend('Modeled Data','Real Data');
% v vs t 

 figure(2);
plot (T,M(:,2)*36/10); 
hold on; 
plot( A(1:1631,1), -A(1:1631,3) ); 
grid on;
xlabel ('time(s)');
ylabel ('speed(km/h)');
title ('part1 freefall(speed)');
hold off;
legend('Modeled Data','Real Data');
%a vs t


axl= diff(M(:,2))./(diff(T));

raxl= diff(  A(:,3)) ./ diff(A(:,1)); 

plotaxl = -1 *10/36 *raxl(1:25:15348);

unsmothedplotaxl = plotaxl;

for i=1:4
plotaxl = smoothdata(plotaxl); 
end

plotttime = A(2:25:end , 1);


 %Note that size(diff(x))= size(x) +1. by removing the first time element we
 %can plot the graph of accelaration. 
 figure(3) %this is unsmothed accelation graph
 xlim([0 60]);
 plot(T(2:end) , axl,'g');
 hold on;
plot(plotttime , unsmothedplotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part1 freefall(acceleration)')
    
figure(4) %this is smothed accelation graph
 plot(T(2:end) , axl,'g');
 hold on;
 xlim([0 60]);
plot(plotttime , plotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part1 freefall(acceleration)')


%% Part 2
% Estimate your uncertainty in the mass that you have chosen (at the 
% beginning of the jump). 
% We searched on internet for the mass and found 118 kg for 
% Felix Baumgartner and all the things he carried during his jump.
%
% How sensitive is the velocity and altitude reached after 60 seconds to 
% changes in the chosen mass?
% Mass play an important role in free fall and resistance. Comparing the graphs, for
% alititude , the real model has notable slope comparing to the predicted
% one. I think that the mass has key role in changing the graph slope.
% These changes are significant when comparing the velocity graphs.

part = 2;
tspan =[0 t];
[T,M] = ode45(@fall, tspan,  start );


% y vs t

figure(5);
plot (T,M(:,1)); 

hold on;
plot( A(:,1), A(:,2)); 
grid on;
xlabel ('time(s)');
ylabel ('altitude(m)');
title ('part2 freefall(altitude)')
legend('Modeled Data','Real Data');
% v vs t 

 figure(6);
plot (T,M(:,2)*36/10); 
hold on; 
plot( A(:,1), -A(:,3) ); 
grid on;
xlabel ('time(s)');
ylabel ('speed(km/h)');
title ('part2 freefall(speed)')
legend('Modeled Data','Real Data');
%a vs t
 



axl= (diff(M(:,2)))./diff(T ); 



figure(7)
xlim([0 t]);
plot(T(2:end) , axl,'g');
hold on;
plot(plotttime , plotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part2 freefall(speed)')



%% Part 3
% Felix was wearing a pressure suit and carrying oxygen. Why? 
% We know that when we get far from the sea level, atmospheric pressure
% drops. So there will be less Oxygen for Felix to breathe. That's why he
% was carrying oxygen. Pressure suit helped him to avoid him feeling all
% the change in pressure during the freefall with high speed. The sudden
% change in pressure can make really bad injurie.
%
%     What can we say about the density of air in the stratosphere?
% The density of air near the top of the stratosphere is nearly zero.
% Also The ozone layer is found within the stratosphere between 15 to 30 km
% (9 to 19 miles) altitude.
%
%     How is the density of air different at around 39,000 meters than it 
%     is on the ground?
% The air density is slightly more than 0.003996 kg/m^3 at 39000m above the
% sea level and is 1.225 kg/m^3 at altitude zero (sea level or ground).
%
% What are the factors involved in calculating the density of air? 
% Pressure, temperature and humidity all affect air density.
%
% How do those factors change when we end up at the ground but start 
% at the stratosphere? 
% Far away from the ground (stratosphere),the air pressure and temprature is
% way less than pressure at the ground.  
% The relative humidity decreases linearly with an increase in altitude 
% at an average of 4% per kilometer. altitude at an average of 4% per
% kilometer.
%
% Please explain how calculating air density up 
%  to the stratosphere is more complicated than say just in the troposphere.
% Finding the difference in air density which depends on 3 factors stated
% above is not easy because in different altitude we might have significant
% changes. And the texture of troposphere is different from stratosphere,
% depending on many factors that must be consider for an accurate answer.
%
% What method(s) can we employ to estimate [the ACd] product? 
% We use the frag constant cd=0.4 and with that we can estimate A. By
% knowing that a person when falling can have up to a 1.2m^2 of surface
% area we twik the calue of A suck that the resulted v vs t graph is close to the
% sample data. we reached an astimated value of 1 m^2. 
%
% What is your estimated [ACd] product?
% 0.48
%
% [Given what we are told in the textbook about the simple drag constant, b,] 
%   does the estimate for ACd seem reasonable?
% this seems reasonable because of you watch the video of him falling, most
% of the tome he is rotating in ait
part = 3;


start = [38969.4 10];
tspan =[0 t];

[T,M] = ode45(@fall, tspan,  start );



axl= (diff(M(:,2)))./diff(T ); 






% y vs t

figure(8);

plot (T,M(:,1)); 

hold on;
plot( A(:,1), A(:,2)); 
grid on;
xlabel ('time(s)');
ylabel ('altitude(m)');
title ('part3 freefall(altitude)')
legend('Modeled Data','Real Data');
% v vs t 

 figure(9);
plot (T,M(:,2)*36/10); 
hold on; 
plot( A(:,1), -A(:,3) ); 
grid on;
xlabel ('time(s)');
ylabel ('speed(km/h)');
title ('part3 freefall(speed)')
legend('Modeled Data','Real Data');
%a vs t


figure(10)
plot(T(2:end) , axl,'g');
hold on;
plot(plotttime , plotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part3 freefall(accelation)')


%% Part 4
% Answer some questions here in these comments...
% What is the actual gravitational field strength around 39,000 meters? 
%   9.6864 m/s^2
%
% How sensitive is the altitude reached after 4.5 minutes to simpler and 
%   more complicated ways of modelling the gravitational field strength? 
% not much differant
%
% What other changes could we make to our model? Refer to, or at least 
%   attempt to explain, the physics behind any changes that you propose. 
% We can calculate the parashut air resitance to model the data so taht it
% matches the sample.
%
% What is a change that we could make to our model that would result in 
%   insignificant changes to the altitude reached after 4.5 minutes? 
% galculate the gravity of the moon and the sun on felix, and modeling the
% acceleration that way.
%
% How can we decide what change is significant and what change is 
%   insignificant?
% Sme thing that changes the graph in a neglegabile maneer is insignificant and 
% something that changes it drastically is significant.
%
% [What changes did you try out to improve the model?  (Show us your changes
%   even if they didn't make the improvement you hoped for.)]
% We calculated the change in the gravity when falling, but it did not have
% a noticible effect. 

part = 4;

start = [38969.4 10];
tspan =[0 t];
[T,M] = ode45(@fall, tspan,  start );


% y vs t

figure(11);
plot (T,M(:,1)); 

hold on;
plot( A(:,1), A(:,2)); 
grid on;
xlabel ('time(s)');
ylabel ('altitude(m)');
title ('part4 freefall(altitude)')
legend('Modeled Data','Real Data');
% v vs t 

 figure(12);
 
plot (T,M(:,2)*36/10); 
hold on; 
plot( A(:,1), -A(:,3) ); 
grid on;
xlabel ('time(s)');
ylabel ('speed(km/h)');
title ('part4 freefall(speed)')
legend('Modeled Data','Real Data');

%a vs t
 



axl= (diff(M(:,2)))./diff(T ); 



figure(13)
plot(T(2:end) , axl,'g');
hold on;
plot(plotttime , plotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part4 freefall(acceleration)')


%% Part 5
% Answer some questions here in these comments...
% At what altitude does Felix pull the ripcord to deploy his parachute? 
% 4 seconds
%
%
%   How safe or unsafe would such an acceleration be for Felix?
% Its safe because a person can hansle up to 9g's of accelaratiion before
% damage.

part = 5;




% Make a single acceleration-plot figure that includes, for each of the 
% model and the acceleration calculated from measurements, the moment when 
% the parachute opens and the following 10 or so seconds. If you have 
% trouble solving this version of the model, just plot the acceleration 
% calculated from measurements. 

start = [38969.4 10];
tspan =[0 t];
[T,M] = ode45(@fall, tspan,  start );

axl= (diff(M(:,2)))./diff(T ); 



figure(14)
plot(T(2:end) , axl,'g');
hold on;
plot(plotttime , plotaxl,'r');
grid on;
legend('Modeled Data','Real Data');
xlabel ('time(s)');
ylabel ('Acceleration(m/s^2)');
title ('part5 freefall(acceleration)');

%% Part 6 
% Answer some questions here in these comments...
% How long does it take for Felix’s parachute to open? 
% 4 seconds

part = 6;

% Redraw the acceleration figure from the previous Part but using the new 
%   model. Also, using your plotting function from Part 1, plot the 
%   measured/calculated data and the model for the entire jump from 
%   stratosphere to ground.
% <place your work here>
%% nested functions  
% nested functions below are required for the assignment.  
% see Appendix B of Physical Modeling in MATLAB for discussion of nested functions

function res = fall(t, X)
    %FALL This fuction takes three inputs of t,X(1), X(2) and outputs 
    % velocity and acceleration
    %   The velocity is equal to dy/dt and acceleration is equal to dv/st. 
    %  By using this two values in the ode45 function we can calculate the graph of 
    % y vs t and v vs t

    % do not modify this function unless required by you for some reason! 

    y = X(1); % the first element is position
    v = X(2); % the second element is velocity

    dydt = v; % velocity: the derivative of position w.r.t. time
    dvdt = acceleration(t, y, v); % acceleration: the derivative of velocity w.r.t. time

    res = [dydt; dvdt]; % pack the results in a column vector
end

function res = acceleration(t, y, v)
    % <insert description of function here>
    % input...
    %   t: time
    %   y: altitude
    %   v: velocity
    % output...
    %   res: acceleration

    % do not modify this function unless required by you for some reason! 

    grav = gravityEst(y); 

    if part == 1 % variable part is from workspace of function main.
        res = -grav;
    else
        m = mass(t, v);
        b = drag(t, y, v, m);

        f_drag = -b * v^2 * sign(v);
        a_drag = f_drag / m;
        res = -grav + a_drag;
    end
end



function grav = gravityEst(y)
    % estimate the acceleration due to gravity as a function of altitude, y
    g_SEA = 9.807;  % gravity at sea level in m/s^2

    if (part <4) 
        grav = g_SEA;
    else %the gravitational field of earth in a distance y of the surface
        grav = (6.674 *10^-11)*(5.972 *10^24) / (6378000+y)^2; 
    end                                                
end

function res = mass(t, v)
    % mass in kg of Felix and all his equipment
    res= 118; %kg
end

function res = drag( t, y, v, m)
% <insert description of function here>

    if part == 2
        res = 0.2;
    else
        % air resistance drag = 1/2*rho*c_d*a = 1/2*rho*CdA
        
       
[rho,a,temp,press,kvisc,ZorH]=stdatmo(y); % kg/m^3 -- fluid density vs y
c_d = 0.4;  % dimensionless -- drag coefficient

if (part==5 && t>258)
    a=4;    % m^2 -- cross-sectional area of the prachute        
           
else
    a = 1.2;  
end
drag = 1/2*rho*c_d*a; 

res= drag;
    end
end

%% Additional nested functions
% Nest any other functions below.  
%Do not put functions in other files when you submit, except you can use
%    the stdatmo function in file stdatmo.m which has been provided to you.

% end of nested functions
 % closes function main.  
 end