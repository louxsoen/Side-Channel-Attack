% [ 파형 정렬 ]
function atrace = alignment(trace,trNum)  % 원본파형.mat | 파형개수

% Setting
windowsize = 40;
stepsize = 30;
threshold = 10;

% data1 = trace(:,1); 
atrace(:,1) =  trace(:,1); % 기준파형 
trLen = length(trace(:,1)); % 파형길이 

% 정렬 함수 호출 
for i = 2 :trNum
    atrace(:,i) = subalignment(trace(:,1),trace(:,i),windowsize,stepsize,threshold,trLen);
    %data2 = trace(:,i);
    %atrace(:,i) = subalignment(data1,data2,windowsize,stepsize,threshold,trLen);
end



end

% 정렬 알고리즘 
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
