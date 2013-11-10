package com.spaceon.udp;

import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.spaceon.R;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.TextView.OnEditorActionListener;

public class UDPSocketActivity extends Activity {
	EditText msg_et = null;
	Button send_bt = null;
	TextView info_tv = null;
	private String msg = null;
	private String send_msg = null;
	public static Handler mHandler;
	  
	 public static String content = ""; 
	/** Called when the activity is first created. */
	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.udpsocket);
		msg_et = (EditText) findViewById(R.id.msg_et);
		send_bt = (Button) findViewById(R.id.send_bt);
		info_tv = (TextView) findViewById(R.id.info_tv);
		 mHandler = new Handler() {
	    		public void handleMessage(Message msg) {
	    			super.handleMessage(msg);
	    			info_tv.setText(content);
	    		}
	    	};
	//	ExecutorService exec = Executors.newCachedThreadPool();
		
		new Thread() {
			@Override
			public void run() {
				UDPSocketReceive server = new UDPSocketReceive();
				 server.runReceive();
				
			}
		}.start(); 
	//	exec.execute(server);
		msg_et.setOnEditorActionListener(new OnEditorActionListener() {
			public boolean onEditorAction(TextView v, int actionId, KeyEvent event) {
				 
				send_msg =v.getText().toString();
				 
				return false;
			}
		});
		send_bt.setOnClickListener(new OnClickListener() {
			@Override
			public void onClick(View v) {
				
				new Thread() {
					@Override
					public void run() {
						UDPSocketSend client = new UDPSocketSend(msg_et.getText().toString());
						 client.send();
						
					}
				}.start();
				//info_tv.setText(msg);
			}
		});

	}
}