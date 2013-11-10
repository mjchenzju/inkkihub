package com.spaceon.tcp;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import com.spaceon.R;
import com.spaceon.udp.UDPSocketSend;
import com.spaceon.udp.UDPSocketReceive;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.NetworkOnMainThreadException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class TCPSocketActivity  extends Activity {
    Button send_bt = null;
    public static Handler mHandler;
    private TextView textView;
    public static String content = ""; 
    EditText msg_et = null;
	/** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.tcpsocket);
        send_bt = (Button) findViewById(R.id.sendButton);
        textView = (TextView)findViewById(R.id.outputId);
         msg_et = (EditText)findViewById(R.id.inputId);
        mHandler = new Handler() {
    		public void handleMessage(Message msg) {
    			super.handleMessage(msg);
    			textView.setText(content);
    		}
    	};
        new Thread() {
			@Override
			public void run() {
				TCPSocketReceive receiveSocket = new TCPSocketReceive();
				receiveSocket.receive();
				
			}
		}.start(); 
    	send_bt.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				
				new Thread() {
					@Override
					public void run() {
						TCPSocketSend tCPSocketSend = new TCPSocketSend(msg_et.getText().toString());
						tCPSocketSend.send();
						
					}
				}.start();
				//info_tv.setText(msg);
			}
		});
    }
	 
}
