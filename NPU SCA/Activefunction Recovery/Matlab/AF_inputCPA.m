% [ 활성함수 입력 CPA ] : 정렬 맞은 상태 가정 
function corr = AF_inputCPA(trace) % 파일 이름 넘겨주기 ( "tanh_input" / tanh_trace ) 

% 입력 CPA 
trNum = 1000;   % Setting %
trLen = 24000; % Setting % 

inputy2 = linspace(-5, 5, 1000);
inputy  = uint32(inputy2);
% 입력층의 입력 추출 
%inputFile = fopen(FN +"_textout.npy",'r');
%fseek(inputFile,128,'bof');

for i=1 : trNum
    %tmp = fread(inputFile, 3,'float'); % 건너뛰기 
    %input(:,i) = fread(inputy, 1,'uint32'); % input(1) 
    %fprintf("%x \n" ,input(1,i)); % 입력값 확인
    HW(1,i) = sum(dec2bin(inputy(1,i)).' == '1'); % 활성함수 입력값의 헤밍웨이트
end

%fclose(inputFile);

%{
% 파형 로딩 
traceFile = fopen(FN +"_traces.npy",'r');
fseek(traceFile,128,'bof');
for i=1 : trNum
    trace(:,i)=fread(traceFile, trLen,'double');
end
fclose(traceFile);
%}

% CPA 
for j = 1 : trLen
    %temp = corrcoef(HW(1,:) , trace(j,:));
    temp = corrcoef(HW(1,:), trace(j,:));
    corr(j) = temp(1,2);
end

    [maxcorr,index] = max(abs(corr(:)));
    fprintf("첫번째 활성함수 : %f at  %d point \n",maxcorr,index);

figure;
plot(corr(:));

end