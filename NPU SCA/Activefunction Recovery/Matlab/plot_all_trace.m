function z=plot_all_trace(filename)
fid = fopen(filename,'r');

trNum = 1000;  %
trLen = 24000; %

fseek(fid,128,'bof');

for i=1:trNum
    z(:,i)=fread(fid, trLen,'double');
    plot(z(:,i));
    hold on;
end

fclose(fid);

end
