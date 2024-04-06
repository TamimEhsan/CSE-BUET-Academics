package com.tamimehsan.Data;

import com.tamimehsan.Model.Car;
import com.tamimehsan.Model.User;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class Database {
    private static Database instance;
    private static final String INPUT_FILE_NAME_CAR = "src/com/tamimehsan/Data/cars.txt";
    private static final String OUTPUT_FILE_NAME_CAR = "src/com/tamimehsan/Data/cars.txt";
    private static final String INPUT_FILE_NAME_USER = "src/com/tamimehsan/Data/users.txt";
    private static final String OUTPUT_FILE_NAME_USER = "src/com/tamimehsan/Data/users.txt";
    private List<Car> cars;
    private List<User> users;
    private Database() {
        cars = new ArrayList<Car>();
        users = new ArrayList<User>();
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
            BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE_NAME_USER));
            while (true) {
                line = br.readLine();
                if (line == null) break;
                addUserDataFromString(line);
            }
            br.close();
        } catch (Exception  e) {
            e.printStackTrace();
        }
        return true;
    }
    public boolean readUserData(){
        try {
            String line;
            BufferedReader br = new BufferedReader(new FileReader(INPUT_FILE_NAME_CAR));
            while (true) {
                line = br.readLine();
                if (line == null) break;
                Car car = getDataFromString(line);
                cars.add(car);
            }
            br.close();
        } catch (Exception  e) {
            e.printStackTrace();
        }
        return true;
    }
    private Car getDataFromString(String data){
        String details[] = data.split(",");
        Car car = new Car(details[0],details[1],details[2],details[3],details[4],details[5],details[6],Integer.parseInt(details[7]),Integer.parseInt(details[8]),details[9]);
        return car;
    }
    private void addUserDataFromString(String data){
        String details[] = data.split(",");
        User user = new User(details[0],details[1]);
        users.add(user);
    }
    public boolean writeData(){
        try {
            BufferedWriter bw = new BufferedWriter(new FileWriter(OUTPUT_FILE_NAME_CAR));
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

    public boolean validateUser(String username,String password){
        for( User user:users ){
            if( user.getUsername().equals(username) && user.getPassword().equals(password) ){
                return true;
            }
        }
        return false;
    }
    public synchronized Car assertBuyCar(String carData){
        int index = -1;
        for(int i=0;i<cars.size();i++){
            Car thisCar = cars.get(i);
            if( thisCar.getRegistrationNumber().equals(carData) && thisCar.getQuantity()>0){
                thisCar.setQuantity(thisCar.getQuantity()-1);
                return thisCar;
            }
        }
       return null;
    }
    public synchronized void deleteCar(int index){
        cars.remove(index);
    }
    public Car addCar(String data){
        Car carToAdd = getDataFromString(data);
        for(Car car:cars){
            if( car.getRegistrationNumber().equals(carToAdd.getRegistrationNumber()) || ( car.getCarMake().equals(carToAdd.getCarMake()) && car.getCarModel().equals(carToAdd.getCarModel()) ) ){
                return null;
            }
        }
        cars.add(carToAdd);
        return carToAdd;
    }
    public synchronized Car modifyCar(String data){
        Car car = getDataFromString(data);
        for( int i=0;i<cars.size();i++ ){
            Car thisCar = cars.get(i);
            if( thisCar.getRegistrationNumber().equals(car.getRegistrationNumber()) ){
                cars.set(i,car);
                return car;
            }
        }
        return null;
    }
    public List<Car> getCars(){
        return cars;
    }

}
