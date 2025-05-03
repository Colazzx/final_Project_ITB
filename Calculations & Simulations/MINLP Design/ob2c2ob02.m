function [f]= ob2c2ob02(x,de,dda,cp,example)

switch example
case 1
    c   = [2 1 3];
    f   = (x(1)-3)^2+(x(2)-2)^2+c*x(3:5);
case 2
    c   = [1 1.5 0.5];
    f   = (c*x(3:5)+x(1)^2+x(2)^2);
case 3
    f = x(7);
case 4
    c   = [5 8 6 10 6 7 4 5];
    a   = [0 1 -10 1 -15 0 0 0 -40 15 0 0 0 15 0 0 80 -65 25 -60 35 -80 0 0 -35]; 
    f   = c*x(26:33)+a*x(1:25)+122;
end
   