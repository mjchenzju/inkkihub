package com.spaceon.udp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketException;
import java.net.UnknownHostException;
import android.os.NetworkOnMainThreadException;
public class UDPSocketSend {
	private static final int SEND_PORT = 7000;
	private DatagramSocket dSocket = null;
	private String msg;
	public UDPSocketSend(String msg)
	{
		super();
		this.msg = msg;
	}
	public  void send()
	{
		StringBuilder sb=new StringBuilder();
		InetAddress local = null;
		try {
			local = InetAddress.getByName("10.0.2.2");
			sb.append("已找到服务器，连接中").append("\n");
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		catch (NetworkOnMainThreadException e)
		{
			e.printStackTrace();
		}
		try {
			dSocket = new DatagramSocket();
		} catch (SocketException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sb.append("正在连接服务器").append("\n");
		
		int msgLen=msg==null?0:msg.length();
		DatagramPacket dPacket = new DatagramPacket(msg.getBytes(),msgLen,local,SEND_PORT);
		try {
			dSocket.send(dPacket);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		sb.append("消息发送成功").append("\n");
		dSocket.close();
		//return sb.toString();
	}
}
