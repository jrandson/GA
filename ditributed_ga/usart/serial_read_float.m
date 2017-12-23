


function y = serial_read_float(obj)
    data = fread(obj,1,'float');
    y = data;
end