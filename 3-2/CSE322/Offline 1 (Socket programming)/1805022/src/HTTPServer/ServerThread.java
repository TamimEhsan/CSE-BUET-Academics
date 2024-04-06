package HTTPServer;


import java.io.*;
import java.net.Socket;
import java.net.URLConnection;
import java.util.Date;

public class ServerThread extends Thread {
    private Socket connection;

    private String req;

    private DataOutputStream dataOutputStream = null;
    private DataInputStream dataInputStream = null;

    private BufferedReader reader;

    private String logFilePath;

    private PrintStream printer;
    private static int request_no = 0;

    private String basicTemplate;

    private int CHUNK_SIZE = 4 * 1024;

    public ServerThread(Socket connection,String logFilePath,String basicTemplate) {
        this.connection = connection;
        this.logFilePath = logFilePath;
        try {
            dataOutputStream = new DataOutputStream(connection.getOutputStream());
            printer = new PrintStream(connection.getOutputStream());
            dataInputStream = new DataInputStream(connection.getInputStream());
            reader = new BufferedReader(new InputStreamReader(connection.getInputStream()));
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.req = req;
        this.basicTemplate = basicTemplate;//readFileData("index.html");
    }



    @Override
    public void run() {
        System.out.println("in client run");
        PrintWriter fileWriter=null;
        try {

            String httpRequest = "";
            try {
                httpRequest = reader.readLine();
            } catch(IOException e) {
                e.printStackTrace();
                return;
            }

            if( httpRequest!=null ){
                System.out.println("httpRequest:: "+httpRequest);
            }else{
                return;
            }
            String httpMethod = httpRequest.split(" ")[0];
            String fileName = httpRequest.split(" ")[1];

            String url = getUrl(httpRequest);
            String path = getPath(httpRequest);

            fileWriter = new PrintWriter(logFilePath+"\\http_log_"+(++request_no)+".log");
            fileWriter.println("HTTP REQUEST LINE FROM CLIENT:\n"+httpRequest+"\n");
            fileWriter.println("HTTP RESPONSE TO CLIENT:");
            if( httpMethod.equalsIgnoreCase("UPLOAD") ){

                recieveFile(fileName);

            }else if( url.equalsIgnoreCase("/") ){

                String htmlPage = basicTemplate.replace("<content>","<h1>Welcome</h1>Click to visit File Server<a class=\"btn btn-primary\" href=\"root/\">Click</a>");
                String htmlHeader = buildHttpHeader("/", htmlPage.length(), "text/html","200 OK");
                printer.println(htmlHeader);
                printer.println(htmlPage);
                fileWriter.write(htmlHeader);

            }else if( url.startsWith("/root") ){
                boolean fileExists = fileExists(path);
                if( !fileExists ){

                    String htmlPage = basicTemplate.replace("<content>","<h1>Error 404</h1><h2>File Not Found</h2>");
                    String htmlHeader = buildHttpHeader("/", htmlPage.length(), "text/html","404 Not Found");
                    fileWriter.write(htmlHeader);
                    printer.println(htmlHeader);
                    printer.println(htmlPage);

                }else if(isDirectory(path)){
                    String htmlPage = buildDirectoryPage(path,url);
                    htmlPage = basicTemplate.replace("<content>",htmlPage);
                    String htmlHeader = buildHttpHeader("/", htmlPage.length(), "text/html","200 OK");
                    fileWriter.write(htmlHeader);
                    printer.println(htmlHeader);
                    printer.println(htmlPage);

                }else{
                    String resposnse = sendFile(path);
                    fileWriter.write(resposnse);
                }
            }else{
                String htmlPage = basicTemplate.replace("<content>","<h1>Error 404</h1><h2>File Not Found</h2>");
                String htmlHeader = buildHttpHeader("/", htmlPage.length(), "text/html","404 Not Found");
                printer.println(htmlHeader);
                printer.println(htmlPage);
                fileWriter.write(htmlHeader);
            }

            dataOutputStream.close();
            printer.close();
            reader.close();
            fileWriter.close();
            connection.close();

            System.out.println("connection closed");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    String getPath(String req) {
        String[] reqParts = req.split(" ");
        String basePath = new File("").getAbsolutePath();
        String url = basePath.concat(reqParts[1]);
        return url;
    }
    String getUrl(String req) {
        String[] reqParts = req.split(" ");
        return reqParts[1];
    }


    boolean fileExists(String url) {
        File file = new File(url);
        return file.exists();
    }
    // check if path is a directory
    boolean isDirectory(String path) {
        File file = new File(path);
        return file.isDirectory();
    }
    private String buildHttpHeader(String path, long length,String type,String status) {
        StringBuilder sbHtml = new StringBuilder();

        sbHtml.append("HTTP/1.1 200 OK\r\n");
        sbHtml.append("Server: Java HTTP Server: 1.0\r\n");
        sbHtml.append("Date: " + new Date() + "\r\n");
        sbHtml.append("Content-Type: "+type+"\r\n");
        sbHtml.append("Content-Length: " + length + "\r\n");

        return sbHtml.toString();
    }

    /**
     * Build http page
     * @return, page text
     */


    // build directory page
    private String buildDirectoryPage(String path,String url) {
        StringBuilder sbHtml = new StringBuilder();
        if( !url.equals("/root/") )
            sbHtml.append("<a class=\"btn btn-primary\" href=\"../\">Back</a>");
        sbHtml.append("<table class=\"table table-striped\">");
        sbHtml.append("<tr>");
        sbHtml.append("<th>File Name</th>");
        sbHtml.append("<th>File Size</th>");
        sbHtml.append("<th>File Type</th>");
        sbHtml.append("<th>Action</th>");
        sbHtml.append("</tr>");
        File directoryPath = new File(path);
        //List of all files and directories


        String contents[] = directoryPath.list();
        for (int i = 0; i < contents.length; i++) {

            File file = new File(path + "/" + contents[i]);
            sbHtml.append("<tr>");
            // add link to contents[i]
            sbHtml.append("<td><a href=" +url+"/"+ contents[i] + ">" + contents[i] + "</a></td>");
            // sbHtml.append("<td>" + contents[i] + "</td>");
            sbHtml.append("<td>" + file.length() + "</td>");
            sbHtml.append("<td>" + (file.isDirectory() ? "Directory" : "File") + "</td>");

            sbHtml.append("<td><a class=\"btn btn-primary\" href=" +url+"/"+ contents[i] + ">" + (file.isDirectory() ? "Open" : "Download")+ "</a></td>");
            sbHtml.append("</tr>");
        }
        sbHtml.append("</table>");
        return sbHtml.toString();
    }
    private String sendFile(String path) throws Exception {

        StringBuilder sbHtml = new StringBuilder();

        int bytes = 0;
        // Open the File where he located in your pc
        File file = new File(path);
        FileInputStream fileInputStream = new FileInputStream(file);
       // System.out.println(file.getName());
       // System.out.println(file.getAbsolutePath());
        // Here we send the File to Server
        String mimeType = URLConnection.guessContentTypeFromName(file.getName());
        if(mimeType == null)
            mimeType = "application/octet-stream";

        dataOutputStream.writeBytes("HTTP/1.1 200 OK\r\n");
        dataOutputStream.writeBytes("Server: Java HTTP Server: 1.0\r\n");
        dataOutputStream.writeBytes("Date: " + new Date() + "\r\n");
        dataOutputStream.writeBytes("Content-Type: "+mimeType+"\r\n");

        sbHtml.append("HTTP/1.1 200 OK\r\n");
        sbHtml.append("Server: Java HTTP Server: 1.0\r\n");
        sbHtml.append("Date: " + new Date() + "\r\n");
        sbHtml.append("Content-Type: "+mimeType+"\r\n");



        //  pr.write("Content-Type: image\r\n");
        if( mimeType.equals("text/plain") || mimeType.equals("image/jpeg") ){

            dataOutputStream.writeBytes("Content-Disposition: inline\r\n");
            sbHtml.append("Content-Disposition: inline\r\n");
        }else{
            sbHtml.append("Content-Disposition: attachment; filename="+file.getName()+"\r\n");
            dataOutputStream.writeBytes("Content-Disposition: attachment; filename=" + file.getName() + "\r\n");

        }
        dataOutputStream.writeBytes("Content-Length: " + file.length() + "\r\n");
        sbHtml.append("Content-Length: " + file.length() + "\r\n");
        dataOutputStream.writeBytes("\r\n");
        //pr.write("\r\n");
        dataOutputStream.flush();
        // Here we  break file into chunks
        byte[] buffer = new byte[4 * 1024];

        while ((bytes = fileInputStream.read(buffer)) != -1) {
            dataOutputStream.write(buffer, 0, bytes);
            dataOutputStream.flush();
        }
        fileInputStream.close();
        return sbHtml.toString();
    }
    public void recieveFile(String fileName){
        try{
            BufferedWriter bufferedWriter = new BufferedWriter(new OutputStreamWriter(connection.getOutputStream()));

            bufferedWriter.write("START");
            bufferedWriter.newLine();
            bufferedWriter.flush();

            int bytesRead = 0;
            byte[] buffer = new byte[CHUNK_SIZE];


            String basePath = new File("").getAbsolutePath();
            String path = basePath.concat("/uploaded/"+fileName);
            FileOutputStream fileOutputStream = new FileOutputStream(path);


            long size = 0;
            while ( /*size>0 &&*/ (bytesRead = dataInputStream.read(buffer, 0, buffer.length /*(int)Math.min(buffer.length, size) */ )) != -1) {
                fileOutputStream.write(buffer, 0, bytesRead);
                size += bytesRead;

            }
            fileOutputStream.close();
            bufferedWriter.close();
            dataInputStream.close();
            System.out.println("File uploaded successfully");

        }catch (Exception e){
            e.printStackTrace();
        }

    }

}