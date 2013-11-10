package com.spaceon.tcp;

import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.os.NetworkOnMainThreadException;

public class TCPSocketSend {
	private final int SERVER_PORT = 51706;
	private final String SERVER_IP = "192.168.40.29";
	private String content = "";

	/** Called when the activity is first created. */
	private String msg;

	public TCPSocketSend(String msg) {
		this.msg = msg;
	}

	public void send() {

		Socket socket;
		try {
			socket = new Socket(SERVER_IP, SERVER_PORT);

			OutputStream ops = socket.getOutputStream();

			DataOutputStream dos = new DataOutputStream(ops);

			dos.write(msg.getBytes());
			Log.d("test", "send succ");
			dos.close();
		} catch (UnknownHostException e) {
			Log.d("test", "UnknownHostException");
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NetworkOnMainThreadException e) {
			Log.d("test", "NetworkOnMainThreadException");
		} catch (IOException e) {
			Log.d("test", "IOException");
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			Log.d("test", "finally");
		}

	}
}