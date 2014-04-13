package es.pymasde.blueterm;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
//import java.net.InetAddress;
//import java.net.NetworkInterface;
import java.net.ServerSocket;
import java.net.Socket;
//import java.net.SocketException;
import java.util.Date;

import android.app.Activity;
import android.content.ContentValues;
import android.content.Intent;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import static android.provider.BaseColumns._ID;
//import static com.strand.TMConstants.*;

public class ServerActivity extends Service {

    private TextView serverStatus, tvIncoming, tvDBDisplay;

    // default ip
    public static String SERVERIP = "localhost";

    // designate a port
    public static final int SERVERPORT = 5000;

    private Handler handler = new Handler();

    private ServerSocket serverSocket;

   
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        
        setContentView(R.layout.server);
        serverStatus = (TextView) findViewById(R.id.server_status);
        tvIncoming = (TextView) findViewById(R.id.tvIncoming);
        tvDBDisplay = (TextView) findViewById(R.id.tvDB);

//        SERVERIP = getLocalIpAddress();

        Thread fst = new Thread(new ServerThread());
        fst.start();
    }

    public class ServerThread implements Runnable {

//        String textIncoming = null;
        String line = null;
        
        public void run() {
            try {
                if (SERVERIP != null) {
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            serverStatus.setText("Listening on IP: " + SERVERIP);
                        }
                    });
                    serverSocket = new ServerSocket(SERVERPORT);
                    while (true) {
                        // listen for incoming clients
                        Socket client = serverSocket.accept();
                        handler.post(new Runnable() {
                            @Override
                            public void run() {
                                serverStatus.setText("Connected.");
                            }
                        });

                        try {
                            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
//                            String line = null;
                        	PrintStream out = new PrintStream(client.getOutputStream());
                            while ((line = in.readLine()) != null) {
                                Log.d("ServerActivity", line);
//                                textIncoming = line;
                                handler.post(new Runnable() {
                                    @Override
                                    public void run() {
//                                    	tvIncoming.setText(line);
                                    	tvIncoming.append(line+"\n");
                                    }
                                });
//                				out.println(new Date().getTime());
//                				out.println(Integer.toString(107));
                				out.println(Long.toString((long) new Date().getTime()));
                                Log.d("ServerActivity", "Phone to PC " + new Date().getTime());
//                				out.println("TLC");
                                handler.post(new Runnable() {
                                    @Override
                                    public void run() {
/*                            			if (new Date().getTime() % 2000 == 0) {
                            				out.println("Phone to PC " + new Date().getTime());
                            				out.println("TLM");
                            			}
*/                                        // do whatever you want to the front end
                                        // this is where you can be creative
                                    }
                                });
                            }
                            break;
                        } catch (Exception e) {
                            handler.post(new Runnable() {
                                @Override
                                public void run() {
                                    serverStatus.setText("Oops. Connection interrupted. Please reconnect your phone.");
                                }
                            });
                            e.printStackTrace();
                        }
                    }
                } else {
                    handler.post(new Runnable() {
                        @Override
                        public void run() {
                            serverStatus.setText("Couldn't detect internet connection.");
                        }
                    });
                }
            } catch (Exception e) {
                handler.post(new Runnable() {
                    @Override
                    public void run() {
                        serverStatus.setText("Error");
                    }
                });
                e.printStackTrace();
            }
        }
    }

    // gets the ip address of your phone's network
/*    private String getLocalIpAddress() {
        try {
            for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
                NetworkInterface intf = en.nextElement();
                for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
                    InetAddress inetAddress = enumIpAddr.nextElement();
                    if (!inetAddress.isLoopbackAddress()) { return inetAddress.getHostAddress().toString(); }
                }
            }
        } catch (SocketException ex) {
            Log.e("ServerActivity", ex.toString());
        }
        return null;
    }
*/
    @Override
    protected void onStop() {
        super.onStop();
        try {
             // make sure you close the socket upon exiting
             serverSocket.close();
         } catch (IOException e) {
             e.printStackTrace();
         }
    }

    public void DisplayDB(View v) {
//    	Intent i=new Intent(this, MCAService.class);
//    	startService(i); 
//    	Cursor cursor = phoneTM.getPhoneDBRecords();
//        startManagingCursor(cursor);
//    	displayPhoneDB(cursor);
    }

    public void ClearDBDisplay(View v) {
//    	Intent i=new Intent(this, MCAService.class);
//    	startService(i); 
//    	tvDBDisplay.setText("");
//    	try {
//        	phoneTM.importDatabase("DBDump.db");
//		} catch (IOException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
    }

    private void displayPhoneDB( Cursor cursor ) {
    	StringBuilder builder = new StringBuilder("Phone DB:\n");
    	int ind = 0;
    	while (cursor.moveToNext()) {
//    		builder.append(phoneTM.getPhoneDBRecord(cursor)).append("\n");
//    		builder.append(ind).append(phoneTM.getPhoneDBRecord(cursor)).append("\n");
    		ind++;
    	}
/*    	try {
			builder = phoneTM.importXMLDatabase("");
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
*/    	tvDBDisplay.setText(builder);
    }

    
}