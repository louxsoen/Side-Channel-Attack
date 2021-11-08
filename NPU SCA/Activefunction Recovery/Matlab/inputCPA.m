function corr = inputCPA(FN,trace) % 파일 이름 넘겨주기 ( tanh_input ) 

% 입력 CPA 
trNum = 1000;   % Setting %
trLen = 24000; % Setting %
inputNum = 3; % Setting %


% 입력층의 입력 추출 
inputFile = fopen(FN +"_textout.npy",'r');
fseek(inputFile,128,'bof');

for i=1 : trNum
    input(:,i) = fread(inputFile, 3,'uint32'); % input(1~3) 
    tmp = fread(inputFile,1,'float'); % 건너뛰기 
    
    % fprintf("%x %x %x \n" ,input(1,i),input(2,i),input(3,i)); 입력값 확인 
    HW(1,i) = sum(dec2bin(input(1,i)).' == '1'); % 첫번째 노드 값의 헤밍웨이트
    HW(2,i) = sum(dec2bin(input(2,i)).' == '1'); % 두번째 노드 값의 헤밍웨이트
    HW(3,i) = sum(dec2bin(input(3,i)).' == '1'); % 세번째 노드 값의 헤밍웨이트
end

fclose(inputFile);

%{
% 파형 로딩 
traceFile = fopen(FN +"_traces.npy",'r');
fseek(traceFile,128,'bof');

for i=1 : trNum
    trace(:,i)=fread(traceFile, trLen,'double');
end

fclose(traceFile);
%}

% CPA T
for j = 1 : trLen
    temp = corrcoef(HW(1,:) , trace(j,:));
    corr(j,1) = temp(1,2);
    
    temp = corrcoef(HW(2,:) , trace(j,:));
    corr(j,2) = temp(1,2);
    
    temp = corrcoef(HW(3,:) , trace(j,:));
    corr(j,3) = temp(1,2);
end

for i = 1 : inputNum
    [maxcorr,index] = max(abs(corr(:,i)));
    fprintf("%d번째 노드 : %f at  %d point \n",i ,maxcorr,index);
end

plot(corr(:,1));
% hold on
% plot(corr(:,2));
% plot(corr(:,3));

end
