#!/usr/bin/env python2.7
#coding: utf-8

import SerialReceiveData
import time
import OrderPushList
import BroadCast
#CMD = "_c#01111111111111111,602$"
CMD = "_h#alive$"
i=0
#order_temp = "FC009108A8B8F5"
#CMD = order_temp.decode('hex')

while True:
    print "input order: "
    data = str(raw_input())
    if data == "exit":
	break
    #CMD = "%s. _h#alive$"%str(i)
    s = SerialReceiveData.Control()
    #result = s.command(CMD)
    #print result
    i = i+1
    #print "count : " +str(i)
    module_short_address = "0001"
    msg_id = "02"
    order = "c"
    #data = "0open"
    orderpushlist_addr= '/tmp/com.inkkinet.orderpushlist'
    data_temp = "or"+str(msg_id)+","+module_short_address+","+order+","+data
    BroadCast.send_data(orderpushlist_addr,data_temp)
