function [C,cp1,ddi2]= ob2c2nlc114(x,de,dda,cp,tspan,d2n)

C   = [x(8)-x(6);
       x(9)-x(6);
       ];


%    [N1  Fp1 N2  Fp2]
ub = [250 90  250 90];
lb = [100 40  100 40];
outputs1 = [];              outputs2 = []; 
if abs(x(6))<=1e-4
    outidx1  = [1 2 3 4];outidx2 = [1 2 3 4 5];
    ub = [250 90  250 90];
    lb = [100 40  100 40];
else
    outidx1  = [1 2 ];outidx2 = [1 2 5]
    ub = [250 90  ];
    lb = [100 40  ];
end

for i = 1:size(de,2)
     %ith Disturbance Set
	[tt,xx]=oib2c2fg4(x,de(:,i),tspan);
    outputs1 = [outputs1; xx(end,outidx1)];
    outputs2 = [outputs2; xx(end-10:end,outidx2) repmat(de(:,i)',length(tt(end-10:end)),1) tt(end-10:end)];
end


[no,mo] = size(outputs1);   
cp1 = pcatest1(outputs1,xx(1,outidx1),lb,ub);
if cp1 == []; cp1 = 1; end
[ddi1,ddi2] = cddetect(outputs2,de,cp1);

