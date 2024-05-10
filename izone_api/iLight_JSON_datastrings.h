/*
 * Developer    : WM (Witold@air-stream.com.au)
 * Company      : Airstream Components
 * Date         : 15/10/2015
 *
 * All code (c)2015 Airstream Components. All rights reserved
 *
 * Description	: iLight system Ethernet JSON interface.
 * Describes all the commands required to control the system, and 
 * requests for checking the current settings of the system.
 *
 *			Send all commands to: iLightCommand
 *			Send all requests to: iLightRequest
 *
 * Revisions:
 * 1.0 - initial release
 * 1.1 - added more information to the set on off schedule time command and
 *		 fav/sched status message (disable off time for schedule)
 * 	   - added all lights off command
 *	   - added "LiLast" last light to the iLight system information
 *     - re-ordered acceleration settings
 *     - added adjustment lock status for the configuration screen
 * 	   - added "LiRgb" command
 *     - added all off anabled status to light JSON
 *     - added light all off enabled command 
 * 1.2 - changed the fav/sched setting commands ("LiFavTime" and "LiFavEn")
 *     - added change bridge command
 *     - added occupancy strategy setting command
 *     - added firmware version request 
 * 1.3 - removed command "LiConfig"
 *	   - added "LiPair" command for pairing iLight RF devices
 *     - changed "LiRemove" command
 *     - fixed change light Rgb mode (from LiRgb" to "LiRgbMode")
 * 1.4 - added "LiOccAuOn" command
 *     - added "OccAutoOn" to lamp JSON status
 *	   - added occupancy sensor settings to lamp JSON status.
 * 1.5 - added "NoBut" (number of buttons) to iLight Switch JSON status (1, 2, 3)
 *     - added command to change "AdLock" setting
 *	   - removed "Temp" from "SwConfig" and "Switch"
 *     - changed switch status and command documentation
 *     - added "RfCh" to system JSON and "LiRfCh" command to change
 *     - added a request for network settings and command to change
 * 1.6 - re-numbered the data request type values (error in doc)
 *	   - added a command to change network settings ("LiNetSet")
 * 1.7 - added light powered on setting to LightSystem ("LiPwrOn")
 *     - added a "LiPwrOn" command to change light powered on setting
 * 1.8 - changed the format for the "LiFavSet" command
 * 1.9 - added alarm settings to each of the lamps 
 *     - added lamp alarm setup command "LiLampAlarm"
 *     - added seconds to the "Time" command
 *     - added command to set all lamps to Holiday mode "LiHoliday"
 * 1.10- changed holiday mode command to allow to clear holiday mode in all lamps
 * 	   - added command to change the "all on" setting (similar to "all off") ("LiAlOn")
 *     - added command to set all lamps on ("LiAllOn")
 *     - added description of response to diagnostics request
 * 1.11- changed switch configuration options in "SwConfig" command to include the new AllOn function
 *     - added info on the "All On" option in the switch setting JSON
 *     - added "AlOn" parameter to iLight Status
 *     - really added command to change the "all on" setting (similar to "all off") ("LiAlOn")
 * 1.12- added LiAlSnooze command
 *	   - added "Att" attribute to switch information
 *     - added last button pressed information
 *     - added seconds to time in system information
 * 1.13- added 3/4G interface requirements
 *	   - upload data responce.
 *     - update flags status request/responce
 * 1.14- added request for current activate status.
 *     - added request to reset all update flags (ResetUpdateFlags)
 * 1.15- added "Reed" - reed switch state for light type CGDO
 *		 added "Pulse - pulse lenght for light type CGDO
 *       added "CgdoPulse" command to change pulse lenght
 *       added "CgpoGarage" command to change CGPO to CGDO
 * 1.16- added "CbldDrive" command to drive a blind up, down or stop
 *       added "CbldCalib" command to calibrate a blind
 *       added "CbldReverse" command to change the direction of the blind
 *		 added "CbldAllOn" command to change setting for the All On command
 *		 added "CbldAllOff" command to change setting for the All Off command
 * 1.17- added "CacrtcSetpoint" command to change the setpoint 
 * 1.18- added "CacdswLedOnOff" command to change the LED setting on the wall switch (CACDSW)
 *       added "CacdswWallSwitchType" command to change the wall switch type (CACDSW)
 *       added "IndividualLiPwrOn" command to change the individual setting for wall switch power on
 *       added "CvfcReverseOutput" command to reverse the output for the (CVFC)
 * 1.19- added "CacdLimitChange" command to change the lower brightness limit for dimmer type devices
 *       added "DeviceTypeChange" command to change devices to temperature controllers (for example)
 * 1.20- added "ResetMe" command for resetting the bridge
 * 1.21- added "AppleHomeKitPair" command to allow the accessory to be paired
 *-----------------------------------------------------------------------------
 * List of commands:
 *
 * system
 * - change tag line 1
 * - change tag line 2
 * - change configuration password
 * - change light page name
 * - set time
 * 
 * lights
 * - change light name
 * - change group number
 * - change page number
 * - change location on page
 * - turn light on/off
 * - change light brightness
 * - change white temperature
 * - change light color (RGB setting)
 * - change light fx
 * - change acceleration
 * - change alarm mode
 * - enable iSens controller
 * - music command
 * - change bridge command
 * - occupancy strategy command
 * 
 * favourites/schedules
 * - change favourite name
 * - change schedule enabled flags
 * - change schedule ON/OFF times
 * - save current light settings into a favourite
 * 
 * configuration connands
 * - attach/configure a light
 * - delete a light.
 * - configure wireless switch with the required parameters
 * - activate favourite (set lights to settings in a favourite)
 * 
 * the following are commands for requesting information from the lighting system
 * - request iLight information
 * 
 */

//**********************************************************
// enable apple homekit pairing
//**********************************************************
{
	"AppleHomeKitPair": 23456
}

//**********************************************************
// reset the bridge
//**********************************************************
{
	"ReSetMe": 12345
}

//**********************************************************
// request iLight information
//**********************************************************
{
	"LiRequest":{
	"Type": x,
	"No": y,
	"No1": z
	}
}
//where 
//x - data type to be requested. 
//	iLight lamp data 	- 1
//	system data			- 2
//	switch data 		- 3
//  fav/sched data		- 4
//  diagnostics			- 5
//  firmware versions   - 6
//  netwrk settings		- 7
//  last button pressed - 8
//y - is index number ( send 0 for system data)
//z - message number ( for FavSched )

// EXAMPLES:
//// request light 23 data
//{
//	"LiRequest":{
//	"Type": 1,
//	"No": 23,
//	"No1": 0
//	}
//}
//// request FavSched 3 info part 2
//{
//	"LiRequest":{
//	"Type": 4,
//	"No": 3,
//	"No1": 2
//	}
//}	


{
	"DeviceTypeChange":
	{
		"No":x,
		"Type":y
	}
}
// where
//- X – device number
//- Y – is the type
//  iLightDeviceTypes_CL5 = 1,
//  iLightDeviceTypes_CGPO = 2,   // CGPO
//  iLightDeviceTypes_CGDO = 3,   // CGPO as garage door
//  iLightDeviceTypes_CBLD = 4,   // roller blind
//  iLightDeviceTypes_CDM = 5,    // dimmer module
//  iLightDeviceTypes_CACR = 6,   // AC relay module
//  iLightDeviceTypes_CACRGD = 7, // AC relay as a garage door controller
//  iLightDeviceTypes_CACRTC_h = 8, // AC relay as a temperature controller
//  iLightDeviceTypes_CACRTC_c = 9,  // AC relay as a temperature controller
//  iLightDeviceTypes_CGPOTC_h = 10,  // CGPO as a temperature controller
//  iLightDeviceTypes_CGPOTC_c = 11,  // CGPO as a temperature controller
//  iLightDeviceTypes_CVFC = 12,      // CVFC voltage free relay
//  iLightDeviceTypes_CVFCGD = 13,    // CVFC as a temperature controller
//  iLightDeviceTypes_CACDSW = 14,    // dimmer module with wall switch
//  iLightDeviceTypes_CVFCTC_h = 15, // CVFC as a temperature controller
//  iLightDeviceTypes_CVFCTC_c = 16,  // CVFC as a temperature controller


//**********************************************************
// Change lower brightness limit for dimmers
//**********************************************************
{
	"CacdLimitChange":
	{
		"No":x,
		"CacdLimit":y
	}
}
// where
//- X – device number
//- Y – limit value ( < 100)


//**********************************************************
// Change the wall switch LED operation on the CACDSW module
//**********************************************************
{
	"CvfcReverseOutput":{
		"No": x,
		"ReverseOutput": y
	}
}
//where
//- x lamp number
//- y is the new settings: 1 - reverse, 0 - normal

//**********************************************************
// Change the individual setting for Wall switch power on
//**********************************************************
{
	"IndividualLiPwrOn":{
		"No": x,
		"LiPwrOn": y
	}
}
//where
//- x lamp number
//- y is the new setting
typedef enum
{
  IndividualWallSwitchOnMode_Global,
  IndividualWallSwitchOnMode_NoChange,
  IndividualWallSwitchOnMode_OnPrevious,
  IndividualWallSwitchOnMode_OnWhite
}IndividualWallSwitchOnMode_e;

//**********************************************************
// Change the wall switch type for the CACDSW module
//**********************************************************
{
	"CacdswWallSwitchType":{
		"No": x,
		"SwitchType": y
	}
}
//where
//- x lamp number
//- y is the new setting
typedef enum
{
  CacdswWallSwitchType_Latching,
  CacdswWallSwitchType_Momentary
}CacdswWallSwitchType_e;

//**********************************************************
// Change the wall switch LED operation on the CACDSW module
//**********************************************************
{
	"CacdswLedOnOff":{
		"No": x,
		"LedOnOff": y
	}
}
//where
//- x lamp number
//- y is the new settings: 1 - OnOff (reverse), 0 - OnOn

//**********************************************************
// Blind all on command settting
//**********************************************************
{
	"CacrtcSetpoint":{
		"No": x,
		"Setpoint": y
	}
}
//where
//- x lamp number
//- y is the new setpoint x100, value limits: 1500 <= b <= 3000, steps of 50

//**********************************************************
// Blind all on command settting
//**********************************************************
{
	"CbldAllOn":{
		"No": x,
		"AllOn": y
	}
}
//where
//- x lamp number
//- y is the new setting (0 - Not applicable (do not move), 1 - move up, 2 - move down )

//**********************************************************
// Blind all off command settting
//**********************************************************
{
	"CbldAllOff":{
		"No": x,
		"AllOff": y
	}
}
//where
//- x lamp number
//- y is the new setting (0 - Not applicable (do not move), 1 - move up, 2 - move down )

//**********************************************************
// set Blind mode
//**********************************************************
{
	"CbldReverse":{
		"No": x,
		"Reverse": y
	}
}
//where
//- x lamp number
//- y is the new setting (1 - reverse, 0 - not reverse)

//**********************************************************
// set Blind mode
//**********************************************************
{
	"CbldCalib":{
		"No": x,
		"Cal": 1
	}
}
//where
//- x lamp number

//**********************************************************
// set Blind mode
//**********************************************************
{
	"CbldDrive":{
		"No": x,
		"Mode": x
	}
}
//where
//- x lamp number
//- y - 0 = down
//    - 1 = up
//    - 2 = stop

//**********************************************************
// set CGPO garage mode
//**********************************************************
{
	"CgpoGarage":{
		"No": x,
		"Type": x
	}
}
//where
//- x lamp number
//- y - 2 = CGPO (normal GPO controller)
//    - 3 = CGDO (garage door controller)

//**********************************************************
// set CGDO garage pulse length
//**********************************************************
{
	"CgdoPulse":{
		"No": x,
		"Pulse": x
	}
}
//where
//- x lamp number
//- y is pulse lenght between 1 and 20

//**********************************************************
// set lamp to snooze
//**********************************************************
{
	"LiAlSnooze":{
		"No": x,
		"Time": y
	}
}
//where
//- x is lamp number
//- y is the snooze time in minutes.

//**********************************************************
// set all lamps to holiday mode
//**********************************************************
{
	"LiHoliday":{
		"Hol": x
	}
}
//where
//- x is 1 - to enable Holiday mode in all lamps
//		 0 - to clear the holiday mode in all lamps

//**********************************************************
// set favourite setting
// the setting will allow for the off time to be not set
// in this case the CL5B will send offH = 31 (0b11111)
// and offM = 63 (0b111111). To disable the off time CL5B
// will expect the same.
//**********************************************************
{
	"LiLampAlarm":{
		"No": x,
		"AlH": a,
		"AlM": b,
		"M": c,
		"Tu": d,
		"W": e,
		"Th": f,
		"F": g,
		"Sa": h,
		"Su": i,
		"En": j
	}
}
//where
//- x is lamp number
//- a is on hours
//- b is on minutes
//- c is monday enabled
//- d is tuesday enabled
//- e is wednesday enabled
//- f is thursday enabled
//- g is friday enabled
//- h is saturnday enabled
//- i is sunday enabled
//- j is alarm enabled

// change network settings
//{
//	"LiNetSet":	{
//		"Dhcp": 1,						// DHCP client enabled
//		"StaticIp": "string"			// static IP address Setting
//		"Mask": "string",				// Subnet Mask
//		"Gateway": "string",			// Default gateway
//		"PriDns": "string",				// Primary DNS server
//		"SecDns": "string"				// Secondary DNS server
//	}
//}
// change network settings
{
	"LiNetSet":	{
		"Dhcp": 1,				// DHCP client enabled
		"StaticIp_1": 0				// static IP address Setting
		"StaticIp_2": 0				// static IP address Setting
		"StaticIp_3": 0				// static IP address Setting
		"StaticIp_4": 0				// static IP address Setting
		"Mask_1": 0,				// Subnet Mask
		"Mask_2": 0,				// Subnet Mask
		"Mask_3": 0,				// Subnet Mask
		"Mask_4": 0,				// Subnet Mask
		"Gateway_1": "string",			// Default gateway
		"Gateway_2": "string",			// Default gateway
		"Gateway_3": "string",			// Default gateway
		"Gateway_4": "string",			// Default gateway
		"PriDns_1": "string",			// Primary DNS server
		"PriDns_2": "string",			// Primary DNS server
		"PriDns_3": "string",			// Primary DNS server
		"PriDns_4": "string",			// Primary DNS server
		"SecDns_1": "string"			// Secondary DNS server
		"SecDns_2": "string"			// Secondary DNS server
		"SecDns_3": "string"			// Secondary DNS server
		"SecDns_4": "string"			// Secondary DNS server
	}
}

// where strings are in the form of 255.255.255.255

//**********************************************************
// send change bridge command
//**********************************************************
{
	"LiOccSt":{
		"No": x,
		"D1": a,
		"A1": b,
		"D2": c,
		"A2": d
	}
}
//where
//x - is the light number to apply this strategy to
//a - delay 1 (0, 10, 15, 20, 30, 60 min)
//b - action 1 (% brightness)
//c - delay 2 (0, 10, 15, 20, 30, 60 min)
//d - action 2 (% brightness)


//**********************************************************
// send change bridge command
//**********************************************************
{
	"LiNewBridge":{
		"New": x
	}
}
//where
//x - is 1 to turn all the light off

//**********************************************************
// turn all lights off command
//**********************************************************
{
	"LiAllOff":{
		"Off": x
	}
}
//where
//x - is 1 to turn all the light off

//**********************************************************
// turn all lights on command
//**********************************************************
{
	"LiAllOn":{
		"On": x
	}
}
//where
//x - is 1 to turn all the light on

//**********************************************************
// lock layout screen adjustment command
//**********************************************************
{
	"LiAdLock":{
		"AdLock": x
	}
}
//where
//x - 1-locked, 0-unlocked

//**********************************************************
// change RF channel command
//**********************************************************
{
	"LiRfCh":{
		"Ch": x
	}
}
//where
//x - is the required channel number ( only allow 1 to 8 )

//**********************************************************
// change light powered on setting
//**********************************************************
{
	"LiPwrOn":{
		"PwrOn": x
	}
}
// where
// x - 0 - no change, 
//     1 - previous setting, 
//     2 - full white

//**********************************************************
// pair a light command
//**********************************************************
{
	"LiPair":{
		"Pair": 1
	}
}
// the device will then respond with the following
// app needs to send this command up to 3 times if the 
// response is error
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"ASH",
	"LiPair":	{
		"Type":	x,
		"No": y
	}
}
// where
//x if the device that that was just paired
//	0 - error (no device paired)
//  1 - iLight lamp paired
//  2 - iLight switch paired
//  3 - N/A
//  4 - N/A
//  5 - iLight repeater paired
//  6 - reticulation controller paired (new)
//  7 - iLight bridge not required to be paired
//y - is the id number the device was paired to.

//**********************************************************
// remove a light
//**********************************************************
{
	"LiRemove":{
		"Type": x,
		"No": y
	}
}
//where
//x - is the device type to delete
//  1 - iLight lamp configured
//  2 - iLight switch configured
//  3 - 
//y - is the index of the device.

//**********************************************************
// configure a switch
//**********************************************************
{
	"SwConfig":{
		"No": a,
		"LiNo": b,
		"OccSys": c,
		"OccNo": d,
		"But1Sys": f,
		"But1No": g,
		"But2Sys": h,
		"But2No": i,
		"But3Sys": j,
		"But3No": k
	}
}
//where
//- a is switch number (use SwNext from iLightSystem)
//- b is the light group number the light sensor will control
//- c is the system the occupancy sensor will control ( please see button/sensor function below )
//- d is the zone/light group number the occupancy sensor will control
//- f is the system button 1 will control ( please see button/sensor function below )
//- g is the zone/light group number button 1 will control
//- h is the system button 2 will control ( please see button/sensor function below )
//- i is the zone/light group number button 2 will control
//- j is the system button 3 will control ( please see button/sensor function below )
//- k is the zone/light group number button 3 will control
// button/sensor function
// 0 - no function
// 1 - iLight 			- group number ( "LGx" - where x is lamp number )
// 2 - iZone on/off		- group number ( "AC" )
// 3 - iZone 			- group number ( "ACx" - where x is zone number )
// 4 - iLight All off	- group number ( "LGOFF" )
// 5 - iLight All on    - group number ( "LGON" )
// 6 - security 		- dp not allow for at this stage.

//**********************************************************
// set favourite setting
//**********************************************************
{
	"LiFavSet":{
		"No": x,
		"Ap": stirng
	}
}
//where 
//- x is the favourite number to save the current system settings into
//- string contains the applicable flag for the lamps (just a string of 1s and 0s, corresponding to the setting for each of the lights)

//**********************************************************
// activate favourite
//**********************************************************
{
	"LiFavAct":{
		"No": x
	}
}
//where 
//- x is the favourite number

//**********************************************************
// set favourite setting
// the setting will allow for the off time to be not set
// in this case the CL5B will send offH = 31 (0b11111)
// and offM = 63 (0b111111). To disable the off time CL5B
// will expect the same.
//**********************************************************
{
	"LiFavTime":{
		"No": x,
		"OnH": a,
		"OnM": b,
		"OffH": c,
		"OffM": d,
		"M": b,
		"Tu": c,
		"W": d,
		"Th": e,
		"F": f,
		"Sa": g,
		"Su": h
	}
}
//where
//- x is favourite number
//- a is on hours
//- b is on minutes
//- c is off hours
//- d is off minutes
//- b is monday enabled
//- c is tuesday enabled
//- d is wednesday enabled
//- e is thursday enabled
//- f is friday enabled
//- g is saturnday enabled
//- h is sunday enabled

//**********************************************************
// set favourite setting
//**********************************************************
{
	"LiFavEn":{
		"No": x,
		"En": a		
	}
}
//where
//- x is favourite number
//- a is schedule enabled

//**********************************************************
// change favourite name
//**********************************************************
{
	"LiFavName":{
		"No": x,
		"Name":"string"
	}
}
//where 
//- x is favourite name 
//- string is the new name (16 chars including string termination)

//**********************************************************
// change tag line 1
//**********************************************************
{
	"LiTag1":{
		"string"
	}
}
//where 
//- string is the new tag text

//**********************************************************
// change tag line 2
//**********************************************************
{
	"LiTag2":{
		"string"
	}
}
//where 
//- string is the new tag text

//**********************************************************
// change configuration password
//**********************************************************
{
	"LiPass":"string"
}
//where 
//- string is the new password

//**********************************************************
// change page name
//**********************************************************
{
	"LiPageName":{
	"No": x,
	"Name":"string"
	}
}

//**********************************************************
// set time
//**********************************************************
{
	"Time":{
	"Y": a,
	"Mo": b,
	"D": c,
	"dow": d,
	"h": e,
	"mi": f,
	"s": g
	}
}
//where 
//- a is year ( last 2 digits only )
//- b is month
//- c is day of month
//- d is day of week
//- e is hour (24 hours)
//- f is minutes
//- g is seconds

//**********************************************************
// change light name
//**********************************************************
{
	"LiName":{
	"No": x,
	"Name":"string"
	}
}
//where
//- x is light number
//- string is the new light name (16 chars including string termination)

//**********************************************************
// change light group number
//**********************************************************
{
	"LiGroup":{
		"No": x,
		"Group": y
	}
}
//where 
//- x is light number
//- y is the new group number

//**********************************************************
// change light page number
//**********************************************************
{
	"LiPage":{
		"No": x,
		"Page": y
	}
}
//where
//x - is light number
//y - is the new page number

//**********************************************************
// change light All Off enabled
//**********************************************************
{
	"LiAlOf":{
		"No": x,
		"AlOf": y
	}
}
//where
//x - is light number
//y - 1 - All off enabled, 0 - All off disabled

//**********************************************************
// change light All Off enabled
//**********************************************************
{
	"LiAlOn":{
		"No": x,
		"AlOn": y
	}
}
//where
//x - is light number
//y - 1 - All on enabled, 0 - All on disabled

//**********************************************************
// change light Rgb mode
//**********************************************************
{
	"LiRgbMode":{
		"No": x,
		"Rgb": y
	}
}
//where
//x - is light number
//y - 1 - rgb, 0 - white

//**********************************************************
// change light Rgb mode
//**********************************************************
{
	"LiOccAutoOn":{
		"No": x,
		"On": y
	}
}
//where
//x - is light number
//y - 1 - auto on enabled, 0 - auto on disabled

//**********************************************************
// change light location on page
//**********************************************************
{
	"LiLoc":{
		"No": x,
		"x": y,
		"y": z
	}
}
//where 
//x - is light number
//y - is x location on page (%)
//z - is y location on page (%)

//**********************************************************
// turn light on/off
//**********************************************************
{
	"LiOn":{
		"No": x,
		"On": y
	}
}
//where
//x - is light number
//y - is the new light state, 1 - on, 0 - off

//**********************************************************
// change light brightness
//**********************************************************
{
	"LiBright":{
		"No": x,
		"Bright": y
	}
}
//where 
//x - is light number
//y is the new brightness (%)

//**********************************************************
// change white light temperature
//**********************************************************
{
	"LiTemp":{
		"No": x,
		"Temp": y
	}
}
//where 
//x - is light number
//y - is the new white light temperature (0 - cold, 100 - warm)

//**********************************************************
// change light RGB color
//**********************************************************
{
	"LiRgb":{
		"No": x,
		"R": r,
		"G": g,
		"B": b
	}
}
//where
//- x is light number
//- r is the R component of RGB (0-255)
//- g is the G component of RGB (0-255)
//- b is the B component of RGB (0-255)

//**********************************************************
// change accelleration
//**********************************************************
{
	"LiAccel":{
		"No": x,
		"Accel": y
	}
}
//where 
//x - is the light number
//y - is the new accel setting (0 - slowest to 3 - fastest)

//**********************************************************
// set light to alarm mode
//**********************************************************
{
	"LiAlarm":{
		"No": x,
		"Alar": y
	}
}
//where 
//x - is the light number
//y - alarm enabled setting

//**********************************************************
// enable iSensor controller mode
//**********************************************************
{
	"LiiSense":{
		"No": x,
		"iSen": y
	}
}
//where
//x - is light number
//y - is iSense enable, 1 - enable, 0 disable

//**********************************************************
// music command
//----------------------------------------------------------
// music in a light will be enabled in with the light mode
// command. Then the music command will not address a signle
// light, rather it will be a broadcast command and all 
// lights with music enabled will listen for this command.
//**********************************************************
{
	"LiMusic":{
		"RgbOn": a,
		"Temp": b,
		"Bright": c,
		"R": d
		"G": e,
		"B": f
	}
}
//where
//a - is RGB enable, 1 - RGB, 0 - white
//b - is white temperature
//c - is brightness
//d - is R component of RGB
//e - is G component of RGB
//f - is B component of RGB

//**********************************************************
// fx command
//**********************************************************
{
	"LiFx":{
		"No": x,
		"Fx": y
	}
}
//where 
//x - is light number
//y - is the required effect
//	0 - none, 
//	1 - reading, 
//	2 - relaxing, 
//	3 - candle, 
//	4 - holiday, 
//	5 - rotate, 
//	6 - circadian, 
//	7 - musinc, 
//	8 - auto brightness,

//**********************************************************
// Information sent from iLight in response to a request command
//**********************************************************

// switch setting
{
	"AirStreamDeviceUId": "001EC0028041", 
	"DeviceType": "ASH",
	"Switch":	{
		"Index": 0,				// switch index
		"But1": 0,				// 0 - button/sensor function (please see below)
		"But1No": 0,			// zone/light number
		"But2": 0,				// 0 - button/sensor function (please see below)
		"But2No": 0,			// zone/light number
		"But3": 0,				// 0 - button/sensor function (please see below)
		"But3No": 0,			// zone/light number
		"Occ": 0,				// 0 - button/sensor function (please see below)
		"OccNo": 0,				// zone/light number
		"Lit": 255,				// light sensor light number		
	}
}
// button/sensor function
// 0 - no function
// 1 - iLight 			- group number ( "LGx" - where x is lamp number )
// 2 - iZone on/off		- group number ( "AC" )
// 3 - iZone 			- group number ( "ACx" - where x is zone number )
// 4 - iLight All off	- group number ( "LGOFF" )
// 5 - iLight All on    - group number ( "LGON" )
// 6 - security 		- dp not allow for at this stage.


// lights setting
{
	"AirStreamDeviceUId": "001EC0028041", 		// system ID
	"DeviceType": "ASH",						// device type (ASH - for AirStream Hardware)
	"iLight":	{
		"Index": 0,				// light index
		"Name": "Light 1",		// upto 16 chars (including string termination)
		"GrNo": 2,				// group number, if 255 no group assigned and show "-"
		"PgNo": 0,				// page number, page on the layout screen
		"LocX": 20,				// X location on the layout page, given in %
		"LocY": 0,				// Y location on the layout page, given in %
		"Att": 1,				// 1 for light is attached/configured to the system, 0 not attached/configured
		"On": 1,				// light on, 1 for on, 0 for off
		"Brig": 100,			// brightness, %
		"Temp": 100,			// white temperature, 0 for full cold, 100 for full warm
		"R":	255,			// Red value, 0-255
		"G":	100,			// Green value, 0-255
		"B":	0,				// Blue value, 0-255
		"Type": "string"		// to be defined, for now only display
		"Pwrd": 0,				// 1 lamp powered, 0 not powered, meaning switched off at the wall and not able to be controlled.
		"Fx": 0,				// 0 - none, 1 - reading, 2 - relaxing, 3 - candle, 4 - holiday, 5 - rotate, 6 - circadian, 7 - musinc, 8 - auto brightness,
		"Acce": 0,				// acceleration (speed of light change), 0 - slow  to 3 - fast (immediate)
		"Alar": 1,				// light set to alarm mode
		"iSen": 0,				// iLight controlled by iSense controller
		"Rgb": 1,				// 1 - light in RGB mode, 0 light in white light mode
		"AlOf": 1,				// 1 - All Off enabled, 0 - all off disabled
		"AlOn": 1,				// 1 - All on enabled, 0 - all on disabled
		"D1": 0,				// occupancy sensor delay 1
		"A1": 0,				// occupancy sensor action 1
		"D2": 0,				// occupancy sensor delay 2
		"A2": 0,				// occupancy sensor action 2
		"OccAuOn": 1,   		// 1 - occ sensor auto on enabled, 0 - occ sensor auto on disabled
		"AlH": 12,				// alarm start hour
		"AlM": 0,				// alarm start minute
		"Reed": 1,				// reed switch state 0 - open, 1 - close
		"Pulse": 4,				// pulse lenght (1 - 20)
		"Days": {				// days enabled
			"M": 1,				// monday enabled
			"Tu": 1,			// tuesday enabled
			"W": 1,				// wednesday enabled
			"Th": 1,			// thursday enabled
			"F": 1,				// friday enabled
			"Sa": 0,			// saturday enabled
			"Su": 0				// sunday enabled
		}
		
	}
}

// FavSched setting
// information for each favourite/setting is split into 6 parts. Each part needs to be requested separately
// - part 1, contains the name, enable flag, on time, off time, days enabled and settings for the first 8 lamps
{
	"AirStreamDeviceUId": "001EC0028041", 		// system ID
	"DeviceType": "ASH",						// device type (ASH - for AirStream Hardware)
	"iLightFav": {
		"Fav": x,								// fav/sched number
		"mInd" : y,								// part number
		"Name": "string",						// fav/sched name (16 chars including string termination)
		"En": 1,								// schedule enabled flag
		"On": {									// on time
			"H": 22,							// hours
			"M": 33								// minutes
		}
		"Off": {								// off time	may be disabled (display --:-- on screen)
			"H": 23,							// hours	(31)
			"M": 45								// minutes	(and 63 when disabled)
		}
		"Days": {								// days enabled
			"M": 1,								// monday enabled
			"Tu": 1,							// tuesday enabled
			"W": 1,								// wednesday enabled
			"Th": 1,							// thursday enabled
			"F": 1,								// friday enabled
			"Sa": 0,							// saturday enabled
			"Su": 0								// sunday enabled
		}
		"iLightFav":[{							// lamp configuration set
			"X": z,								// lamp number
			"S": "string"						// lamp settings (coma delimited string, see below)
			},{
			
			// in total 8 lamps
	
		}]
	}
}
//where string "Set.S" is comma delimited "a,b,c,d,e,f,g,h,i"
//	- a is lamp on
//	- b is brightness
//	- c is white temperature
//	- d is red
//	- e is green
//	- f is blue
//	- g is Fx
//	- h is rgbOn
//	- i is acceleration
//  - j is applicable flag ( 0 = not applicable)

// parts 2 to 6 contain settings for 24 consecutive lamp settings each
{
	"AirStreamDeviceUId": "001EC0028041", 		// system ID
	"DeviceType": "ASH",						// device type (ASH - for AirStream Hardware)
	"iLightFav": {
		"Fav": x,								// fav/sched number
		"mInd" : y,								// part number
		"iLightFav":[{							// lamp configuration set
			"X": z,								// lamp number
			"S": "string"						// lamp settings (coma delimited string, see above)
			},{
			
			// in total 24 lamps
	
		}]
	}
}

// system info
{
	"AirStreamDeviceUId": "001EC0028041", 
	"DeviceType": "ASH",
	"iLightSystem":	{
		"IntV": 1						// interface version
		"Tag1": "string",				// first line text
		"Tag2": "string",				// second line text
		"Pass": "string",				// configuration password
		"Pg1N": "string",				// layout page 1 name, up to 16 characters (including string termination)
		"Pg2N": "string",				// layout page 2 name, up to 16 characters (including string termination)
		"Pg3N": "string",				// layout page 3 name, up to 16 characters (including string termination)
		"Pg4N": "string",				// layout page 4 name, up to 16 characters (including string termination)
		"Pg5N": "string",				// layout page 5 name, up to 16 characters (including string termination)
		"Pg6N": "string",				// layout page 6 name, up to 16 characters (including string termination)
		"Pg7N": "string",				// layout page 7 name, up to 16 characters (including string termination)
		"Pg8N": "string",				// layout page 8 name, up to 16 characters (including string termination)
		"Pg9N": "string",				// layout page 9 name, up to 16 characters (including string termination)
		"Pg10N": "string",				// layout page 10 name, up to 16 characters (including string termination)
		"LiNext": 3,					// used for light configuration, the next light will be configured with this number
		"SWNext": 3,					// used for switch configuration, the next switch will be configured with this number
		// also include current time
		"Time":{						// this is the iLight system time.
			"Y": 15,
			"Mo": 9,
			"D": 25,
			"dow": 2
			"h": 15,
			"mi": 36,
			"s": 12
		},
		"LiLast":3,						// the last configured light in the table.
		"SwLast":100,					// the last configured switch in the table
		"AdLock":1,						// screen layout adjustment lock (1-locked, 0-unlocked)
		"RfCh": 1,						// RF channel used by the system ( 1 - 8 )
		"LiPwrOn": 2					// light power on options (0 - no change, 1 - previous setting, 2 - full white).
	}
}

// firmware versions
{
	"AirStreamDeviceUId":	"001EC0028041",
	"DeviceType":	"ASH",
	"Fmw":	"string"					// where string is a comma separated string with device and their firmware version
}

// network settings
{
	"AirStreamDeviceUId": "001EC0028041", 
	"DeviceType": "ASH",
	"NetworkSettings":	{
		"IpAddress": "string",			// current IP address
		"Mac": "string",				// MAC address
		"Dhcp": 1,						// DHCP client enabled
		"StaticIp": "string"			// static IP address Setting
		"Mask": "string",				// Subnet Mask
		"Gateway": "string",			// Default gateway
		"PriDns": "string",				// Primary DNS server
		"SecDns": "string"				// Secondary DNS server
	}
}

// diagnostics information
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"ASH",
	"iLightDiagLamp":	{
		"Temp":	0,						// internal Temp. in 0.01degC
		"Reduction":	0,				// Drightness reduction (%)
		"LightReading":	0,				// Light sensor Current Reading 
		"OccupancyReading":	0,
		"LightSetpoint":	65535,  	// Light Sensor Setpoint (if oxffff print “NOT SET”)
		"LampOverride":	255,			// Current Override ( 0xff – “NIL”, 0 – “OFF”, else number)
		"LightTimeouts":	0,			
		"LightPerCent":	0,				
		"TempBrightness":	0,			// Auto Brightness
		"OccPresentTimeout":	0,		// Time Since Last Move	
		"LampFavCalcChecksum":	17014,
		"LampFavRecChecksum":	0,
		"LiTimeout":	0,				// Light Sensor (1 – “YES”, 0 – “NO”)
		"OccTimeout":	0,				// iSense (1 – “YES”, 0 – “NO”)
		"OccCurrentAction":	0,          // iSense Action Required ( 0xff – “NIL”, 0 – “OFF”, else number)
		"Powered": 1					// Power Available (1 – “YES”, 0 – “NO”)
	}
}

// last button pressed information
{
	"AirStreamDeviceUId": "001EC0028041", 
	"DeviceType": "ASH",
	"LiLastButton":	{
		"Sw": 0,			// switch number, 255 if no button has been pressed yet
		"But": 0,			// button number, 255 if no button has been pressed yet
	}
}



// 3/4G interface.
// - upload data responce
// The server upon receiving information from the bridge will respond with the following infromation

// - lamp information upload confirmation
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightLampConf":	{
		"Index":	0,					// lamp number
		"conf":		"string"			// Ok - if no update required
										// Error - if something is wrong
										// Update - if there was a change from a smart device, information was not accepted by the server.
	}
}

// - switch information upload confirmation
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightSwitchConf":	{
		"Index":	0,					// switch number
		"conf":		"string"			// Ok - if no update required
										// Error - if something is wrong
										// Update - if there was a change from a smart device, information was not accepted by the server.
	}
}

// - system information upload confirmation
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightSystemConf":	{
		"conf":		"string"			// Ok - if no update required
										// Error - if something is wrong
										// Update - if there was a change from a smart device, information was not accepted by the server.
	}
}

// - fav/sched information upload confirmation
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightFavsConf":	{
		"Index":	0,					// fav/sched number
		"conf":		"string"			// Ok - if no update required
										// Error - if something is wrong
										// Update - if there was a change from a smart device, information was not accepted by the server.
	}
}


// bridge gets status of changes from smart devices from server .
// periodically, the bridge will ask the server for updated flags
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"ASH",
	"iLightUpdateFlagsGet":	"string"	
}
// where string can be:
// - Lamps, Switches, System, Favs, Activate, ResetUpdateFlags, Settings

// the server will respond with the following
// - Lamps
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightUpdateLamps": "string"	
}
// where string is 128 1s and 0s, each correspoing to a ligth updated from a smart device flag

// - Switches
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightUpdateSwitches": "string"	
}
// where string is 128 1s and 0s, each correspoing to a switch updated from a smart device flag

// - System
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightUpdateSystem": "string"	
}
// where string is a 1 or 0, correspoing to a system setting updated from a smart device flag

// - Favs
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightUpdateFavs": "string"	
}
// where string is 9 1s and 0s, each correspoing to a Fav updated from a smart device flag

// - Activate
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightActivate": int	
}
// where int can be:
// 0 - none
// 1 - fav 1
// 2 - fav 2
// 3 - fav 3
// 4 - fav 4
// 5 - fav 5
// 6 - fav 6
// 7 - fav 7
// 8 - fav 8
// 9 - fav 9
// 10- all on
// 11- all off
// 12- reset bridge

// - Settings
{
	"AirStreamDeviceUId": "123456794",
	"DeviceType":   "IASD",
	"iLightSettings":{
		"CheckLamps": a,
		"CheckSwitches": b,
		"CheckSystem": c,
		"CheckFunctions": d,
		"CheckFavourites": e,
		"LampUploadTimeout": f,
		"SwitchUploadTimeout": g,
		"SystemUploadTimeout": h,
		"FavouriteUploadTimeout",: i
	}
}
// where a, b, c... are ints set in server

// - ResetUpdateFlags
{
	"AirStreamDeviceUId":	"123456794",
	"DeviceType":	"IASD",
	"iLightResetUpdateFlags": 1	
}








