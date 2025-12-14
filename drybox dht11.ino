#include <Wire.h>
#include <dht_nonblocking.h>
#include <LiquidCrystal_I2C.h>

#define DHT_SENSOR_TYPE DHT_TYPE_11 //defines the type of humidity sensor

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );




void setup( )
{
  Serial.begin( 9600);   //intilaize serial port
  
  lcd.init();          // initialize the lcd 
  lcd.init();
  lcd.backlight();

}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}


void loop( )
{
  float temperature;
  float humidity;


  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "Tempereture = " );
    lcd.setCursor(0,0);
    lcd.print("Temp = ");
    Serial.print( temperature, 1 );
    lcd.setCursor(7,0);
    lcd.print( temperature, 1 );
    lcd.setCursor(12,0);
    lcd.print("deg.");

    Serial.print( " deg. C,       Humidity = " );
    lcd.setCursor(0,1);
    lcd.print("Humi = ");
    Serial.print( humidity, 1 );
    lcd.setCursor(7,1);
    lcd.print(humidity, 1 );
    Serial.println( "%" );
    lcd.setCursor(12,1);
    lcd.print("%");
  }
}

