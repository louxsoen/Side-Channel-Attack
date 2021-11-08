function z = read_corr_trace(fileName)
fileID = fopen("./corrtrace/" + fileName, 'r');
%fileID = fopen(fileName, 'r');

traceLen = 22000;


z = fread(fileID, traceLen, 'double');

plot(z,'r');

fclose(fileID);

end
