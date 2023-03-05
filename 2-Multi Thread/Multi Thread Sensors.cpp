#include <iostream> 

#include <queue> 

#include <thread> 

#include <mutex> 

#include <chrono> 

  

class Sensor { 

public: 

  int value; 

   

  void readData() { 

    // Code to read sensor data goes here 

    // For this example, we'll just generate a random number between 0 and 100 

    value = rand() % 100; 

    std::this_thread::sleep_for(std::chrono::seconds(1)); 

  } 

}; 

  

class SensorData { 

public: 

  std::queue<int> dataQueue; 

  std::mutex dataMutex; 

  int name; 

  void readSensorData(Sensor& sensor) { 

    while (true) { 

      sensor.readData(); 

       

      std::lock_guard<std::mutex> guard(dataMutex); 

      dataQueue.push(sensor.value); 

    } 

  } 

   

  void printData() { 

    while (true) { 

      std::lock_guard<std::mutex> guard(dataMutex); 

      while (!dataQueue.empty()) { 

        std::cout << "Sensor data " <<name<<": "<< dataQueue.front() << std::endl; 

        dataQueue.pop(); 

      } 

    } 

  } 

}; 

  

int main() { 

  const int numSensors = 4; 

  Sensor sensors[numSensors]; 

  SensorData sensorData1; 

   SensorData sensorData2; 

   

  sensorData1.name=1; 

  sensorData2.name=2; 

  

  

   

  std::thread threads[numSensors]; 

   

    threads[0] = std::thread(&SensorData::readSensorData, &sensorData1, std::ref(sensors[0])); 

     threads[1] = std::thread(&SensorData::readSensorData, &sensorData2, std::ref(sensors[1])); 

   

   

  std::thread printThread1(&SensorData::printData, &sensorData1); 

  std::thread printThread2(&SensorData::printData, &sensorData2); 

   

  for (int i = 0; i < numSensors; ++i) { 

    threads[i].join(); 

  } 

   

  printThread1.join(); 

  printThread2.join(); 

   

  return 0; 

} 
