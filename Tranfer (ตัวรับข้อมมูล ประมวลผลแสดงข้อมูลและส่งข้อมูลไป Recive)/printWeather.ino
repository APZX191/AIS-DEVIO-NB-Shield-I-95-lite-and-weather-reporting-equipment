//Prints the various variables directly to the port
//I don't like the way this function is written but Arduino doesn't support floats under sprintf
void printWeather()
{
  calcWeather(); 

  TX.write("#");
  TX.print(winddir);
  TX.write("a");
  TX.print(windspeedmph, 1);
  TX.write("b");
  TX.print(humidity, 1);
  TX.write("c");
  TX.print(tempf, 1);
  TX.write("d");
  TX.print(rainin,2);
  TX.write("e");
  TX.print(dailyrainin, 2);
  TX.write("f");
  TX.print(pressure, 2);
  TX.write("g");
  TX.print(batt_lvl, 2);
  TX.write("h");
  TX.print(light_lvl, 2);
  TX.write("i");
  
  
  Serial.println();
  Serial.print("winddir=");
  Serial.println(winddir);
  Serial.print("windspeedmph=");
  Serial.println(windspeedmph, 1);
  Serial.print("humidity=");
  Serial.println(humidity, 1);
  Serial.print("tempf=");
  Serial.println(tempf, 1);
  Serial.print("rainin=");
  Serial.println(rainin,2);
  Serial.print("dailyrainin=");
  Serial.println(dailyrainin, 2);
  Serial.print("pressure=");
  Serial.println(pressure, 2);
  Serial.print("batt_lvl=");
  Serial.println(batt_lvl, 2);
  Serial.print("light_lvl=");
  Serial.println(light_lvl, 2);
}
