%% 1
clear
format long
xp= [0.9 1.3 1.9 2.1 2.6 3.0 3.9 4.4 4.7 5.0 6.0 7.0 8.0 9.2 10.5 11.3 11.6 12.0 12.6 13.0 13.3 ];
%yp= [1.3 1.5 1.85 2.1 2.6 2.7 2.4 2.15 2.05 2.1 2.25 2.3 2.25 1.95 1.4 0.9 0.7 0.6 0.5 0.4 0.25];
yp= sin(xp.*xp);
syms y [1 length(xp)]
syms x
syms interp
s=1;

for n=14

for i= s:n
   y(i)=1;
   for j= s:n
       if (j ~= i)
       y(i)= y(i) * (x-xp(j))/(xp(i)-xp(j));
       end
   end
end

interp = 0;

for i= s:n 
   interp = interp + yp(i)*y(i);
end
disp(interp);
fplot(interp,[0 15])
hold on;
end
%plot([0.9 1.3 1.9],[1.3 1.5 1.85], '-.or')
xlabel("x")
ylabel("Interpolation")
legend( 'N=2','N=3','N=4','N=5','N=6','N=7','N=8','N=9', 'location','northeast');
plot(xp,yp, '-.o')
axis([2.58 ,5.1 ,2 ,2.8] );
saveas(gcf,'3.png')
