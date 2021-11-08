% 피크를 이용해서 가중치 연산부분 자르기
function cutTrace = cutting(movingcorr,trace, trNum)
 
% 10 ^ 5 Scale
start = 1; % 시작 
end_ = 14500; % 끝

jump = 27000; % 다음 첫번째 피크로 이동거리
cut = 14500;  % 자르는 범위 
find = 4200;  % 최고 피크 찾는 범위 
num = 6; % 가중합 연산 개수 

cutTrace = zeros(cut*10,trNum,num);

% 가중합 연산부분 자르기 
for i = 1 : trNum
    st = start;
    ed = end_;
    
    for j = 1 : num
        % 최고 피크 찾아서 자르기
        [temp ,peakpoint] = max(movingcorr(ed - find : ed , i)); 
        peakpoint = peakpoint + ed - find - 1;
        %fprintf("%d ",peakpoint);
        if j == 1 
            len = length(trace(st : peakpoint*10 , i));            
            cutTrace(:,i,j) = vertcat( trace(st : peakpoint*10 , i), zeros(cut*10 - len,1) ); % 10 ^ 6 Scale
            fprintf("[%d]-(%d) : %d ~ %d \n",i,j,st,peakpoint*10);
        else
            st = peakpoint - cut;
            len = length(trace(st*10 : peakpoint*10 -   1 , i));
            cutTrace(:,i,j) = vertcat( trace(st*10 : peakpoint*10 - 1 , i), zeros(cut*10 - len,1) ) ; % 10 ^ 6 Scale
            fprintf("[%d]-(%d) : %d ~ %d \n",i,j,st*10,peakpoint*10);
        end
        ed = peakpoint + jump;
        
        % cutTrace(:,i,j) = trace(start*10 : end_*10,i); % 스케일 차이 극복 
        %cutTrace(:,i,j) = vertcat( trace(start*10 : end_*10,i) , zeros(cut*10 - length(trace(start*10:end_*10)),1)); % 스케일 차이 극복 
    end
    %fprintf("\n");
end

% figure;
% plot(cutTrace(:,1,1));


 end
