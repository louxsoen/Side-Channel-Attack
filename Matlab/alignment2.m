% [ Cutting 파형 정렬 ]
function atrace = alignment2(cutTrace,trNum)  % 원본파형.mat | 파형개수

% Setting
windowsize = 40; % 40 100
stepsize = 30;  % 30 80
threshold = 10; % 10 20

num = 6; % 가중합 연산 개수 
trLen = length(cutTrace(:,1,1)); % Cutting 파형 길이 


% 기준파형 
for i = 1 : num
    atrace(:,1,i) =  cutTrace(:,1,i); 
end


% 정렬 함수 호출 
for j = 1 : num
    for i = 2 :trNum
        atrace(:,i,j) = subalignment(cutTrace(:,1,j),cutTrace(:,i,j),windowsize,stepsize,threshold,trLen);
    end
end



end

% 정렬 알고리즘 ( Matlab 정렬코드 인덱싱 수정 필요 )
function data2 = subalignment(data1, data2, windowsize, stepsize,threshold,trLen)

for i = 1 : stepsize : trLen - windowsize % + 1  % stepsize만큼 i 증가 ( +1 제거 필요 )
    maxcovpos = 0;
    maxcov = 0;
    
    for j= - threshold : threshold
        if j < 0
            size = windowsize - abs(j);
            x = data1(i : i + size);
            y = data2(i - j: i - j + size);  %%
        else
            size = windowsize - abs(j);
            x = data1(i + j : i + j + size);
            y = data2(i : i + size);  %%
            
        end
        % cov = xcorr(x,y);
        temp = corrcoef(x,y); %% 
        cov = temp(1,2);
        
        if cov > maxcov
            maxcovpos = j;
            maxcov = cov;
        end
    end
    
    if maxcovpos < 0
        for k = i : trLen + maxcovpos
            data2(k) = data2(k - maxcovpos);
        end
    else
        for k = trLen - maxcovpos - 1 : -1 : i  %%
            data2( k + maxcovpos ) = data2(k);
        end
    end
    %align = data2;
end

end
