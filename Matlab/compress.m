function cptrace = compress(trace,trNum,rate) % 압축 파형 만들기

for i = 1 : trNum
    for  j = 1: length(trace(:,i))/rate
        cptrace(j,i) = mean(trace(1+(j-1)*rate:j*rate,i));
    end
    endA

figure;
plot(cptrace(:,1));

end
