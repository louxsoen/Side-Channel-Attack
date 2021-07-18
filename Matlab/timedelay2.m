% [ 활성함수 입력CPA + movingCPA파형으로 연산시간 측정 ] : 피크 2개인 movingCPA 결과 이용 
function time = timedelay2(inputcorr , movecorr,trNum,FN)

for i = 1 : trNum
  [maxcorr,front] = max(abs(inputcorr(:)));
  [maxcorr,index] = maxk(movecorr(1:15000,i),2);  % Setting % 
  
  %fprintf("%d ",front);
  %fprintf("%d %d \n",index(1),index(2));
  
  % 더 뒤에 있는 index 확인 
  if index(1) < index(2) 
     Y(i) = ( index(2) - index(1) ) + (index(1) - front ) + 2;
  else
     Y(i) = ( index(1) - index(2) ) + (index(2) - front ) + 2;
  end
  
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
figure;
scatter(X,Y + 2289,'filled'); % tanh : 2363 / sigmoid : 2289  % Setting % 
xlabel('input');
ylabel('timedelay');
title('sigmoid 함수'); % Setting % 
grid on

end 
