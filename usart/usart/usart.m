

%obj = serial('COM4','BaudRate',9600,'DataBits',8); %(Arduino/Genuino Mega or Mega 2560)' ,'BaudRate',9600
%obj.InputBufferSize = 5000;
%obj.BaudRate = 1843200;
%fopen(obj)    
%fclose(obj)

%obj.InputBufferSize = 8;
    
%data = fread(obj,1,'int');
%disp(data);    
while(1)   
    
    %l� um int
    %f = fread(obj,1,'int');
    %disp(f);
    
    %l� um float
    %f = fread(obj,1,'float');
    %disp(f);
    
    %escreve inteiro
    %fwrite(obj,28,'int');
    %f = fread(obj,1,'int');
    %disp(f);
    
    
    %escreve float
    %a = 1234.57849; % your float point number
    %n = 16;         % number bits for integer part of your number      
    %m = 20;         % number bits for fraction part of your number
    % binary number
    %d2b = [ fix(rem(fix(a)*pow2(-(n-1):0),2)), fix(rem( rem(a,1)*pow2(1:m),2))];  % 
    % the inverse transformation
    %b2d = d2b*pow2([n-1:-1:0 -(1:m)].');    
    %mat = mat2str(d2b);
        
    fwrite(obj,3.8025,'float32');     
    f = fread(obj,1,'float32'); %f = fscanf(obj,'%f'); %
    %use vpa para aumentar a precis�o
    disp(vpa(f));    
    pause;
end



