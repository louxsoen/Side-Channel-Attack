function [z,atr]=cut_and_align(trace)
    compare_this=trace(:,1);
    
    for i=1:1000
        z(1,i)=0;
        for j=1:400
            threshold=j-200;
            if threshold>0
                tmp=trace(1:end-threshold,i);
                corr=corrcoef(compare_this(threshold+1:end),trace(1:end-threshold,i));
            else
                tmp=trace((-threshold)+1:end,i);
                corr=corrcoef(compare_this(1:end+threshold),trace((-threshold)+1:end,i));
            end
            if corr(1,2)>z(1,i)
                z(1,i)=corr(1,2);
                z(2,i)=threshold;
                if threshold>0
                    atr(:,i)=vertcat(tmp,zeros(threshold,1));
                else
                    atr(:,i)=vertcat(zeros((-threshold),1),tmp);
                end
            end
        end
    end
        
        
end
