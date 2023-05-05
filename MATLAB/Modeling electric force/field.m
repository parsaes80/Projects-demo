clear
n = input( "what the number of source charges?");
l=zeros(n,3);
q=zeros(n,1);
for k=1:n 
    l(k,1)= (10^-2)* input("what the location of the charge on x-axis?");
    l(k,2)= (10^-2)*input("what the location of the charge on y-axis?");
    l(k,3)= (10^-2)*input("what the location of the charge on z-axis?");
    q(k,1)= (10^-2)*input("what the magnitude of the charge in nC?");
end 

lt=zeros(1,3);
lt(1)= (10^-2)*input("what the location of the test position on x-axis?");
lt(2)= (10^-2)*input("what the location of the test position on y-axis?");
lt(3)= (10^-2)*input("what the location of the test position on z-axis?");

e= zeros(n,3);

for k= 1:n
e(k,1)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(1)-l(k,1));
e(k,2)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(2)-l(k,2));
e(k,3)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(3)-l(k,3));
end

et = [sum(e(:,1)),sum(e(:,2)), sum(e(:,3))];

disp(["total field magnitude: ", norm(et)])
disp(["x-axis",et(1)])
disp(["y-axis",et(2)])
disp(["z-axis",et(3)])
for k=1:n
vecPlot3D(lt,e(k,:),1,"blue",0)
hold on 
end

vecPlot3D(lt,et,1,"red",1)
hold off
