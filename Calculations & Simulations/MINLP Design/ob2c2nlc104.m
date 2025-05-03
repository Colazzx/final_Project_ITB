function [C,Ceq,cp]= ob2c2nlc104(x,de,dda,cp,tspan,d2n)

 % x  = [200 50  200 50  5   0   0   0   0   0   100]';
 % x  = [N1  Fp1 N2  Fp2 Fl  y1  y2  y3  y4  y5  Profit]
 %       1   2   3   4   5   6   7   8   9   10  11
 % d2 = [Nl]
 
 % Karakteristik sistem open loop
 K   = [2.28  2.67  3.31];
 Tau = [1369.3  1331.4  2155.9];

 %Tank1
 ab1    = round(x(7)+x(8)+1);

 Ceq(1) = (K(ab1)*x(2)-x(1))/Tau(ab1);

 %Tank2
 ab2    = round(x(9)+x(10)+1);

 Ceq(2) = (K(ab2)*x(4)-x(3))/Tau(ab2);
 
 %Profit variation
 Ceq(3) = x(11)+0.4*x(5)*(d2n-(1-x(6))*x(1)-x(6)*x(3))-2*(x(2)+x(4))-(ab1+ab2);

C = [x(1)-200; 
     100-x(1);
     x(2)-90; 
     40-x(2);
     x(3)-x(6)*200; 
     x(6)*100-x(3);
     x(4)-x(6)*90;
     x(6)*40-x(4);
     x(5)-0.1*x(2);
     x(1)-0.9*d2n;
     x(3)-0.9*x(6)*x(1);

  
     x(8)-x(6);
     x(9)-x(6);
];


    ub = [200 90  200 90];
    lb = [100 40  100 40];
    outputs1 = [];              outputs2 = [];
    if abs(x(6))<=1e-4
       outidx1  = [1 2 3 4];outidx2 = [1 2 3 4 5];
       ub = [200 90  200 90];
       lb = [100 40  100 40];
    else
       outidx1  = [1 2 ];outidx2 = [1 2 5];
       ub = [200 90  ];
       lb = [100 40  ];
    end

    for i = 1:size(de,2)
		[tt,xx]=oib2c2fg4(x,de(:,i),tspan);
        %outputs1 = [outputs1; xx(end,outidx1)];
        outputs2 = [outputs2; xx(end-10:end,outidx1)];
    end
   
    if abs(x(6))<=1e-4
        C   = [C; max(outputs2-ub(ones(size(outputs2,1),1),:))'];
    else
        C   = [C; max(outputs2-ub(ones(size(outputs2,1),1),:))';0;0];
    end 