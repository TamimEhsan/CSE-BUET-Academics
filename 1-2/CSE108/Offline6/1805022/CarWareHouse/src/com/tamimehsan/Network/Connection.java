package com.tamimehsan.Network;

import com.tamimehsan.Model.TransferObject;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;

public class Connection {
    private static Connection instance;

    private Socket connection;
    private ObjectInputStream in;
    private ObjectOutputStream out;

    private boolean connected;
    private static String LOCALHOST = "127.0.0.1";
    private static int PORT = 26979;

    private Connection() {
    }

    public static Connection getInstance() {
        if (instance == null) {
            instance = new Connection();
        }
        return instance;
    }

    public void startConnection() {
        new Thread() {
            @Override
            public void run() {
                try {
                    connection = new Socket(InetAddress.getByName(LOCALHOST), PORT);
                    out = new ObjectOutputStream(connection.getOutputStream());
                    in = new ObjectInputStream(connection.getInputStream());
                    connected = true;
                    getInput();
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }.start();
    }

    private void getInput() {
        while (connected) {
            try {
                TransferObject message = (TransferObject) in.readUnshared();
                RequestProcessor.getInstance().processRequest(message);
            } catch (IOException | ClassNotFoundException e) {
                connected = false;
            }
        }
    }

    public void send(TransferObject s) {
        if (!connected) return;
        try {
            out.writeUnshared(s);
        } catch (IOException e) {
            connected = false;
        }
    }

    public void closeClient() {
        connected = false;
        try {
            if (out != null) out.close();
            if (in != null) in.close();
            if (connection != null) connection.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println("Closing connection");
    }

}
