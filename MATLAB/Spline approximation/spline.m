
clear
clc 

format long
h= @(m) 2^ (-m);
f=@(x) exp(-x);
vals=zeros(1,4);
for m= [2 3 4 5]
x= 0:h(m):1;
y= exp(-x);

% "non a-knot vs. end slope:
 %yy= spline(x,y); % not a-knot
 yy= spline(x,[-1, y, -1/exp(1)]); % clamped
clear x p
% hold on
syms x
syms p [1  2^m] 
s2 = 0;
for i=1:2^m 
p(i)= yy.coefs(i,:) * [(x- (i-1)*h(m))^3; (x- (i-1)*h(m))^2 ;x- (i-1)*h(m); 1 ];
s2 = int(p(i),[(i-1)*h(m) i*h(m)])+s2;
%fplot(p(i),[(i-1)*h(m) i*h(m)])
end
s = vpa( integral (f,0,1),50);
disp(h(m))
disp(vpa(abs((s2-s)),50))
vals(m-1)=(vpa(abs((s2-s)),50));
end
 %plot([2 3 4 5],vals)
%  plot([ h(2) h(3) h(4) h(5)],(vals),'ro')

plot(log10([ h(2) h(3) h(4) h(5)]),log10(vals),'ro')
xlabel('log(h)');
ylabel('log(error)');
 hold on
 
%axis([0  0.256 0  3.64*10^-5] )
hold off