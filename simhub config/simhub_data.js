function getCurrentLapTime(){
	var lapTime = $prop('CurrentLapTime');
	lapTime = lapTime.toString();
	if(lapTime == "00:00:00")
	{
		return lapTime;
	}
	else
		lapTime = lapTime.toString().slice(3,11);
	return lapTime;
}
function getRPM(){
	var rpm = $prop('DataCorePlugin.GameData.NewData.Rpms');
	rpm = format(rpm,"0");
	return rpm;
}
function getSpeed(){
	var speed = $prop('SpeedKmh');
	speed = format(speed, '0');
	return speed;
}
function getGear(){
	var gear = $prop('Gear');
	return gear;
}
function getBestLapTime(){
	var bestLapTime = $prop('BestLapTime');
	bestLapTime = bestLapTime.toString();
	if(bestLapTime == "00:00:00")
	{
		return bestLapTime;
	}
	else
		bestLapTime = bestLapTime.toString().slice(3,11);
	return bestLapTime;
}
function getFuel(){
	var fuel = $prop('FuelPercent');
	fuel = format(fuel, '0');
	return fuel;
}
function getRedLine(){
	var redLine = $prop('CarSettings_CurrentGearRedLineRPM');
	return redLine;
}
function getBrake(){
	var brake = $prop('Brake');
	brake = format(brake, '0');
	return brake;
}
function getThrottle(){
	var throttle = $prop('Throttle');
	throttle = format(throttle, '0');
	return throttle;
}
function getLap()
{
	lap = $prop('CurrentLap');
	return lap;
}
var speed = getSpeed();
var carData = "{\"speed\":" + getSpeed() + ",\"rpm\":" + getRPM() + ",\"cLapTime\":" +"\"" + getCurrentLapTime() + "\"," +"\"gear\":" + "\"" +getGear() + "\"" + ",\"bLapTime\":" +"\"" + getBestLapTime() + "\""+ ",\"fuel\":"+ getFuel() + ",\"redLineRPM\":"+ getRedLine()
  + ",\"brake\":" + getBrake() + ",\"throttle\":"+ getThrottle()  + ",\"lap\":"+ getLap() +"}";
return carData;