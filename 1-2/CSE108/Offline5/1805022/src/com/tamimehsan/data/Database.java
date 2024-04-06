package com.tamimehsan.data;

import com.tamimehsan.classes.Car;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Database {
    private static Database instance;
    private static final String INPUT_FILE_NAME = "src/com/tamimehsan/data/cars.txt";
    private static final String OUTPUT_FILE_NAME = "src/com/tamimehsan/data/cars.txt";
    private List <Car> cars;
    private Database() {
        cars = new ArrayList<Car>();
    }

    public static Database getInstance(){
        if(instance == null ){
            instance = new Database();
        }
        return instance;
    }

    public boolean readData(){
        try {
            String line;
            BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE_NAME));
            while (true) {
                line = br.readLine();
                if (line == null) break;
                addDataFromString(line);
            }
            br.close();
        } catch (Exception  e) {
            e.printStackTrace();
        }
        return true;
    }

    private void addDataFromString(String data){
        String details[] = data.split(",");
        Car car = new Car(details[0],Integer.parseInt(details[1]),details[2],details[3],details[4],details[5],details[6],Integer.parseInt(details[7]));
        cars.add(car);
    }

    public List<Car> searchCarByRegistrationNumber(String registrationNumber){
        List<Car> searchedCars = new ArrayList<Car>();
        for(Car car: cars){
            if( car.getRegistrationNumber().equalsIgnoreCase(registrationNumber) ){
                searchedCars.add(car);
                return searchedCars;
            }
        }
        return searchedCars;
    }
    public List<Car> searchByMadeAndMake(String carMake,String carModel){
        List<Car> searchedCars = new ArrayList<Car>();
        for(Car car:cars){
            if( (car.getCarModel().equalsIgnoreCase(carModel) && car.getCarMake().equalsIgnoreCase(carMake)) || carModel.equalsIgnoreCase("ANY") ){
                searchedCars.add(car);
            }
        }
        return searchedCars;
    }

    public void addCar(String carToAdd){
        addDataFromString(carToAdd);
    }

    public void deleteCar(Car carToRemove){
        cars.remove(carToRemove);
    }


    public boolean writeData(){
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME));
            for(Car car: cars){
                String details = car.toString();
                bw.write(car.toString());
                bw.write("\n");
            }
            bw.close();
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        return true;
    }
}
