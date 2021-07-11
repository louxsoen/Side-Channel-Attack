function corr = timedelay(standard , trace, trNum)

startindex = 1; % 1 | 27
startpoint = 1; % [ 1 ~ ( length(trace(:,i)) - length(standard) )]  1271000

% 기준파형을 밀면서 상관계수 구하기
for i = startindex : ( startindex + trNum )
    
    range = (length(trace(:,i)) - length(standard)); % [ 1 ~ ( length(trace(:,i)) - length(standard) ) ]
    
    for j = startpoint : ( startpoint + range - 1 )
        
        % correalation coefficient
        temp = corrcoef(standard , trace(j:length(standard) + j - 1 ,i));
        corr(j,i) = temp(1,2);
        
        % cross correlation
%         temp = xcorr(standard , trace(j:length(standard)+j - 1 ,i));
%         corr(j,i) = temp(1,1);
    end
    
end

plot(corr(:,startindex));

% 상관계수 파형을 이용하여 연산시간 측정 





end
