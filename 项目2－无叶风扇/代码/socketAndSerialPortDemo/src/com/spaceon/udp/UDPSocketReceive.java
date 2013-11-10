package com.spaceon.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

import com.spaceon.tcp.TCPSocketActivity;

import android.util.Log;

public class UDPSocketReceive  {
	private static final int RECEIVE_PORT = 6000;
	private byte[] msg = new byte[1024];
	private boolean life = true;

	public UDPSocketReceive() {
	}

	public boolean isLife() {
		return life;
	}

	public void setLife(boolean life) {
		this.life = life;
	}

	//@Override
	public void runReceive() {
		DatagramSocket dSocket = null;
		byte[] buf=null;
		DatagramPacket dPacket = new DatagramPacket(msg, msg.length);
		try {
			dSocket = new DatagramSocket(RECEIVE_PORT);

			while (life) {
				try {
					dSocket.receive(dPacket);
				//	Log.i("msg receive", new String(dPacket.getData()));
					UDPSocketActivity.content = new String(dPacket.getData()) + "\n";
					UDPSocketActivity.mHandler.sendMessage(UDPSocketActivity.mHandler.obtainMessage());
				//	dPacket.setData(buf);
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		} catch (SocketException e) {
			e.printStackTrace();
		}
		// TODO Auto-generated method stub

	}

}
