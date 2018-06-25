#include "System.h"
#include "ArduinoLibrary.h"
#include "Constants.h"
#include "prototype.h"

void setup()
{
    deviceInit();

   // degitalRead( CFG_BTN ) == LOW ) ? goConfigMode() : goGoalButtonMode();
   goConfigMode();
}

void loop()
{
    
}

void deviceInit()
{
    /* 入出力設定 */
    pinMode( CFG_BTN, INPUT );
    pinMode( GOAL_BTN, INPUT );

    /* シリアル通信 */
    Serial.begin( 115200 );

    /* ファイルシステム */
    SPIFFS.begin();
}
