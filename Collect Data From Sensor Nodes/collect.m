function collect()
	
	limit = 1501;
  fid = fopen ("logDataFerran", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    if( i == limit )
    	break;
  	end
  	i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    temp1(i) = str2double(r(2));
    hum1(i) = str2double(r(3));
    noise1(i) = str2double(r(4));
    light1(i) = str2double(r(5));
    gas1(i) = str2double(r(6));
    time1(i) = r(7);

  end
  fclose(fid);
  
  fid = fopen ("logDataSergio", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    if( i == limit )
    	break;
  	end
  	i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    temp2(i) = str2double(r(2));
    hum2(i) = str2double(r(3));
    noise2(i) = str2double(r(4));
    light2(i) = str2double(r(5));
    gas2(i) = str2double(r(6));
    time2(i) = r(7);

  end
  fclose(fid);
  
  fid = fopen ("logDataUPF", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    if( i == limit )
    	break;
  	end
  	i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    temp3(i) = str2double(r(2));
    hum3(i) = str2double(r(3));
    noise3(i) = str2double(r(4));
    light3(i) = str2double(r(5));
    gas3(i) = str2double(r(6));
    time3(i) = r(7);
    
  end
  fclose(fid);


  figure 1
  plot(1:i,temp1,'r');
  hold on
  plot(1:i,temp2,'b');
  plot(1:i,temp3,'g');
  hold off
  ylabel( 'Temperature [Celsius Degrees]', "fontsize", 18);
  xlabel ("Time [minutes]", "fontsize", 18) 
  title( 'Temperature', "fontsize", 20 );
  legend('Montgat', 'Badalona', 'Barcelona')
  saveas (1, "../Final\ Report/Figures/CompleteGraphicTemperature.png");
  
  figure 2
  plot(1:i,hum1,'r');
  hold on
  plot(1:i,hum2,'b');
  plot(1:i,hum3,'g');
  hold off
  ylabel( 'Relative Humidity [%]', "fontsize", 18 );
  xlabel( 'Time [minutes]', "fontsize", 18 );
  title( 'Relative Humidity', "fontsize", 20 );
  legend('Montgat', 'Badalona', 'Barcelona')
  saveas (2, "../Final\ Report/Figures/CompleteGraphicHumidity.png");
  
  figure 3
  plot(1:i,noise1,'r');
  hold on
  plot(1:i,noise2,'b');
  plot(1:i,noise3,'g');
  hold off
  ylabel( 'Noise [%]', "fontsize", 18 );
  xlabel( 'Time [minutes]', "fontsize", 18 );
  title( 'Noise', "fontsize", 20 );
  legend('Montgat', 'Badalona', 'Barcelona')
  saveas (3, "../Final\ Report/Figures/CompleteGraphicNoise.png");
  
  figure 4
  plot(1:i,light1,'r');
  hold on
  plot(1:i,light2,'b');
  plot(1:i,light3,'g');
  hold off
  ylabel( 'Light [Lux]', "fontsize", 18 );
  xlabel( 'Time [minutes]', "fontsize", 18 );
  title( 'Light', "fontsize", 20 );
  legend('Montgat', 'Badalona', 'Barcelona')
  saveas (4, "../Final\ Report/Figures/CompleteGraphicLight.png");
  
  figure 5
  plot(1:i,gas1,'r');
  hold on
  plot(1:i,gas2,'b');
  plot(1:i,gas3,'g');
  hold off
  ylabel( 'Gas presence [%]', "fontsize", 18 );
  xlabel( 'Time [minutes]', "fontsize", 18 );
  title( 'Air quality', "fontsize", 20 );
  legend('Montgat', 'Badalona', 'Barcelona')
  saveas (5, "../Final\ Report/Figures/CompleteGraphicGas.png");

end
