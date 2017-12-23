function y = array_to_dec(x)
 if ~isvector(x)
     error('Input must be a vector')
 end
 data = []
 for i = 1:length(x)
     if x(i) ~= 0
        data = [data x(i)]
     end
 end
 
 y = data
end