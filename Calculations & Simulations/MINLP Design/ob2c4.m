%clc,clear,
warning off

plfig = '';

disp(' ')
disp('    Caleb & Hansen')
disp('    Water Filtering using Chitosan Adsorbent')
disp('    Checked by EE')
disp('    May 2024')


time = fix(clock);
tic
fprintf('    Start time : %i/%i/%i , %i:%i:%i\n\n',time(3),time(2),time(1),time(4),time(5),time(6));

tspan = [0 3600];
itk = 1;
Names = {'N1' 'Fp1' 'N2' 'Fp2'};


fprintf('iteration %g\n',itk);
disp('outer loop')

options = optimset('Display','off','Bdisplay',1);

x0o  = [200 50  200 50  5   1     1     1     1     1    0     ]';
%x0o = [N1  Fp1 N2  Fp2 Fl  y1    y2    y3    y4    y5   Profit]
set  = {[], [], [], [],[], [0 1],[0 1],[0 1],[0 1],[0 1],[]};
 
d2n  = [200];

A   = [];   b   = [];   Aeq = [];   beq = [];
vlb = [-inf -inf -inf -inf -inf  0 0 0 0 0 -inf]';
vub = [ inf  inf  inf  inf  inf  1 1 1 1 1  inf]';
intidx = [ 6 7 8 9 10 ]';
[xol(:,itk),olf(:,itk),~,~,~,~,~,il]=fminconsete5('ob2c2ob04',x0o,intidx,[],A,b,Aeq,beq,vlb,vub,'ob2c2nlc004','ob2c2nlc014',options,set,inf,0,[],[],[],d2n);
fprintf('\tN1  = %0.3f, N2  = %0.3f \n',xol(1,itk),xol(3,itk));
fprintf('\tFp1 = %0.3f, Fp2 = %0.3f, Fl = %0.3f, Objective function = %g \n',xol(2,itk),xol(4,itk),xol(5,itk),abs(xol(11,itk)));
fprintf('\ty1  = %0.3f, y2 = %0.3f, y3 = %0.3f, y4 = %0.3f, y5 = %0.3f\n',xol(6,itk),xol(7,itk),xol(8,itk),xol(9,itk),xol(10,itk));

disp('inner loop')
	%Determining EDS 
    %EDS
    [uu,de] = makeeds([d2n],{0.75:0.5:1.25});
    %DOS
    %    [N1  Fp1 N2  Fp2]
    ub = [200 90  200 90];
    lb = [100 40  100 40];

	mu=size(de,2);
    outputs1 = []; outputs2 = []; 
         if xol(6,itk)==0
             outidx1  = [1 2 3 4];outidx2 = [1 2 3 4 5];
             ub = [200 90  200 90];
             lb = [100 40  100 40];
         else
             outidx1  = [1 2 ];outidx2 = [1 2 5];
             ub = [200 90  ];
             lb = [100 40  ];
         end
    for i=1:mu
        xd  = de(:,i)'; 
   	    [tt,xx]=oib2c2fg4_cl(xol(:,itk),xd,tspan);
        outputs1 = [outputs1; xx(end,outidx1)];
        outputs2 = [outputs2; xx(end-10:end,outidx2) repmat(xd,length(tt(end-10:end)),1) tt(end-10:end)];
    end
        
    [no,mo] = size(outputs1);   [n1,m1] = size(outputs2);   [nd,md] = size(xd);
       
    %PCA test
    [cp,pair,PC,ff] = pcatest1(outputs1,xx(1,outidx1),lb,ub);

    disp('Groups')
	[np,~]=size(pair);
	for k=1:np
        [i,j] = find(pair(k,:)~=0);
        disp(Names(pair(k,j)));    
	end
	
	disp('Functional variables')
	[np,mp]=size(cp);
	for k=1:np
        disp(Names(cp(k)));    
	end 
    %end of PCA test

  %detecting critical disturbances 
  [ddi1,ddi2] = cddetect(outputs2,de,cp);
  disp('Disturbance combination found in AOS by qhull');
  disp(ddi2);
  
  switch plfig
  case 'plotfigure'
      %plotting disturbance combinations
      figure(itk*100+1)
      plot(de(1,:),'ro',ddi1(1,:),'bx',ddi2(1,:),'yv');
      xlabel(Names(cp));title('Critical disturbance combination');
      axis([150 250]);
  end
  
  %computing rOCI 
  %computing generalized volume vol2  
  [k2,vol2] = chullne(outputs2(:,cp),ff);
  %computing generalized volume vol3
  [ck3,vol3] = qhalfne4(outputs2(:,cp),lb(cp),ub(cp),ff);
  rOCI(itk) = vol3/vol2;
  %other indices
  fprintf('Flexibility index = %g\n',rOCI(itk)); 
  fprintf('GAE = %g $\n',vol2); 
  [~,vol5] = chullne(outputs2(:,[cp;m1]),[]);
  fprintf('GIAE = %g $\n',vol5); 
  [y,vol4] = chullne(outputs2(:,[mo+1 m1]),[]);
  fprintf('Profit variation = %g $second\n\n\n',vol4); 

  itk=itk+1;
  
  %----------------End of Inner Loop  
  dda=ddi2;

 while or(~ismember(ddi2',dda','rows'),itk==2)
 %while (rOCI(itk-1)<1)
     dda = unique([dda ddi2]','rows')';
     fprintf('iteration %g\n',itk);
     disp('outer loop')
 
     A   = [];   b   = [];   Aeq = [];   beq = [];
     options = optimset('Display','off','Bdisplay',1);
     intidx = [ 6 7 8 9 10 ]';
     [xol(:,itk),olf(:,itk),~,~,~,~,~,il]=fminconsete5('ob2c2ob14',xol(:,1),intidx,[],A,b,Aeq,beq,vlb,vub,'ob2c2nlc104','ob2c2nlc114',options,set,inf,0,de,dda,cp,tspan,d2n);
     fprintf('\tN1  = %0.3f, N2  = %0.3f \n',xol(1,itk),xol(3,itk));
     fprintf('\tFp1 = %0.3f, Fp2 = %0.3f, Fl = %0.3f, Objective function = %g \n',xol(2,itk),xol(4,itk),xol(5,itk),abs(xol(11,itk)));
     fprintf('\ty1  = %0.3f, y2 = %0.3f, y3 = %0.3f, y4 = %0.3f, y5 = %0.3f\n',xol(6,itk),xol(7,itk),xol(8,itk),xol(9,itk),xol(10,itk));
 
 	disp('inner loop')
 		%Determining EDS 
         %EDS
         [uu,de] = makeeds([d2n],{0.75:0.5:1.25});
         %DOS
         %    [N1  Fp1 N2  Fp2]
         ub = [200 90  200 90];
         lb = [100 40  100 40];
 
         mu=size(de,2);
         outputs1 = []; outputs2 = []; 
         if xol(6,itk)==0
             outidx1  = [1 2 3 4];outidx2 = [1 2 3 4 5];
             ub = [200 90  200 90];
             lb = [100 40  100 40];
         else
             outidx1  = [1 2 ];outidx2 = [1 2 5];
             ub = [200 90 ];
             lb = [100 40 ];
         end
         for i=1:mu
             xd  = de(:,i)';
        	    [tt,xx]=oib2c2fg4_cl(xol(:,itk),xd,tspan);
             outputs1 = [outputs1; xx(end,outidx1)];
             outputs2 = [outputs2; xx(end-10:end,outidx2) repmat(xd,length(tt(end-10:end)),1) tt(end-10:end)];
         end

        [no,mo] = size(outputs1);   [n1,m1] = size(outputs2);   [nd,md] = size(xd);

        %PCA test
        [cp,pair,PC,ff] = pcatest1(outputs1,xx(1,outidx1),lb,ub);

        disp('Groups')
		[np,~]=size(pair);
		for k=1:np
            [i,j] = find(pair(k,:)~=0);
            disp(Names(pair(k,j)));    
		end

		disp('Functional variables')
		[np,mp]=size(cp);
		for k=1:np
            disp(Names(cp(k)));    
		end 
        %end of PCA test

      %detecting critical disturbances 
      [ddi1,ddi2] = cddetect(outputs2,de,cp);
      disp('Disturbance combination found in AOS by qhull');
      disp(ddi2);

      switch plfig
      case 'plotfigure'
          %plotting disturbance combinations
          figure(itk*100+1)
          plot(de(1,:),de(2,:),'ro',ddi1(1,:),ddi1(2,:),'bx',ddi2(1,:),ddi2(2,:),'yv');
          xlabel('Tf');ylabel('Cf');title('Critical disturbance combination');
          axis([298 315 19.5 21]);
      end

      %computing rOCI 
      %computing generalized volume vol2  
      [k2,vol2] = chullne(outputs2(:,cp),ff);
      %computing generalized volume vol3
      [ck3,vol3] = qhalfne4(outputs2(:,cp),lb(cp),ub(cp),ff);
      rOCI(itk) = vol3/vol2;
      fprintf('Flexibility index = %g\n',rOCI(itk)); 
      %other indices
      fprintf('GAE = %g $\n',vol2); 
      [~,vol5] = chullne(outputs2(:,[cp;m1]),[]);
      fprintf('GIAE = %g $\n',vol5); 
      [y,vol4] = chullne(outputs2(:,[mo+1 m1]),[]);
      fprintf('Profit variation = %g $second\n',vol4); 

      % itk=itk+1;
      itk = 1;

      %----------------End of Inner Loop  
      dda=ddi2;

end

%---------------------------------------------
time = fix(clock);
fprintf('Finish time : %i/%i/%i , %i:%i:%i\n\n',time(3),time(2),time(1),time(4),time(5),time(6));
fprintf('CPU time : %g minutes\n',toc/60);

