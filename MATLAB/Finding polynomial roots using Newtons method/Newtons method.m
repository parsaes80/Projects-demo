clear
clc
syms a;
syms L;
format long;
f = @(x) x^4  -x^3;
di = @(x) 4* x^3 -3*x^2;
%% first initial guess being 1.1
p=1.1;

v2= zeros (1,10);

for  k =1:10 
  pn= vpa(p- (f(p)/di(p)) , 100);
  disp(p);
  a = log((abs(pn-1))/L)/log(abs(p-1));
  if k>1 
  fplot (a);
  end
  hold on
  p= pn;
end 



%%
fprintf('\n----------------------\n')
%% second initial guess being 0.1
p=0.1;

for  k =1:100 
 
    p= vpa(p- (f(p)/di(p)) , 100);
    disp(p);
    v2(k)= vpa(p,100);
end 

%% function for alpha
% alpha for initial guess 0.1

for k = 1:9
    PN = v2(k);
    PN1 = v2(k+1);
    
   a = log((abs(PN1))/L)/log(abs(PN));
    fplot (a);
    hold on
end
plot(0.657474,0.997756,"o");
plot(2.89,1.99552,"o");
xlabel("λ");
ylabel("α");
saveas(gcf,'Barchart.png')