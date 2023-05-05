%% a)
%Lets make the matrix A and vector P
v1= ones(1,25);
v2= (-0.5)*ones(1,24);

L=diag(v2,-1) + diag(v1,0); %L has the diagonal enteries too
U=diag(v2,1);
A= L+U; 

B= [0.5,zeros(1,24)]';
pr= A\B; %exact value of the answer
p = zeros(25,1); %initial guess

%The iteration of gauess sidel methid in the for loop

for k=1:1000 
p = L\(B-(U*p));
if k==10 || k==100 || k==1000
    plot(p);
end

hold on
end
legend("k=1000","k=100","k=10")
xlabel("index")
ylabel("value")
hold off
%% b)

%create general nxn matrix with the wanted qualities
for n=2:100
v1= ones(1,n);
v2= (-0.5)*ones(1,n-1);

L=diag(v2,-1) + diag(v1,0);
U=diag(v2,1);
A= L+U;

B= [0.5,zeros(1,n-1)]';
pr= A\B;
p = zeros(n,1);%initial guess
normr= norm(pr); %exact value of the norm
norma= norm(p); 
num =0;
while abs((normr-norma)/normr)> (10^-3) 

p = L\(B-(U*p));
norma = norm(p);
num=num+1;
end
  plot(n,num,'-o');
  hold on;
end
xlabel("n")
ylabel("number of oporations")
clear
%% c)
% from the plot we have two main posibilites, either a logarithmic function
% or a radical function. If it's O(n^1/2) then n= C * sqrt(num) where C 
% is a the same constant for all data points. Same hold for O(log(n)), 
% n= C* log(num). We can run the code so that we check wheather C is
% constant for radical or Logarithm. When we run the code it shows that C is
% constant not for log but for the square root of n at around 0.816, which
% shows the n plot roughly has the function  n = 0.816 * sqrt(num). So what
% is the reason that big O= O(n^1/2)? If we take a look at a we find out
% that its a symetric posetive definate matrix. For this kind of matrix, we
% arrive at the answer quadradically, so the number of oporations rises
% inverse to quaradic which is square root, and thats what we see on the
% data.











