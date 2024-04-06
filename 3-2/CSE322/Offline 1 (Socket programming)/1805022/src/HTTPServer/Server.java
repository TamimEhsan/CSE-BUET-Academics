package HTTPServer;


import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
    public static int PORT = 5022;

    //  start server and wait for clients
    public static void main(String[] args) {

        File baseDir = new File("");
        String logPath = baseDir.getAbsolutePath();
        logPath = logPath.concat("/log");
        File logDirectory = new File(logPath);
        System.out.println(logDirectory.getAbsolutePath());
        if(!logDirectory.exists()){
            logDirectory.mkdir();
        }else{
            // delete directory and create new one
            String[] entries = logDirectory.list();
            for(String entry: entries){
                File toBeDeleted = new File(logDirectory.getPath(), entry);
                toBeDeleted.delete();
            }
        }
        String rootPath = baseDir.getAbsolutePath().concat("/root");
        File rootDirectory = new File(rootPath);
        if( !rootDirectory.exists() ) rootDirectory.mkdir();

        String uploadPath = baseDir.getAbsolutePath().concat("/uploaded");
        File uploadDirectory = new File(uploadPath);
        if( !uploadDirectory.exists() ) uploadDirectory.mkdir();
        String logFilePath = logDirectory.getAbsolutePath();

        String basicTemplate = readFileData("index.html");
        try {
            ServerSocket server = new ServerSocket(PORT, 100);
            System.out.println("Server started");
            while (true) {
                Socket connection = server.accept();
                System.out.println("New Client connected!");
                ServerThread serverThread= new ServerThread(connection,logFilePath,basicTemplate);
                serverThread.start();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static String readFileData(String fileName) {
        try{
            File file = new File(fileName);
            FileInputStream fis = new FileInputStream(file);
            BufferedReader br = new BufferedReader(new InputStreamReader(fis, "UTF-8"));
            StringBuilder sb = new StringBuilder();
            String line;
            while(( line = br.readLine()) != null ) {
                sb.append( line );
                sb.append( '\n' );
            }
            return sb.toString();
        }catch (Exception e){
            System.out.println(e.getMessage());
        }

        return "";
    }





}
