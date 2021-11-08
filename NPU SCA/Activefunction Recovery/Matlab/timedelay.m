function time = timedelay(inputcorr , movecorr,trNum,FN)

% 2개의 상관계수 파형을 이용하여 연산시간 측정 

for i = 1 : trNum
  [maxcorr,front] = max(abs(inputcorr(:,1)));
  [maxcorr,back] = max(movecorr(:,i));
  
   Y(i) = (back - front);
   %fprintf("%d ",Y(i));
end


% 활성함수 입력값 로딩

inputFile = fopen(FN,'r');
fseek(inputFile,128,'bof');

%fprintf("\n");

for i=1 : trNum
    temp = fread(inputFile, 3, 'float');
    X(i) = fread(inputFile, 1, 'float');
    %fprintf("%d ",X(i));
end

%fprintf("\n");

% X,Y값 1개의 배열로 합치기 
time = [X; Y];


% 그래프 그리기 
scatter(X,Y+7133,'filled');
xlabel('input');
ylabel('timedelay');
title('sigmoid 함수');
grid on



end 
