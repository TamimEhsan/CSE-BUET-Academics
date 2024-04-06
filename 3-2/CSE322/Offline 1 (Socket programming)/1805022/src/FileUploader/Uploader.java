package FileUploader;

import java.util.Scanner;

public class Uploader {
    public static void main(String[] args) {
        // connect to socket running at port 5022 and create a new thread
        // to handle the request
        Scanner scanner = new Scanner(System.in);
        while(true){
            String fileName = scanner.nextLine();
            UploaderThread uploaderThread = new UploaderThread(fileName);
            uploaderThread.start();
        }

    }
}
