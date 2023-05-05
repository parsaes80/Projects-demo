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
lt(1)= (10^-2)*input("what the location of the test charge on x-axis?");
lt(2)= (10^-2)*input("what the location of the test charge on y-axis?");
lt(3)= (10^-2)*input("what the location of the test charge on z-axis?");
qt= input("what the magnitude of the test charge in nC?");
e= zeros(n,3);

for k= 1:n
e(k,1)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(1)-l(k,1));
e(k,2)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(2)-l(k,2));
e(k,3)= (9 *q(k) / (vectorMag(lt-l(k,:))^3))*(lt(3)-l(k,3));
end
f=(qt*10^-9) .*e;

et = [sum(e(:,1)),sum(e(:,2)), sum(e(:,3))];
ft= (qt*10^-9)*et;

disp(["total force magnitude: ", norm(ft)])
disp(["x-axis",ft(1)])
disp(["y-axis",ft(2)])
disp(["z-axis",ft(3)])
for k=1:n
vecPlot3D(lt,f(k,:),100,"blue",0)
hold on 
end

vecPlot3D(lt,ft,100,"red",1)
hold on
