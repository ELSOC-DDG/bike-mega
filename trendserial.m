%{
t = 0 ;
x = 0 ;
startSpot = 0;
interv = 1000 ; % considering 1000 samples
step = 0.1 ; % lowering step has a number of cycles and then acquire more data
while ( t <interv )
    b = sin(t)+5;
    x = [ x, b ];
    plot(x) ;
      if ((t/step)-500 < 0)
          startSpot = 0;
      else
          startSpot = (t/step)-500;
      end
      axis([ startSpot, (t/step+50), 0 , 10 ]);
      grid
      t = t + step;
      drawnow;
      pause(0.01)
  end
%}

snew=instrfind;
%fclose(snew);

obj = serial('COM3')
fopen(obj)

buffer = zeros(1000,4);



while(1)
    
  % update the buffer
  while(obj.BytesAvailable > 50)
        
  [s,count,msg] = fgets(obj);
      
  A = sscanf(s,'%f,%f,%f,%f');
    
 if(length(A) == 4)

   % shift buffer
   buffer = circshift(buffer,1);
   % update buffer
   buffer(1,1) = A(1)/1000;
   buffer(1,2) = A(2)/100;
   buffer(1,3) = A(3)/100;
   buffer(1,4) = A(4)/100;
 end
  end   

    
    
        
% plot buffer
plot(buffer(:,1),buffer(:,2));
hold on
plot(buffer(:,1),buffer(:,3));
hold on
plot(buffer(:,1),buffer(:,4));
hold off
legend('Voltage (V)','Current (A)','Output');
xlabel('Time (seconds)');
title('Bike Output');  
axis([ buffer(1)-10, buffer(1), 0 , 40]);
grid
            
drawnow;
pause(0.01)
        
end
  
  fclose(obj);

