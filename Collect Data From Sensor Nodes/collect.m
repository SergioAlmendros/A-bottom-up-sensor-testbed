function collect()

  fid = fopen ("logData1", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    
    if(i < 62)
      temp1(i) = str2double(r(2));
      hum1(i) = str2double(r(3));
      noise1(i) = str2double(r(4));
      light1(i) = str2double(r(5));
      gas1(i) = str2double(r(6));
      time1(i) = r(7);
    end

  end
  fclose(fid);
  
  fid = fopen ("logData2", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    if(i < 62)
      temp2(i) = str2double(r(2));
      hum2(i) = str2double(r(3));
      noise2(i) = str2double(r(4));
      light2(i) = str2double(r(5));
      gas2(i) = str2double(r(6));
      time2(i) = r(7);
    end

  end
  fclose(fid);
  
  fid = fopen ("logData3", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');
    if(i < 62)
      temp3(i) = str2double(r(2));
      hum3(i) = str2double(r(3));
      noise3(i) = str2double(r(4));
      light3(i) = str2double(r(5));
      gas3(i) = str2double(r(6));
      time3(i) = r(7);
    end
    
  end
  fclose(fid);


  figure 1
  plot(1:61,temp1,'r');
  hold on
  plot(1:61,temp2,'b');
  plot(1:61,temp3,'g');
  hold off
  ylabel( 'Temperature' );
  xlabel( 'Time' );
  title( "Temperature" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  saveas (1, "../Final\ Report/Figures/GraphicTemperature.png");
  
  figure 2
  plot(1:61,hum1,'r');
  hold on
  plot(1:61,hum2,'b');
  plot(1:61,hum3,'g');
  hold off
  ylabel( 'Humidity' );
  xlabel( 'Time' );
  title( "Humidity" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  saveas (2, "../Final\ Report/Figures/GraphicHumidity.png");
  
  figure 3
  plot(1:61,noise1,'r');
  hold on
  plot(1:61,noise2,'b');
  plot(1:61,noise3,'g');
  hold off
  ylabel( 'Noise' );
  xlabel( 'Time' );
  title( "Noise" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  saveas (3, "../Final\ Report/Figures/GraphicNoise.png");
  
  figure 4
  plot(1:61,light1,'r');
  hold on
  plot(1:61,light2,'b');
  plot(1:61,light3,'g');
  hold off
  ylabel( 'Light' );
  xlabel( 'Time' );
  title( "Light" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  saveas (4, "../Final\ Report/Figures/GraphicLight.png");
  
  figure 5
  plot(1:61,gas1,'r');
  hold on
  plot(1:61,gas2,'b');
  plot(1:61,gas3,'g');
  hold off
  ylabel( 'Gas presence' );
  xlabel( 'Time' );
  title( "Air quality" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  saveas (5, "../Final\ Report/Figures/GraphicGas.png");

end
