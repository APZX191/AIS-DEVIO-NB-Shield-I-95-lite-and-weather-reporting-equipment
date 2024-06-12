static void smartdelay(unsigned long ms)
{
  unsigned long start = millis();
  do
  {

  } while (millis() - start < ms);
}
