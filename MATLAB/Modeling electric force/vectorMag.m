function [output]= vectorMag(input)

siz =size (input);
if (siz(1)==1 ) || (siz(2)==1)

output = norm (input);
else 
    fprintf("the input is not a coloum or row vector")
    output=0;
end 

end