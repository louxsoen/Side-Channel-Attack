function cptrace = compress2(FN,trNum,rate) % 압축 파형 만들기

% 파일 읽기 
fid = fopen(FN,'r');

for i = 1 : trNum
    len = fread(fid,1,'uint32');
    trace = fread(fid,len,'double');
    
    for  j = 1: len / rate
        cptrace(j,i) = mean(trace( 1 + (j-1)*rate : j*rate) );
    end
    
    % 진행도 확인
    if mod(i,50) == 0
        i
    end
end

figure;
plot(cptrace(:,1));

end
