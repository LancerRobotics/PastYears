 /*!@addtogroup HiTechnic
00002  * @{
00003  * @defgroup hteopd EOPD Sensor
00004  * HiTechnic EOPD Sensor
00005  * @{
00006  */

 /*
00009  * $Id: hitechnic-eopd.h 133 2013-03-10 15:15:38Z xander $
00010  */

 #ifndef __HTEOPD_H__
 #define __HTEOPD_H__
 /** \file hitechnic-eopd.h
00015  * \brief HiTechnic EOPD Sensor driver
00016  *
00017  * hitechnic-eopd.h provides an API for the HiTechnic EOPD sensor.
00018  *
00019  * Changelog:
00020  * - 0.1: Initial release
00021  * - 0.2: Removed HTEOPDsetRange() and HTEOPDgetRange(), not really necessary
00022  *        Changed the way raw value is calculated due to sensor type change
00023  * - 0.3: Renamed HTEOPDgetRaw to HTEOPDreadRaw
00024  *        Renamed HTEOPDgetProcessed to HTEOPDreadProcessed
00025  *        Added SMUX functions
00026  * - 0.4: Added No Wait versions of HTEOPDsetShortRange and HTEOPDsetLongRange for non-SMUX functions
00027  *        Changed the underlying sensor types for RobotC 1.57A and higher.
00028  * - 0.5: Now only supports ROBOTC 2.00<br>
00029  *        Make use of the new analogue sensor calls for SMUX sensors in common.h
00030  * - 0.6: Replaced array structs with typedefs
00031  *
00032  * Credits:
00033  * - Big thanks to HiTechnic for providing me with the hardware necessary to write and test this.
00034  *
00035  * License: You may use this code as you wish, provided you give credit where its due.
00036  *
00037  * THIS CODE WILL ONLY WORK WITH ROBOTC VERSION 3.59 AND HIGHER.
00038
00039  * \author Xander Soldaat (xander_at_botbench.com)
00040  * \date 20 February 2011
00041  * \version 0.6
00042  * \example hitechnic-eopd-test1.c
00043  * \example hitechnic-eopd-SMUX-test1.c
00044  */

 #pragma systemFile

 #ifndef __COMMON_H__
 #include "common.h"
 #endif

 // This ensures the correct sensor types are used.
 TSensorTypes HTEOPDLRType = sensorAnalogActive;
 TSensorTypes HTEOPDSRType = sensorAnalogInactive;

 int HTEOPDreadRaw(tSensors link);
 int HTEOPDreadProcessed(tSensors link);
 void HTEOPDsetShortRange(tSensors link);
 void HTEOPDsetLongRange(tSensors link);

 #ifdef __HTSMUX_SUPPORT__
 int HTEOPDreadRaw(tMUXSensor muxsensor);
 int HTEOPDreadProcessed(tMUXSensor muxsensor);
 void HTEOPDsetShortRange(tMUXSensor muxsensor);
 void HTEOPDsetLongRange(tMUXSensor muxsensor);
 #endif

 /**
00069  * Get the raw value from the sensor
00070  * @param link the HTEOPD port number
00071  * @return raw value of the sensor
  */
 int HTEOPDreadRaw(tSensors link) {
   return 1023 - SensorRaw[link];
 }


 /**
00079  * Get the raw value from the sensor
00080  * @param muxsensor the SMUX sensor port number
00081  * @return raw value of the sensor
00082  */
 #ifdef __HTSMUX_SUPPORT__
 int HTEOPDreadRaw(tMUXSensor muxsensor) {
   return 1023 - HTSMUXreadAnalogue(muxsensor);
 }
 #endif // __HTSMUX_SUPPORT__


 /**
00091  * Get the processed value from the sensor. This is obtained by using sqrt(raw value * 10)
00092  * @param link the HTEOPD port number
00093  * @return processed value of the sensor
  */
 int HTEOPDreadProcessed(tSensors link) {
   int _val = sqrt(HTEOPDreadRaw(link) * 10);
   return _val;
 }


 /**
00102  * Get the processed value from the sensor. This is obtained by using sqrt(raw value * 10)
00103  * @param muxsensor the SMUX sensor port number
00104  * @return processed value of the sensor
  */
 #ifdef __HTSMUX_SUPPORT__
 int HTEOPDreadProcessed(tMUXSensor muxsensor) {
   int _val = sqrt((long)HTEOPDreadRaw(muxsensor) * (long)10);
   return _val;
 }
 #endif // __HTSMUX_SUPPORT__


 /**
00115  * Set the range of the sensor to short range, this is done
00116  * by configuring the sensor as sensorRawValue
  * @param link the HTEOPD port number
  */
 void HTEOPDsetShortRange(tSensors link) {
   SetSensorType(link, HTEOPDSRType);
 }


 /**
00125  * Set the range of the sensor to short range, this is done
00126  * by switching off dig0
00127  * @param muxsensor the SMUX sensor port number
00128  */
 #ifdef __HTSMUX_SUPPORT__
 void HTEOPDsetShortRange(tMUXSensor muxsensor) {
   HTSMUXsetAnalogueInactive(muxsensor);
 }
 #endif // __HTSMUX_SUPPORT__


 /**
00137  * Set the range of the sensor to long range, this is done
00138  * by configuring the sensor as sensorLightActive and setting
00139  * it to modeRaw
  * @param link the HTEOPD port number
  */
 void HTEOPDsetLongRange(tSensors link) {
   SetSensorType(link, HTEOPDLRType);
 }


 /**
  * Set the range of the sensor to long range, this is done
  * by setting dig0 high (1).
  * @param muxsensor the SMUX sensor port number
  */
#ifdef __HTSMUX_SUPPORT__
void HTEOPDsetLongRange(tMUXSensor muxsensor) {
  HTSMUXsetAnalogueActive(muxsensor);
}
#endif // __HTSMUX_SUPPORT__

#endif // __HTEOPD_H__

/*
 * $Id: hitechnic-eopd.h 133 2013-03-10 15:15:38Z xander $
 */
/* @} */
/* @} */
