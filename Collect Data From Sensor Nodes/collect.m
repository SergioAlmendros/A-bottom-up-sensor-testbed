function collect()

  fid = fopen ("collect1.in", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');

    temp1(i) = str2double(r(1));
    hum1(i) = str2double(r(2));
    noise1(i) = str2double(r(3));
    light1(i) = str2double(r(4));
    gas1(i) = str2double(r(5));
    time1(i) = r(6);
  end
  fclose(fid);
  
  fid = fopen ("collect2.in", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');

    temp2(i) = str2double(r(1));
    hum2(i) = str2double(r(2));
    noise2(i) = str2double(r(3));
    light2(i) = str2double(r(4));
    gas2(i) = str2double(r(5));
    time2(i) = r(6);
  end
  fclose(fid);
  
  fid = fopen ("collect3.in", 'r');
  i = 0;
  while ( feof(fid) == 0 )
    i = i+1;
    p = fgetl(fid);
    #disp(p)
    r = regexp(p, ' ', 'split');

    temp3(i) = str2double(r(1));
    hum3(i) = str2double(r(2));
    noise3(i) = str2double(r(3));
    light3(i) = str2double(r(4));
    gas3(i) = str2double(r(5));
    time3(i) = r(6);
  end
  fclose(fid);

  figure
  plot(1:i+1,temp1,'r');
  hold on
  plot(1:i+1,temp2,'b');
  plot(1:i+1,temp3,'g');
  hold off
  xlabel( 'Temperature' );
  ylabel( 'Time' );
  title( "Temperature" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  
  figure
  plot(1:i+1,hum1,'r');
  hold on
  plot(1:i+1,hum2,'b');
  plot(1:i+1,hum3,'g');
  hold off
  xlabel( 'Humidity' );
  ylabel( 'Time' );
  title( "Humidity" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  
  figure
  plot(1:i+1,noise1,'r');
  hold on
  plot(1:i+1,noise2,'b');
  plot(1:i+1,noise3,'g');
  hold off
  xlabel( 'Noise' );
  ylabel( 'Time' );
  title( "Noise" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  
  figure
  plot(1:i+1,light1,'r');
  hold on
  plot(1:i+1,light2,'b');
  plot(1:i+1,light3,'g');
  hold off
  xlabel( 'Light' );
  ylabel( 'Time' );
  title( "Light" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')
  
  figure
  plot(1:i+1,gas1,'r');
  hold on
  plot(1:i+1,gas2,'b');
  plot(1:i+1,gas3,'g');
  hold off
  xlabel( 'Gas presence' );
  ylabel( 'Time' );
  title( "Air quality" );
  legend('Arduino 1', 'Arduino 2', 'Arduino 3')

end






















