package com.tamimehsan.Network;

import com.tamimehsan.Data.Database;
import com.tamimehsan.Model.TransferObject;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Client extends Thread {

    private Socket connection;

    private ObjectOutputStream out;
    private ObjectInputStream in;

    public Client(Socket connection) {
        this.connection = connection;
    }

    @Override
    public void run() {
        try {
            out = new ObjectOutputStream(connection.getOutputStream());
            in = new ObjectInputStream(connection.getInputStream());
            TransferObject transferObject = RequestProcessor.getInstance().sendAllCarRequest(Database.getInstance().getCars());
            send(transferObject);
            do {
                TransferObject message = (TransferObject) in.readUnshared();
                RequestProcessor.getInstance().processRequest(message, this);
            } while (true);
        } catch (IOException | ClassNotFoundException e) {
            Server.getInstance().removeClient(this);
        }
    }

    public void send(TransferObject stringToSend) {
        try {
            out.writeUnshared(stringToSend);
        } catch (IOException e) {
            Server.getInstance().removeClient(this);
        }
    }

    public void closeClient() {
        try {
            if (connection != null && !connection.isClosed()) connection.close();
            if (in != null) in.close();
            if (out != null) out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
