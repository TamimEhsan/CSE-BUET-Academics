package FileUploader;

import java.io.*;
import java.net.Socket;
import java.net.URLConnection;
import java.util.Date;

public class UploaderThread extends Thread {
    private String filePath;
    private static final int PORT = 5022;
    private static final String HOST = "127.0.0.1";
   // private static final String FILE_PATH = "C:\\Users\\Tamim\\Desktop\\";
   // private DataOutputStream dataOutputStream;
    private Socket connection;

    private int CHUNK_SIZE = 4 * 1024;
    public UploaderThread(String filePath) {
        this.filePath = filePath;

    }

    @Override
    public void run() {
        try{
            File file = new File(filePath);
            if( !file.exists() ){
                System.out.println("File not found");
                return;
            }
            connection = new Socket(HOST, PORT);
            DataOutputStream dataOutputStream = new DataOutputStream(connection.getOutputStream());
            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(connection.getOutputStream()));
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            FileInputStream  fileInputStream = new FileInputStream(file);;

            System.out.println("Connected to server");

            String fileName = file.getName();
            System.out.println(file.getName());

            bufferedWriter.write("Upload "+fileName);
            bufferedWriter.newLine();
            bufferedWriter.flush();

            String input = bufferedReader.readLine(); //<required for handshake :/

            // Here we  break file into chunks
            byte[] buffer = new byte[CHUNK_SIZE];

            int bytes = 0;
            while ((bytes = fileInputStream.read(buffer)) != -1) {
                dataOutputStream.write(buffer, 0, bytes);
                dataOutputStream.flush();
            }
            System.out.println("File sent to server");
            dataOutputStream.close();
            bufferedWriter.close();
            bufferedReader.close();
            fileInputStream.close();
            connection.close();

        }catch (Exception e){
            e.printStackTrace();
        }

    }

}
