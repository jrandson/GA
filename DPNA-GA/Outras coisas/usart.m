%delete(instrfind({'Port'},{'COM3'}));
%	 
%obj.timeout = 30;
%(Arduino/Genuino Mega or Mega 2560)' ,'BaudRate',9600
%obj.InputBufferSize = 5000;
%obj.BaudRate = 1843200;
%fopen(obj)    
%fclose(obj)

while(1)  
  
    %fwrite(obj,qtd_gen, 'int32'); 
    adc = fread(obj,1,'int32');
    disp(sprintf('ADC:%d',adc));
    dist = fread(obj,1,'float32');        
   
    str = sprintf('Distância:%f',dist);   
    disp(str);
    
    pause;
end;







