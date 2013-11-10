package com.spaceon.tcp;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.ServerSocket;
import java.net.Socket;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.TextView;

public class TCPSocketReceive {
	/** Called when the activity is first created. */
	private final int SERVER_PORT = 8090;
	
	 

	public void receive() {
		try {
			// ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
			ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
			// 循环侦听客户端连接请求
			Log.d("test", "startServer:");
			while (true) {
				Socket client = serverSocket.accept();

				try {
					Log.d("test", "有人来访:");
					// 等待客户端发送打开网站的消息
					BufferedReader in = new BufferedReader(
							new InputStreamReader(client.getInputStream()));
					String str = in.readLine();
					TCPSocketActivity.content = str + "\n";
					TCPSocketActivity.mHandler.sendMessage(TCPSocketActivity.mHandler.obtainMessage());

				} catch (Exception e) {
					e.printStackTrace();
				} finally {
					client.close();
				}
				Thread.sleep(1000);
			}
		} catch (Exception e) {
			Log.d("test", "Exception:");
			e.printStackTrace();
		}
	}


}