% [ Moving corr ] : 밀면서 상관계수 구하기 + 최적화
 function corr = movingcorr2(standard , trace, trNum) % Matlab ( 기준파형 | 대상파형 ) | 개수 

startpoint = 1; % 대상파형 시작 지점 
num = 100;%length(standard); % 커팅한 파형의 개수 ( < trNum ) 

% 기준파형을 밀면서 상관계수 구하기
for i = 1 : trNum 
    
    range = (length(trace(:,i)) - length(standard)) - startpoint; 
    
    for j = startpoint : ( startpoint + range )
        for k = 1 : num
            cut(:,k) = trace( (j-1)*num + k : (j-1)*num + length(standard) + k - 1);
        end
        
        % correalation coefficient
        temp = corrcoef(standard , cut);
        corrtrace( (j-1)*num + 1 : j*num ) = temp(1,:);
        
        if mod(j, 100) == 0
            j
        end
    end
end

figure;
plot(corr(:,1));


end
