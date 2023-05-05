function [] = vecPlot3D(arg1,arg2,scale,color,origin)

quiver3(arg1(1),arg1(2),arg1(3),arg2(1),arg2(2),arg2(3),scale,color);
hold on 
if origin ~= 0
plot3(arg1(1),arg1(2),arg1(3),'o')
hold off
else
hold off
end
