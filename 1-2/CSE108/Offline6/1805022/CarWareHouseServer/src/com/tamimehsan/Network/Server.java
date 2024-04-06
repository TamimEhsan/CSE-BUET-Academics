package com.tamimehsan.Network;

import com.tamimehsan.Model.TransferObject;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;

public class Server {
    private static Server instance;
    private ServerSocket server;
    public static int PORT = 26979;
    public List<Client> clientsList;


    private Server() {
        clientsList = new ArrayList<>();
    }

    public static Server getInstance() {
        if (instance == null) {
            instance = new Server();
        }
        return instance;
    }

    public void startServer() {
        try {
            server = new ServerSocket(PORT, 100);
            System.out.println("Server started");
            while (true) {
                Socket connection = server.accept();
                System.out.println("New Client connected!");
                Client client = new Client(connection);
                client.start();
                clientsList.add(client);
            }
        } catch (IOException e) {
            //e.printStackTrace();
        }
    }

    public void broadcast(TransferObject message) {
        for (Client client : clientsList) {
            client.send(message);
        }
    }

    public void removeClient(Client client) {
        System.out.println("Client disconnected");
        clientsList.remove(client);
    }

    public void closeConnection() {
        for (Client client : clientsList) {
            client.closeClient();
        }
        try {
            if (server != null && !server.isClosed()) server.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
