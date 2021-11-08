% [ Moving corr ] : 파일 읽어서 밀면서 상관계수 구하기 + 최적화 
function z = movingcorr3(FN,trNum)

% 파일 읽기 
fid = fopen(FN,'r');

for k = 1 : trNum
    len = fread(fid,1,'uint32');
    z = fread(fid,len,'double');

% 기준파형을 밀면서 상관계수 구하기
for i = startindex : ( startindex + trNum - 1 )
    
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

    
end

figure;
plot(z);


end
