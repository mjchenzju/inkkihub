package com.spaceon;

 

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.spaceon.serialPort.MainMenu;
import com.spaceon.tcp.TCPSocketActivity;
import com.spaceon.udp.UDPSocketActivity;

public class socketAndSerialPortDemoActivity extends Activity {
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        final Button buttonUdp = (Button)findViewById(R.id.udp_id);
        buttonUdp.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivity(new Intent(socketAndSerialPortDemoActivity.this, UDPSocketActivity.class));
			}
		});

      final Button buttonTcp = (Button)findViewById(R.id.tcp_id);
        buttonTcp.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivity(new Intent(socketAndSerialPortDemoActivity.this, TCPSocketActivity.class));
			}
		});
          
        final Button buttonSerial= (Button)findViewById(R.id.serial_id);
        buttonSerial.setOnClickListener(new View.OnClickListener() {
			public void onClick(View v) {
				startActivity(new Intent(socketAndSerialPortDemoActivity.this, MainMenu.class));
			}
		}); 
    }
}