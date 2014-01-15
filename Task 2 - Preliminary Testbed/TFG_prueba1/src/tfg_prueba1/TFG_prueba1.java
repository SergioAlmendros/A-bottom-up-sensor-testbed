
package tfg_prueba1;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;



public class TFG_prueba1 {


    public static void main(String[] args) throws IOException {
        
        int puerto = 5555;
        ServerSocket server = new ServerSocket(puerto);
        String msg = "";
        
        while(true)
        {
            Socket connectedserver = server.accept();
            BufferedReader inClient = new BufferedReader(new InputStreamReader(connectedserver.getInputStream()));
            int c = 0;
            msg = inClient.readLine();
            String[] msg2 = msg.split(" ");
            String msgData = msg2[1].substring(1);
            if(msgData.equals("FIN"))
            {
                connectedserver.close();
                break;
            }
            System.out.println(msg);
        }
        server.close();

    }
}
