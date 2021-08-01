N=19922; % size of the Monte Carlo study with alpha 0.02 and error 0.008
p=0.62;  % given probability of the simulation

TotalWeight=zeros(N,1); % total weight of the chunks for every trial

littleN=250;

for k=1:N;
    i=0;
    for deneme=1:littleN; % this loop counts the accepted trials
        U = rand;
        if p >= U
            i=i+1;
        end
    end;
    accepted=i;

        
        
    weight=0;   % total weight for this week
    for product=1:accepted;
        X=0;
        Y=0.22;     % started like that to make sure while loop starts
        NORMAL=0;   
        
        while (Y>NORMAL);
            U=rand;
            X=8*U;
            Y=0.22*rand;

            if X <=2
                NORMAL=0.07*X;
            elseif X<=5
                NORMAL=-0.02*((X-4)^2)+0.22;
            elseif X<=7
                NORMAL=0.08*(5-X)+0.2;
            else
                NORMAL=-0.04*X+0.32;
            end
        end;

        weight=weight+X;
    end;
    TotalWeight(k) = weight;


    
    
    







end;

p_est = mean(TotalWeight>640);
expectedWeight = mean(TotalWeight);
stdWeight = std(TotalWeight);
fprintf('Estimated probability = %f\n',p_est);
fprintf('Expected weight = %f\n',expectedWeight);
fprintf('Standard deviation = %f\n',stdWeight);