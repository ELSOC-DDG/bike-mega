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
%snew=instrfind;
%fclose(snew);

obj = serial('COM9')
fopen(obj)

buffer = zeros(1000,4);

scores = cell([10 2]);
scores(1:10, 1:1) = {0};
scores(1:10, 2:2) = {''};

while(1)
    
	% update the buffer
    while(obj.BytesAvailable > 50)

        [s,count,msg] = fgets(obj);

        A = sscanf(s,'%f,%f,%f,%f');
        
        if(length(A) == 4)
            if (A(4)/100 == 1)
                % shift buffer
                buffer = circshift(buffer,1);
                % update buffer
                buffer(1,1) = A(1)/1000;
                buffer(1,2) = A(2)/100;
                buffer(1,3) = A(3)/100;
                buffer(1,4) = A(4)/100;
                
                % plot buffer
                figure(1);%trend
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
            elseif (A(4)/100 == 2) 
                disp('NO GO!');
                % competition mode is over, get score as calculated by
                % arduino
                score = A(1);
                disp(score);
                if (score > scores{10, 1})
                    user = input('Please enter your name: ', 's');
                    temp = cell([11 2]);
                    temp(1:10, 1:2) = scores(1:10, 1:2);
                    temp{11,1} = score;
                    temp{11,2} = user;
                    temp
                    temp = sortrows(temp, -1)
                    scores(1:10, 1:2) = temp(1:10, 1:2);
                    scores
                end
                
                for k = 1:10
                    string = sprintf('%d. %s - %d', k, scores{k, 2},  scores{k, 1});
                    %string = sprintf('%d. %s - %d', k, 'kkk',  22);
                    figure(2);%score
                    t = uicontrol(2,'Style','text','String',string,'Position',[100 (600-60*k) 500 60]);
                    set(t,'FontSize',36,'Fontname','Helvetica','Fontweight','bold');
                end
                
            end
        end
    end
        
end
  
  fclose(obj);

