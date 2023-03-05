#include <iostream> 

#include <queue> 

  

class Sensor { 

public: 

  int value; 

   

  void readData() { 

    // Code to read sensor data goes here 

    // For this example, we'll just generate a random number between 0 and 100 

    value = rand() % 100; 

  

  } 

}; 

  

class SensorData { 

public: 

    int name; 

  std::queue<int> dataQueue; 

   

  void readSensorData(Sensor& sensor) { 

    sensor.readData(); 

    dataQueue.push(sensor.value); 

  } 

   

  void printData() { 

    while (!dataQueue.empty()) { 

      std::cout << "Sensor data " <<name<<": "<< dataQueue.front() << std::endl; 

      dataQueue.pop(); 

    } 

  } 

}; 

  

int main() { 

  Sensor sensor1; 

  Sensor sensor2; 

  SensorData sensorData1; 

  SensorData sensorData2; 

   

  sensorData1.name=1; 

  sensorData2.name=2; 

  while (true) { 

    sensorData1.readSensorData(sensor1); 

    sensorData1.printData(); 

    sensorData2.readSensorData(sensor2); 

    sensorData2.printData(); 

     

  } 

   

  return 0;
