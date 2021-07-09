function z=read_floatinput(filename)
fid = fopen(filename,'r');

trNum = 100;

fseek(fid,128,'bof');

for i=1:trNum
   temp =fread(fid, 1,'float');
   fprintf('%f \n',temp);
   temp =fread(fid, 3,'float');
end

fclose(fid);

end
